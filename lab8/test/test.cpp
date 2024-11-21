#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "../src/WithState/GumballMachine.h"
#include "../src/MultiGumballMachine/Naive/GumballMachine.h"
#include "../src/MultiGumballMachine/MultiGumballMachine.h"

using ::testing::Return;

// TODO через моки протестировать сотояния

class MockGumballMachine : public IGumballMachine {
public:
    MOCK_METHOD(void, ReleaseBall, (), (override));
    MOCK_METHOD(unsigned, GetBallCount, (), (const, override));
    MOCK_METHOD(void, SetSoldOutState, (), (override));
    MOCK_METHOD(void, SetNoQuarterState, (), (override));
    MOCK_METHOD(void, SetSoldState, (), (override));
    MOCK_METHOD(void, SetHasQuarterState, (), (override));
};

class MockMultiGumballMachine : public multiGumballMachine::IMultiGumballMachine {
public:
    MOCK_METHOD(void, ReleaseBall, (), (override));
    MOCK_METHOD(unsigned, GetBallCount, (), (const, override));
    MOCK_METHOD(unsigned, GetQuarterCount, (), (const, override));
    MOCK_METHOD(unsigned, GetMaxQuarterCount, (), (const, override));
    MOCK_METHOD(void, AddQuarter, (), (override));
    MOCK_METHOD(void, RefillBall, (unsigned numBalls), (override));
    MOCK_METHOD(void, ReturnAllQuarters, (), (override));
    MOCK_METHOD(void, SetSoldOutState, (), (override));
    MOCK_METHOD(void, SetNoQuarterState, (), (override));
    MOCK_METHOD(void, SetSoldState, (), (override));
    MOCK_METHOD(void, SetHasQuarterState, (), (override));
};

class GumballMachineTest : public ::testing::Test
{
protected:
    GumballMachine gumballMachine{5};
    std::streambuf* originalCout{};
    std::ostringstream testOutput;

    void SetUp() override
    {
        originalCout = std::cout.rdbuf(testOutput.rdbuf());
    }

    void TearDown() override
    {
        std::cout.rdbuf(originalCout);
    }
};

TEST_F(GumballMachineTest, InitialState)
{
    EXPECT_EQ(gumballMachine.ToString(), R"(
Mighty Gumball, Inc.
C++-enabled Standing Gumball Model #2016
Inventory: 5 gumballs
Machine is waiting for quarter
)");
}

TEST_F(GumballMachineTest, InsertQuarterInNoQuarterState)
{
    gumballMachine.InsertQuarter();
    EXPECT_EQ(gumballMachine.ToString(), R"(
Mighty Gumball, Inc.
C++-enabled Standing Gumball Model #2016
Inventory: 5 gumballs
Machine is waiting for turn of crank
)");
}

TEST_F(GumballMachineTest, InsertQuarterInHasQuarterState)
{
    gumballMachine.InsertQuarter();
    gumballMachine.InsertQuarter();
    EXPECT_EQ(gumballMachine.ToString(), R"(
Mighty Gumball, Inc.
C++-enabled Standing Gumball Model #2016
Inventory: 5 gumballs
Machine is waiting for turn of crank
)");
}

TEST_F(GumballMachineTest, TurnCrankInHasQuarterState)
{
    gumballMachine.InsertQuarter();
    gumballMachine.TurnCrank();
    EXPECT_EQ(gumballMachine.ToString(), R"(
Mighty Gumball, Inc.
C++-enabled Standing Gumball Model #2016
Inventory: 4 gumballs
Machine is waiting for quarter
)");
}

TEST_F(GumballMachineTest, TurnCrankWithoutQuarter)
{
    gumballMachine.TurnCrank();
    EXPECT_EQ(gumballMachine.ToString(), R"(
Mighty Gumball, Inc.
C++-enabled Standing Gumball Model #2016
Inventory: 5 gumballs
Machine is waiting for quarter
)");
}

TEST_F(GumballMachineTest, EjectQuarterInHasQuarterState)
{
    gumballMachine.InsertQuarter();
    gumballMachine.EjectQuarter();
    EXPECT_EQ(gumballMachine.ToString(), R"(
Mighty Gumball, Inc.
C++-enabled Standing Gumball Model #2016
Inventory: 5 gumballs
Machine is waiting for quarter
)");
}

TEST_F(GumballMachineTest, EjectQuarterInNoQuarterState)
{
    gumballMachine.EjectQuarter();
    EXPECT_EQ(gumballMachine.ToString(), R"(
Mighty Gumball, Inc.
C++-enabled Standing Gumball Model #2016
Inventory: 5 gumballs
Machine is waiting for quarter
)");
}

TEST_F(GumballMachineTest, SoldOutState)
{
    for (int i = 0; i < 5; ++i) {
        gumballMachine.InsertQuarter();
        gumballMachine.TurnCrank();
    }

    EXPECT_EQ(gumballMachine.ToString(), R"(
Mighty Gumball, Inc.
C++-enabled Standing Gumball Model #2016
Inventory: 0 gumballs
Machine is sold out
)");
}

TEST_F(GumballMachineTest, InsertQuarterInSoldOutState)
{
    for (int i = 0; i < 5; ++i) {
        gumballMachine.InsertQuarter();
        gumballMachine.TurnCrank();
    }

    gumballMachine.InsertQuarter();

    EXPECT_EQ(gumballMachine.ToString(), R"(
Mighty Gumball, Inc.
C++-enabled Standing Gumball Model #2016
Inventory: 0 gumballs
Machine is sold out
)");
}

TEST_F(GumballMachineTest, EjectQuarterInSoldOutState)
{
    for (int i = 0; i < 5; ++i) {
        gumballMachine.InsertQuarter();
        gumballMachine.TurnCrank();
    }

    gumballMachine.EjectQuarter();

    EXPECT_EQ(gumballMachine.ToString(), R"(
Mighty Gumball, Inc.
C++-enabled Standing Gumball Model #2016
Inventory: 0 gumballs
Machine is sold out
)");
}

TEST_F(GumballMachineTest, MultipleOperations)
{
    for (int i = 0; i < 3; ++i)
    {
        gumballMachine.InsertQuarter();
        gumballMachine.TurnCrank();
        EXPECT_TRUE(!(gumballMachine.ToString().find("waiting for quarter") == std::string::npos));
    }

    for (int i = 0; i < 3; ++i)
    {
        gumballMachine.InsertQuarter();
        gumballMachine.TurnCrank();
    }

    EXPECT_TRUE(!(gumballMachine.ToString().find("sold out") == std::string::npos));
}

// Тесты для NoQuarterState
TEST_F(GumballMachineTest, NoQuarterState_InsertQuarter)
{
    gumballMachine.InsertQuarter();
    EXPECT_EQ(testOutput.str(), "You inserted a quarter\n");
}

TEST_F(GumballMachineTest, NoQuarterState_EjectQuarter)
{
    gumballMachine.EjectQuarter();
    EXPECT_EQ(testOutput.str(), "You haven't inserted a quarter\n");
}

TEST_F(GumballMachineTest, NoQuarterState_TurnCrank)
{
    gumballMachine.TurnCrank();
    EXPECT_EQ(testOutput.str(), "You turned but there's no quarter\nYou need to pay first\n");
}

// Тесты для HasQuarterState
TEST_F(GumballMachineTest, HasQuarterState_InsertQuarter)
{
    gumballMachine.InsertQuarter();
    gumballMachine.InsertQuarter();
    EXPECT_EQ(testOutput.str(), "You inserted a quarter\nYou can't insert another quarter\n");
}

TEST_F(GumballMachineTest, HasQuarterState_EjectQuarter)
{
    gumballMachine.InsertQuarter();
    gumballMachine.EjectQuarter();
    EXPECT_EQ(testOutput.str(), "You inserted a quarter\nQuarter returned\n");
}

TEST_F(GumballMachineTest, HasQuarterState_TurnCrank)
{
    gumballMachine.InsertQuarter();
    gumballMachine.TurnCrank();
    EXPECT_EQ(testOutput.str(), "You inserted a quarter\nYou turned...\nA gumball comes rolling out the slot...\n");
}

// Тесты для SoldOutState
TEST_F(GumballMachineTest, SoldOutState_InsertQuarter)
{
    std::string expectedString;
    for (int i = 0; i < 5; ++i)
    {
        gumballMachine.InsertQuarter();
        expectedString += "You inserted a quarter\n";
        gumballMachine.TurnCrank();
        expectedString += "You turned...\nA gumball comes rolling out the slot...\n";
    }

    gumballMachine.InsertQuarter();
    expectedString += "Oops, out of gumballs\nYou can't insert a quarter, the machine is sold out\n";
    EXPECT_EQ(testOutput.str(), expectedString);
}

TEST_F(GumballMachineTest, SoldOutState_EjectQuarter)
{
    std::string expectedString;
    for (int i = 0; i < 5; ++i)
    {
        gumballMachine.InsertQuarter();
        expectedString += "You inserted a quarter\n";
        gumballMachine.TurnCrank();
        expectedString += "You turned...\nA gumball comes rolling out the slot...\n";
    }

    gumballMachine.EjectQuarter();
    expectedString += "Oops, out of gumballs\nYou can't eject, you haven't inserted a quarter yet\n";
    EXPECT_EQ(testOutput.str(), expectedString);
}

TEST_F(GumballMachineTest, SoldOutState_TurnCrank)
{
    std::string expectedString;
    for (int i = 0; i < 5; ++i)
    {
        gumballMachine.InsertQuarter();
        expectedString += "You inserted a quarter\n";
        gumballMachine.TurnCrank();
        expectedString += "You turned...\nA gumball comes rolling out the slot...\n";
    }

    gumballMachine.TurnCrank();
    expectedString += "Oops, out of gumballs\nYou turned but there's no gumballs\nNo gumball dispensed\n";
    EXPECT_EQ(testOutput.str(), expectedString);
}

// Тесты для SoldState
TEST_F(GumballMachineTest, SoldState_InsertQuarter)
{
    std::string expectedString;
    gumballMachine.InsertQuarter();
    expectedString += "You inserted a quarter\n";
    gumballMachine.TurnCrank();
    expectedString += "You turned...\nA gumball comes rolling out the slot...\n";

    gumballMachine.InsertQuarter();
    expectedString += "You inserted a quarter\n";
    EXPECT_EQ(testOutput.str(), expectedString);
}

TEST_F(GumballMachineTest, SoldState_EjectQuarter)
{
    std::string expectedString;
    gumballMachine.InsertQuarter();
    expectedString += "You inserted a quarter\n";
    gumballMachine.TurnCrank();
    expectedString += "You turned...\nA gumball comes rolling out the slot...\n";

    gumballMachine.EjectQuarter();
    expectedString += "You haven't inserted a quarter\n";
    EXPECT_EQ(testOutput.str(), expectedString);
}

TEST_F(GumballMachineTest, SoldState_TurnCrank)
{
    std::string expectedString;
    gumballMachine.InsertQuarter();
    expectedString += "You inserted a quarter\n";
    gumballMachine.TurnCrank();
    expectedString += "You turned...\nA gumball comes rolling out the slot...\n";

    gumballMachine.TurnCrank();
    expectedString += "You turned but there's no quarter\nYou need to pay first\n";
    EXPECT_EQ(testOutput.str(), expectedString);
}

TEST_F(GumballMachineTest, SoldState_Dispence)
{
    std::string expectedString;
    for (int i = 0; i < 5; ++i)
    {
        gumballMachine.InsertQuarter();
        expectedString += "You inserted a quarter\n";
        gumballMachine.TurnCrank();
        expectedString += "You turned...\nA gumball comes rolling out the slot...\n";
    }

    gumballMachine.TurnCrank();
    expectedString += "Oops, out of gumballs\nYou turned but there's no gumballs\nNo gumball dispensed\n";
    EXPECT_EQ(testOutput.str(), expectedString);
}

// Тесты состояний через MockGumballMachine
// NoQuarterState
TEST_F(GumballMachineTest, Mock_NoQuarterState_InsertQuarter)
{
    MockGumballMachine mockGumballMachine;
    NoQuarterState state = NoQuarterState(mockGumballMachine);

    EXPECT_CALL(mockGumballMachine, SetHasQuarterState()).Times(1);

    state.InsertQuarter();
    EXPECT_EQ(testOutput.str(), "You inserted a quarter\n");
}

TEST_F(GumballMachineTest, Mock_NoQuarterState_EjectQuarter)
{
    MockGumballMachine mockGumballMachine;
    NoQuarterState state = NoQuarterState(mockGumballMachine);

    state.EjectQuarter();
    EXPECT_EQ(testOutput.str(), "You haven't inserted a quarter\n");
}

TEST_F(GumballMachineTest, Mock_NoQuarterState_TurnCrank)
{
    MockGumballMachine mockGumballMachine;
    NoQuarterState state = NoQuarterState(mockGumballMachine);

    state.TurnCrank();
    EXPECT_EQ(testOutput.str(), "You turned but there's no quarter\n");
}

TEST_F(GumballMachineTest, Mock_NoQuarterState_Dispense)
{
    MockGumballMachine mockGumballMachine;
    NoQuarterState state = NoQuarterState(mockGumballMachine);

    state.Dispense();
    EXPECT_EQ(testOutput.str(), "You need to pay first\n");
}

TEST_F(GumballMachineTest, Mock_NoQuarterState_ToString)
{
    MockGumballMachine mockGumballMachine;
    NoQuarterState state = NoQuarterState(mockGumballMachine);

    std::string actualString = state.ToString();
    EXPECT_EQ(actualString, "waiting for quarter");
}

// HasQuarterState
TEST_F(GumballMachineTest, Mock_HasQuarterState_InsertQuarter)
{
    MockGumballMachine mockGumballMachine;
    HasQuarterState state = HasQuarterState(mockGumballMachine);

    state.InsertQuarter();
    EXPECT_EQ(testOutput.str(), "You can't insert another quarter\n");
}

TEST_F(GumballMachineTest, Mock_HasQuarterState_EjectQuarter)
{
    MockGumballMachine mockGumballMachine;
    HasQuarterState state = HasQuarterState(mockGumballMachine);

    EXPECT_CALL(mockGumballMachine, SetNoQuarterState).Times(1);
    state.EjectQuarter();
    EXPECT_EQ(testOutput.str(), "Quarter returned\n");
}

TEST_F(GumballMachineTest, Mock_HasQuarterState_TurnCrank)
{
    MockGumballMachine mockGumballMachine;
    HasQuarterState state = HasQuarterState(mockGumballMachine);

    EXPECT_CALL(mockGumballMachine, SetSoldState).Times(1);
    state.TurnCrank();
    EXPECT_EQ(testOutput.str(), "You turned...\n");
}

TEST_F(GumballMachineTest, Mock_HasQuarterState_Dispense)
{
    MockGumballMachine mockGumballMachine;
    HasQuarterState state = HasQuarterState(mockGumballMachine);

    state.Dispense();
    EXPECT_EQ(testOutput.str(), "No gumball dispensed\n");
}

TEST_F(GumballMachineTest, Mock_HasQuarterState_ToString)
{
    MockGumballMachine mockGumballMachine;
    HasQuarterState state = HasQuarterState(mockGumballMachine);

    std::string actualString = state.ToString();
    EXPECT_EQ(actualString, "waiting for turn of crank");
}

// SoldState
TEST_F(GumballMachineTest, Mock_SoldState_InsertQuarter)
{
    MockGumballMachine mockGumballMachine;
    SoldState state = SoldState(mockGumballMachine);

    state.InsertQuarter();
    EXPECT_EQ(testOutput.str(), "Please wait, we're already giving you a gumball\n");
}

TEST_F(GumballMachineTest, Mock_SoldState_EjectQuarter)
{
    MockGumballMachine mockGumballMachine;
    SoldState state = SoldState(mockGumballMachine);

    state.EjectQuarter();
    EXPECT_EQ(testOutput.str(), "Sorry you already turned the crank\n");
}

TEST_F(GumballMachineTest, Mock_SoldState_TurnCrank)
{
    MockGumballMachine mockGumballMachine;
    SoldState state = SoldState(mockGumballMachine);

    state.TurnCrank();
    EXPECT_EQ(testOutput.str(), "Turning twice doesn't get you another gumball\n");
}

TEST_F(GumballMachineTest, Mock_SoldState_Dispense)
{
    MockGumballMachine mockGumballMachine;
    SoldState state = SoldState(mockGumballMachine);

    EXPECT_CALL(mockGumballMachine, ReleaseBall).Times(1);
    EXPECT_CALL(mockGumballMachine, GetBallCount())
            .WillOnce(Return(1));
    EXPECT_CALL(mockGumballMachine, SetNoQuarterState).Times(1);

    state.Dispense();

    EXPECT_CALL(mockGumballMachine, ReleaseBall).Times(1);
    EXPECT_CALL(mockGumballMachine, GetBallCount())
            .WillOnce(Return(0));
    EXPECT_CALL(mockGumballMachine, SetSoldOutState).Times(1);

    state.Dispense();
}

TEST_F(GumballMachineTest, Mock_SoldState_ToString)
{
    MockGumballMachine mockGumballMachine;
    SoldState state = SoldState(mockGumballMachine);

    std::string actualString = state.ToString();
    EXPECT_EQ(actualString, "delivering a gumball");
}

// SoldOutState
TEST_F(GumballMachineTest, Mock_SoldOutState_InsertQuarter)
{
    MockGumballMachine mockGumballMachine;
    SoldOutState state = SoldOutState(mockGumballMachine);

    state.InsertQuarter();
    EXPECT_EQ(testOutput.str(), "You can't insert a quarter, the machine is sold out\n");
}

TEST_F(GumballMachineTest, Mock_SoldOutState_EjectQuarter)
{
    MockGumballMachine mockGumballMachine;
    SoldOutState state = SoldOutState(mockGumballMachine);

    state.EjectQuarter();
    EXPECT_EQ(testOutput.str(), "You can't eject, you haven't inserted a quarter yet\n");
}

TEST_F(GumballMachineTest, Mock_SoldOutState_TurnCrank)
{
    MockGumballMachine mockGumballMachine;
    SoldOutState state = SoldOutState(mockGumballMachine);

    state.TurnCrank();
    EXPECT_EQ(testOutput.str(), "You turned but there's no gumballs\n");
}

TEST_F(GumballMachineTest, Mock_SoldOutState_Dispense)
{
    MockGumballMachine mockGumballMachine;
    SoldOutState state = SoldOutState(mockGumballMachine);

    state.Dispense();
    EXPECT_EQ(testOutput.str(), "No gumball dispensed\n");
}

TEST_F(GumballMachineTest, Mock_SoldOutState_ToString)
{
    MockGumballMachine mockGumballMachine;
    SoldOutState state = SoldOutState(mockGumballMachine);

    std::string actualString = state.ToString();
    EXPECT_EQ(actualString, "sold out");
}

// Тесты для наивной мульти машины

class NaiveMultiGumballMachineTest : public ::testing::Test {
protected:
    multiNaive::GumballMachine gumballMachine{5};
    std::streambuf* originalCout{};
    std::ostringstream testOutput;

    void SetUp() override {
        originalCout = std::cout.rdbuf(testOutput.rdbuf());
    }

    void TearDown() override {
        std::cout.rdbuf(originalCout);
    }
};

// Тесты для NoQuarterState
TEST_F(NaiveMultiGumballMachineTest, InitialState) {
    EXPECT_EQ(gumballMachine.ToString(), R"(
Mighty Gumball, Inc.
C++-enabled Standing Gumball Model #2016
Inventory: 5 gumballs
Machine is waiting for quarter
)");
}

TEST_F(NaiveMultiGumballMachineTest, InsertQuarter_NoQuarterState) {
    gumballMachine.InsertQuarter();
    EXPECT_EQ(testOutput.str(), "You inserted a quarter\n");
}

TEST_F(NaiveMultiGumballMachineTest, InsertQuarter_TooManyQuarters) {
    std::string expectedString;
    for (int i = 0; i < 5; ++i)
    {
        gumballMachine.InsertQuarter();
        if (i == 0)
        {
            expectedString += "You inserted a quarter\n";
        }
        else
        {
            expectedString += "You inserted another quarter\n";
        }
    }
    gumballMachine.InsertQuarter();
    expectedString += "You can't insert another quarter\n";

    EXPECT_EQ(testOutput.str(), expectedString);
}

TEST_F(NaiveMultiGumballMachineTest, EjectQuarter_NoQuarterState) {
    gumballMachine.EjectQuarter();
    EXPECT_EQ(testOutput.str(), "You can't eject, you haven't inserted a quarter yet\n");
}

TEST_F(NaiveMultiGumballMachineTest, EjectQuarter_HasQuarterState) {
    gumballMachine.InsertQuarter();
    gumballMachine.EjectQuarter();
    EXPECT_EQ(testOutput.str(), "You inserted a quarter\nReturn all quarters\n");
}

TEST_F(NaiveMultiGumballMachineTest, TurnCrank_NoQuarterState) {
    gumballMachine.TurnCrank();
    EXPECT_EQ(testOutput.str(), "You turned but there's no quarter\n");
}

TEST_F(NaiveMultiGumballMachineTest, Refill_NoQuarterState) {
    std::string expectedString;
    gumballMachine.Refill(5);
    expectedString += "Added gumball\n";
    EXPECT_EQ(testOutput.str(), expectedString);
}

// Тесты для HasQuarterState
TEST_F(NaiveMultiGumballMachineTest, TurnCrank_HasQuarterState) {
    gumballMachine.InsertQuarter();
    gumballMachine.TurnCrank();
    EXPECT_EQ(testOutput.str(), "You inserted a quarter\nYou turned...\nA gumball comes rolling out the slot...\n");
}

TEST_F(NaiveMultiGumballMachineTest, TurnCrank_SoldOutAfterDispense) {
    std::string expectedString;
    for (int i = 0; i < 5; ++i)
    {
        gumballMachine.InsertQuarter();
        gumballMachine.TurnCrank();
        expectedString += "You inserted a quarter\n";
        expectedString += "You turned...\nA gumball comes rolling out the slot...\n";
    }
    expectedString += "Oops, out of gumballs\nReturn all quarters\n";
    gumballMachine.TurnCrank();
    expectedString += "You turned but there's no gumballs\n";

    EXPECT_EQ(testOutput.str(), expectedString);
}

TEST_F(NaiveMultiGumballMachineTest, Refill_HasQuarterState) {
    std::string expectedString;
    gumballMachine.InsertQuarter();
    expectedString += "You inserted a quarter\n";
    gumballMachine.Refill(5);
    expectedString += "Added gumball\n";
    EXPECT_EQ(testOutput.str(), expectedString);
}

// Тесты для SoldState
TEST_F(NaiveMultiGumballMachineTest, SoldState_Dispense)
{
    std::string expectedString;
    expectedString += "You inserted a quarter\n";
    for (int i = 0; i < 5; ++i)
    {
        gumballMachine.InsertQuarter();
        if (i >= 1)
        {
            expectedString += "You inserted another quarter\n";
        }
    }
    for (int i = 0; i < 2; ++i)
    {
        gumballMachine.TurnCrank();
        expectedString += "You turned...\nA gumball comes rolling out the slot...\n";
    }
    for (int i = 0; i < 2; ++i)
    {
        gumballMachine.InsertQuarter();
        expectedString += "You inserted another quarter\n";
    }
    for (int i = 0; i < 3; ++i)
    {
        gumballMachine.TurnCrank();
        expectedString += "You turned...\nA gumball comes rolling out the slot...\n";
    }
    expectedString += "Oops, out of gumballs\nReturn all quarters\n";

    EXPECT_EQ(testOutput.str(), expectedString);
}

// Тесты для SoldOutState
TEST_F(NaiveMultiGumballMachineTest, SoldOutState_InsertQuarter) {
    std::string expectedString;
    for (int i = 0; i < 5; ++i)
    {
        gumballMachine.InsertQuarter();
        gumballMachine.TurnCrank();
        expectedString += "You inserted a quarter\n";
        expectedString += "You turned...\nA gumball comes rolling out the slot...\n";
    }
    expectedString += "Oops, out of gumballs\nReturn all quarters\n";
    gumballMachine.InsertQuarter();
    expectedString += "You can't insert a quarter, the machine is sold out\n";

    EXPECT_EQ(testOutput.str(), expectedString);
}

TEST_F(NaiveMultiGumballMachineTest, SoldOutState_EjectQuarter) {
    std::string expectedString;
    for (int i = 0; i < 5; ++i)
    {
        gumballMachine.InsertQuarter();
        gumballMachine.TurnCrank();
        expectedString += "You inserted a quarter\n";
        expectedString += "You turned...\nA gumball comes rolling out the slot...\n";
    }
    expectedString += "Oops, out of gumballs\nReturn all quarters\n";
    gumballMachine.EjectQuarter();
    expectedString += "You can't eject, you haven't inserted a quarter yet\n";

    EXPECT_EQ(testOutput.str(), expectedString);
}

TEST_F(NaiveMultiGumballMachineTest, Refill_SoldOutState) {
    std::string expectedString;

    for (int i = 0; i < 5; ++i)
    {
        gumballMachine.InsertQuarter();
        expectedString += "You inserted a quarter\n";
        gumballMachine.TurnCrank();
        expectedString += "You turned...\nA gumball comes rolling out the slot...\n";
    }
    gumballMachine.Refill(0);
    expectedString += "Oops, out of gumballs\nReturn all quarters\nAdded gumball\n";
    gumballMachine.TurnCrank();
    expectedString += "You turned but there's no gumballs\n";
    EXPECT_EQ(testOutput.str(), expectedString);

    gumballMachine.Refill(1);
    expectedString += "Added gumball\n";
    gumballMachine.TurnCrank();
    expectedString += "You turned but there's no quarter\n";
    EXPECT_EQ(testOutput.str(), expectedString);

}

// Проверка на возврат всех монеток после последнего шарика
TEST_F(NaiveMultiGumballMachineTest, ReturnQuartersAfterLastBall) {
    for (int i = 0; i < 3; ++i)
    {
        gumballMachine.InsertQuarter();
        gumballMachine.TurnCrank();
    }
    EXPECT_EQ(gumballMachine.ToString().find("You can return your quarters now."), std::string::npos);

    for (int i = 0; i < 2; ++i)
    {
        gumballMachine.InsertQuarter();
        gumballMachine.TurnCrank();
    }

    EXPECT_EQ(gumballMachine.ToString().find("You can return your quarters now."), std::string::npos);

    for (int i = 0; i < 3; ++i)
    {
        gumballMachine.InsertQuarter();
        gumballMachine.TurnCrank();
    }

    EXPECT_EQ(gumballMachine.ToString().find("You can return your quarters now."), std::string::npos);
}


// Тесты для мульти машины

class MultiGumballMachine : public ::testing::Test
{
protected:
    multiGumballMachine::MultiGumballMachine gumballMachine{5};
    std::streambuf* originalCout{};
    std::ostringstream testOutput;

    void SetUp() override
    {
        originalCout = std::cout.rdbuf(testOutput.rdbuf());
    }

    void TearDown() override
    {
        std::cout.rdbuf(originalCout);
    }
};

// Тесты для NoQuarterState
TEST_F(MultiGumballMachine, InitialState) {
    EXPECT_EQ(gumballMachine.ToString(), R"(
Mighty Gumball, Inc.
C++-enabled Standing Gumball Model #2016
Inventory: 5 gumballs
Machine is waiting for quarter
)");
}

TEST_F(MultiGumballMachine, InsertQuarter_NoQuarterState) {
    gumballMachine.InsertQuarter();
    EXPECT_EQ(testOutput.str(), "You inserted a quarter\n");
}

TEST_F(MultiGumballMachine, InsertQuarter_TooManyQuarters) {
    std::string expectedString;
    for (int i = 0; i < 5; ++i)
    {
        gumballMachine.InsertQuarter();
        if (i == 0)
        {
            expectedString += "You inserted a quarter\n";
        }
        else
        {
            expectedString += "You inserted another quarter\n";
        }
    }
    gumballMachine.InsertQuarter();
    expectedString += "You can't insert another quarter\n";

    EXPECT_EQ(testOutput.str(), expectedString);
}

TEST_F(MultiGumballMachine, EjectQuarter_NoQuarterState) {
    gumballMachine.EjectQuarter();
    EXPECT_EQ(testOutput.str(), "You haven't inserted a quarter\n");
}

TEST_F(MultiGumballMachine, EjectQuarter_HasQuarterState) {
    gumballMachine.InsertQuarter();
    gumballMachine.EjectQuarter();
    EXPECT_EQ(testOutput.str(), "You inserted a quarter\nReturn all quarters\n");
}

TEST_F(MultiGumballMachine, TurnCrank_NoQuarterState) {
    gumballMachine.TurnCrank();
    EXPECT_EQ(testOutput.str(), "You turned but there's no quarter\nYou need to pay first\n");
}

TEST_F(MultiGumballMachine, Refill_NoQuarterState) {
    std::string expectedString;
    gumballMachine.Refill(5);
    expectedString += "Added gumball\n";
    EXPECT_EQ(testOutput.str(), expectedString);
}

// Тесты для HasQuarterState
TEST_F(MultiGumballMachine, TurnCrank_HasQuarterState) {
    gumballMachine.InsertQuarter();
    gumballMachine.TurnCrank();
    EXPECT_EQ(testOutput.str(), "You inserted a quarter\nYou turned...\nA gumball comes rolling out the slot...\n");
}

TEST_F(MultiGumballMachine, TurnCrank_SoldOutAfterDispense) {
    std::string expectedString;
    for (int i = 0; i < 5; ++i)
    {
        gumballMachine.InsertQuarter();
        gumballMachine.TurnCrank();
        expectedString += "You inserted a quarter\n";
        expectedString += "You turned...\nA gumball comes rolling out the slot...\n";
    }
    expectedString += "Oops, out of gumballs\n";
    gumballMachine.TurnCrank();
    expectedString += "You turned but there's no gumballs\nNo gumball dispensed\n";

    EXPECT_EQ(testOutput.str(), expectedString);
}

TEST_F(MultiGumballMachine, Refill_HasQuarterState) {
    std::string expectedString;
    gumballMachine.InsertQuarter();
    expectedString += "You inserted a quarter\n";
    gumballMachine.Refill(5);
    expectedString += "Added gumball\n";
    EXPECT_EQ(testOutput.str(), expectedString);
}

// Тесты для SoldOutState
TEST_F(MultiGumballMachine, SoldOutState_InsertQuarter) {
    std::string expectedString;
    for (int i = 0; i < 5; ++i)
    {
        gumballMachine.InsertQuarter();
        gumballMachine.TurnCrank();
        expectedString += "You inserted a quarter\n";
        expectedString += "You turned...\nA gumball comes rolling out the slot...\n";
    }
    expectedString += "Oops, out of gumballs\n";
    gumballMachine.InsertQuarter();
    expectedString += "You can't insert a quarter, the machine is sold out\n";

    EXPECT_EQ(testOutput.str(), expectedString);
}

TEST_F(MultiGumballMachine, SoldOutState_EjectQuarter) {
    std::string expectedString;
    for (int i = 0; i < 5; ++i)
    {
        gumballMachine.InsertQuarter();
        gumballMachine.TurnCrank();
        expectedString += "You inserted a quarter\n";
        expectedString += "You turned...\nA gumball comes rolling out the slot...\n";
    }
    expectedString += "Oops, out of gumballs\n";
    gumballMachine.EjectQuarter();
    expectedString += "You can't eject, you haven't inserted a quarter yet\n";

    EXPECT_EQ(testOutput.str(), expectedString);
}

// Тесты для SoldState
TEST_F(MultiGumballMachine, SoldState_Dispense)
{
    std::string expectedString;
    expectedString += "You inserted a quarter\n";
    for (int i = 0; i < 5; ++i)
    {
        gumballMachine.InsertQuarter();
        if (i >= 1)
        {
            expectedString += "You inserted another quarter\n";
        }
    }
    for (int i = 0; i < 2; ++i)
    {
        gumballMachine.TurnCrank();
        expectedString += "You turned...\nA gumball comes rolling out the slot...\n";
    }
    for (int i = 0; i < 2; ++i)
    {
        gumballMachine.InsertQuarter();
        expectedString += "You inserted another quarter\n";
    }
    for (int i = 0; i < 3; ++i)
    {
        gumballMachine.TurnCrank();
        expectedString += "You turned...\nA gumball comes rolling out the slot...\n";
    }
    expectedString += "Oops, out of gumballs\n";

    EXPECT_EQ(testOutput.str(), expectedString);
}

TEST_F(MultiGumballMachine, Refill_SoldOutState) {
    std::string expectedString;
    expectedString += "You inserted a quarter\n";
    for (int i = 0; i < 5; ++i)
    {
        gumballMachine.InsertQuarter();
        if (i >= 1)
        {
            expectedString += "You inserted another quarter\n";
        }
    }
    for (int i = 0; i < 2; ++i)
    {
        gumballMachine.TurnCrank();
        expectedString += "You turned...\nA gumball comes rolling out the slot...\n";
    }
    for (int i = 0; i < 2; ++i)
    {
        gumballMachine.InsertQuarter();
        expectedString += "You inserted another quarter\n";
    }
    for (int i = 0; i < 3; ++i)
    {
        gumballMachine.TurnCrank();
        expectedString += "You turned...\nA gumball comes rolling out the slot...\n";
    }
    expectedString += "Oops, out of gumballs\n";
    gumballMachine.Refill(0);
    expectedString += "Added gumball\n";
    gumballMachine.TurnCrank();
    expectedString += "You turned but there's no gumballs\nNo gumball dispensed\n";
    gumballMachine.Refill(1);
    expectedString += "Added gumball\n";
    gumballMachine.TurnCrank();
    expectedString += "You turned...\nA gumball comes rolling out the slot...\nOops, out of gumballs\n";

    EXPECT_EQ(testOutput.str(), expectedString);
}

// Проверка на возврат всех монеток после последнего шарика
TEST_F(MultiGumballMachine, ReturnQuartersAfterLastBall) {
    for (int i = 0; i < 3; ++i)
    {
        gumballMachine.InsertQuarter();
        gumballMachine.TurnCrank();
    }
    EXPECT_EQ(gumballMachine.ToString().find("You can return your quarters now."), std::string::npos);

    for (int i = 0; i < 2; ++i)
    {
        gumballMachine.InsertQuarter();
        gumballMachine.TurnCrank();
    }

    EXPECT_EQ(gumballMachine.ToString().find("You can return your quarters now."), std::string::npos);

    for (int i = 0; i < 3; ++i)
    {
        gumballMachine.InsertQuarter();
        gumballMachine.TurnCrank();
    }

    EXPECT_EQ(gumballMachine.ToString().find("You can return your quarters now."), std::string::npos);
}

// Тесты состояний через MockGumballMachine
// NoQuarterState
TEST_F(MultiGumballMachine, Mock_NoQuarterState_InsertQuarter)
{
    MockMultiGumballMachine mockMultiGumballMachine;
    multiGumballMachine::NoQuarterState state = multiGumballMachine::NoQuarterState(mockMultiGumballMachine);

    EXPECT_CALL(mockMultiGumballMachine, AddQuarter()).Times(1);
    EXPECT_CALL(mockMultiGumballMachine, SetHasQuarterState()).Times(1);

    state.InsertQuarter();
    EXPECT_EQ(testOutput.str(), "You inserted a quarter\n");
}

TEST_F(MultiGumballMachine, Mock_NoQuarterState_EjectQuarter)
{
    MockMultiGumballMachine mockMultiGumballMachine;
    multiGumballMachine::NoQuarterState state = multiGumballMachine::NoQuarterState(mockMultiGumballMachine);

    state.EjectQuarter();
    EXPECT_EQ(testOutput.str(), "You haven't inserted a quarter\n");
}

TEST_F(MultiGumballMachine, Mock_NoQuarterState_TurnCrank)
{
    MockMultiGumballMachine mockMultiGumballMachine;
    multiGumballMachine::NoQuarterState state = multiGumballMachine::NoQuarterState(mockMultiGumballMachine);

    state.TurnCrank();
    EXPECT_EQ(testOutput.str(), "You turned but there's no quarter\n");
}

TEST_F(MultiGumballMachine, Mock_NoQuarterState_Dispense)
{
    MockMultiGumballMachine mockMultiGumballMachine;
    multiGumballMachine::NoQuarterState state = multiGumballMachine::NoQuarterState(mockMultiGumballMachine);

    state.Dispense();
    EXPECT_EQ(testOutput.str(), "You need to pay first\n");
}

TEST_F(MultiGumballMachine, Mock_NoQuarterState_ToString)
{
    MockMultiGumballMachine mockMultiGumballMachine;
    multiGumballMachine::NoQuarterState state = multiGumballMachine::NoQuarterState(mockMultiGumballMachine);

    std::string actualString = state.ToString();
    EXPECT_EQ(actualString, "waiting for quarter");
}

TEST_F(MultiGumballMachine, Mock_NoQuarterState_Refill)
{
    MockMultiGumballMachine mockMultiGumballMachine;
    multiGumballMachine::NoQuarterState state = multiGumballMachine::NoQuarterState(mockMultiGumballMachine);

    EXPECT_CALL(mockMultiGumballMachine, RefillBall(1)).Times(1);

    state.Refill(1);
    EXPECT_EQ(testOutput.str(), "Added gumball\n");
}

// HasQuarterState
TEST_F(MultiGumballMachine, Mock_HasQuarterState_InsertQuarter)
{
    MockMultiGumballMachine mockMultiGumballMachine;
    multiGumballMachine::HasQuarterState state = multiGumballMachine::HasQuarterState(mockMultiGumballMachine);

    EXPECT_CALL(mockMultiGumballMachine, GetQuarterCount()).WillOnce(Return(1));
    EXPECT_CALL(mockMultiGumballMachine, GetMaxQuarterCount()).WillOnce(Return(5));
    EXPECT_CALL(mockMultiGumballMachine, AddQuarter()).Times(1);

    state.InsertQuarter();
    EXPECT_EQ(testOutput.str(), "You inserted another quarter\n");

    EXPECT_CALL(mockMultiGumballMachine, GetQuarterCount()).WillOnce(Return(5));
    EXPECT_CALL(mockMultiGumballMachine, GetMaxQuarterCount()).WillOnce(Return(5));

    state.InsertQuarter();
    EXPECT_EQ(testOutput.str(), "You inserted another quarter\nYou can't insert another quarter\n");
}

TEST_F(MultiGumballMachine, Mock_HasQuarterState_EjectQuarter)
{
    MockMultiGumballMachine mockMultiGumballMachine;
    multiGumballMachine::HasQuarterState state = multiGumballMachine::HasQuarterState(mockMultiGumballMachine);

    EXPECT_CALL(mockMultiGumballMachine, ReturnAllQuarters).Times(1);
    EXPECT_CALL(mockMultiGumballMachine, SetNoQuarterState).Times(1);

    state.EjectQuarter();
}

TEST_F(MultiGumballMachine, Mock_HasQuarterState_TurnCrank)
{
    MockMultiGumballMachine mockMultiGumballMachine;
    multiGumballMachine::HasQuarterState state = multiGumballMachine::HasQuarterState(mockMultiGumballMachine);

    EXPECT_CALL(mockMultiGumballMachine, GetQuarterCount).WillOnce(Return(0));
    EXPECT_CALL(mockMultiGumballMachine, SetNoQuarterState).Times(1);

    state.TurnCrank();
    EXPECT_EQ(testOutput.str(), "No quarters left.\n");

    EXPECT_CALL(mockMultiGumballMachine, GetQuarterCount).WillOnce(Return(1));
    EXPECT_CALL(mockMultiGumballMachine, SetSoldState).Times(1);

    state.TurnCrank();
    EXPECT_EQ(testOutput.str(), "No quarters left.\nYou turned...\n");
}

TEST_F(MultiGumballMachine, Mock_HasQuarterState_Dispense)
{
    MockMultiGumballMachine mockMultiGumballMachine;
    multiGumballMachine::HasQuarterState state = multiGumballMachine::HasQuarterState(mockMultiGumballMachine);

    state.Dispense();
    EXPECT_EQ(testOutput.str(), "No gumball dispensed\n");
}

TEST_F(MultiGumballMachine, Mock_HasQuarterState_ToString)
{
    MockMultiGumballMachine mockMultiGumballMachine;
    multiGumballMachine::HasQuarterState state = multiGumballMachine::HasQuarterState(mockMultiGumballMachine);

    std::string actualString = state.ToString();
    EXPECT_EQ(actualString, "waiting for turn of crank");
}

TEST_F(MultiGumballMachine, Mock_HasQuarterState_Refill)
{
    MockMultiGumballMachine mockMultiGumballMachine;
    multiGumballMachine::HasQuarterState state = multiGumballMachine::HasQuarterState(mockMultiGumballMachine);

    EXPECT_CALL(mockMultiGumballMachine, RefillBall(1)).Times(1);

    state.Refill(1);
    EXPECT_EQ(testOutput.str(), "Added gumball\n");
}

// SoldState
TEST_F(MultiGumballMachine, Mock_SoldState_InsertQuarter)
{
    MockMultiGumballMachine mockMultiGumballMachine;
    multiGumballMachine::SoldState state = multiGumballMachine::SoldState(mockMultiGumballMachine);

    state.InsertQuarter();
    EXPECT_EQ(testOutput.str(), "Please wait, we're already giving you a gumball\n");
}

TEST_F(MultiGumballMachine, Mock_SoldState_EjectQuarter)
{
    MockMultiGumballMachine mockMultiGumballMachine;
    multiGumballMachine::SoldState state = multiGumballMachine::SoldState(mockMultiGumballMachine);

    state.EjectQuarter();
    EXPECT_EQ(testOutput.str(), "Sorry you already turned the crank\n");
}

TEST_F(MultiGumballMachine, Mock_SoldState_TurnCrank)
{
    MockMultiGumballMachine mockMultiGumballMachine;
    multiGumballMachine::SoldState state = multiGumballMachine::SoldState(mockMultiGumballMachine);

    state.TurnCrank();
    EXPECT_EQ(testOutput.str(), "Turning twice doesn't get you another gumball\n");
}

TEST_F(MultiGumballMachine, Mock_SoldState_Dispense)
{
    MockMultiGumballMachine mockMultiGumballMachine;
    multiGumballMachine::SoldState state = multiGumballMachine::SoldState(mockMultiGumballMachine);

    EXPECT_CALL(mockMultiGumballMachine, ReleaseBall).Times(1);
    EXPECT_CALL(mockMultiGumballMachine, GetBallCount()).WillOnce(Return(0));
    EXPECT_CALL(mockMultiGumballMachine, SetSoldOutState).Times(1);
    state.Dispense();
    EXPECT_EQ(testOutput.str(), "Oops, out of gumballs\n");

    EXPECT_CALL(mockMultiGumballMachine, ReleaseBall).Times(1);
    EXPECT_CALL(mockMultiGumballMachine, GetBallCount()).WillOnce(Return(1));
    EXPECT_CALL(mockMultiGumballMachine, GetQuarterCount()).WillOnce(Return(1));
    EXPECT_CALL(mockMultiGumballMachine, SetHasQuarterState).Times(1);
    state.Dispense();

    EXPECT_CALL(mockMultiGumballMachine, ReleaseBall).Times(1);
    EXPECT_CALL(mockMultiGumballMachine, GetBallCount()).WillOnce(Return(1));
    EXPECT_CALL(mockMultiGumballMachine, GetQuarterCount()).WillOnce(Return(0));
    EXPECT_CALL(mockMultiGumballMachine, SetNoQuarterState).Times(1);
    state.Dispense();
}

TEST_F(MultiGumballMachine, Mock_SoldState_ToString)
{
    MockMultiGumballMachine mockMultiGumballMachine;
    multiGumballMachine::SoldState state = multiGumballMachine::SoldState(mockMultiGumballMachine);

    std::string actualString = state.ToString();
    EXPECT_EQ(actualString, "delivering a gumball");
}

TEST_F(MultiGumballMachine, Mock_SoldState_Refill)
{
    MockMultiGumballMachine mockMultiGumballMachine;
    multiGumballMachine::SoldState state = multiGumballMachine::SoldState(mockMultiGumballMachine);

    state.Refill(1);
    EXPECT_EQ(testOutput.str(), "Not added gumball when giving giving you a gumball\n");
}

// SoldOutState
TEST_F(MultiGumballMachine, Mock_SoldOutState_InsertQuarter)
{
    MockMultiGumballMachine mockMultiGumballMachine;
    multiGumballMachine::SoldOutState state = multiGumballMachine::SoldOutState(mockMultiGumballMachine);

    state.InsertQuarter();
    EXPECT_EQ(testOutput.str(), "You can't insert a quarter, the machine is sold out\n");
}

TEST_F(MultiGumballMachine, Mock_SoldOutState_EjectQuarter)
{
    MockMultiGumballMachine mockMultiGumballMachine;
    multiGumballMachine::SoldOutState state = multiGumballMachine::SoldOutState(mockMultiGumballMachine);

    EXPECT_CALL(mockMultiGumballMachine, GetQuarterCount()).WillOnce(Return(0));
    state.EjectQuarter();
    EXPECT_EQ(testOutput.str(), "You can't eject, you haven't inserted a quarter yet\n");

    EXPECT_CALL(mockMultiGumballMachine, GetQuarterCount()).WillOnce(Return(1));
    EXPECT_CALL(mockMultiGumballMachine, ReturnAllQuarters).Times(1);
    state.EjectQuarter();
}

TEST_F(MultiGumballMachine, Mock_SoldOutState_TurnCrank)
{
    MockMultiGumballMachine mockMultiGumballMachine;
    multiGumballMachine::SoldOutState state = multiGumballMachine::SoldOutState(mockMultiGumballMachine);

    state.TurnCrank();
    EXPECT_EQ(testOutput.str(), "You turned but there's no gumballs\n");
}

TEST_F(MultiGumballMachine, Mock_SoldOutState_Dispense)
{
    MockMultiGumballMachine mockMultiGumballMachine;
    multiGumballMachine::SoldOutState state = multiGumballMachine::SoldOutState(mockMultiGumballMachine);

    state.Dispense();
    EXPECT_EQ(testOutput.str(), "No gumball dispensed\n");
}

TEST_F(MultiGumballMachine, Mock_SoldOutState_ToString)
{
    MockMultiGumballMachine mockMultiGumballMachine;
    multiGumballMachine::SoldOutState state = multiGumballMachine::SoldOutState(mockMultiGumballMachine);

    std::string actualString = state.ToString();
    EXPECT_EQ(actualString, "sold out");
}

TEST_F(MultiGumballMachine, Mock_SoldOutState_Refill)
{
    MockMultiGumballMachine mockMultiGumballMachine;
    multiGumballMachine::SoldOutState state = multiGumballMachine::SoldOutState(mockMultiGumballMachine);

    EXPECT_CALL(mockMultiGumballMachine, RefillBall(1)).Times(1);
    EXPECT_CALL(mockMultiGumballMachine, GetBallCount()).WillOnce(Return(0));
    state.Refill(1);
    EXPECT_EQ(testOutput.str(), "Added gumball\n");

    EXPECT_CALL(mockMultiGumballMachine, RefillBall(0)).Times(1);
    EXPECT_CALL(mockMultiGumballMachine, GetBallCount()).WillOnce(Return(1));
    EXPECT_CALL(mockMultiGumballMachine, GetQuarterCount()).WillOnce(Return(1));
    EXPECT_CALL(mockMultiGumballMachine, SetHasQuarterState).Times(1);
    state.Refill(0);

    EXPECT_CALL(mockMultiGumballMachine, RefillBall(0)).Times(1);
    EXPECT_CALL(mockMultiGumballMachine, GetBallCount()).WillOnce(Return(1));
    EXPECT_CALL(mockMultiGumballMachine, GetQuarterCount()).WillOnce(Return(0));
    EXPECT_CALL(mockMultiGumballMachine, SetNoQuarterState).Times(1);
    state.Refill(0);
}

GTEST_API_ int main(int argc, char **argv) {
    std::cout << "Running tests" << std::endl;
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}