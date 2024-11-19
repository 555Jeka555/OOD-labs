#include <gtest/gtest.h>
#include "../src/WithState/GumballMachine.h"
#include "../src/MultiGumballMachine/Naive/GumballMachine.h"
#include "../src/MultiGumballMachine/MultiGumballMachine.h"

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


// Тесты для наивной мульти машины

class NaiveMultiGumballMachineTest : public ::testing::Test {
protected:
    multiNaive::GumballMachine gumballMachine{5};
    std::streambuf* originalCout;
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
    expectedString += "Oops, out of gumballs\n";
    gumballMachine.TurnCrank();
    expectedString += "You turned but there's no gumballs\n";

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
    expectedString += "Oops, out of gumballs\n";
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
    expectedString += "Oops, out of gumballs\n";
    gumballMachine.EjectQuarter();
    expectedString += "You can't eject, you haven't inserted a quarter yet\n";

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

GTEST_API_ int main(int argc, char **argv) {
    std::cout << "Running tests" << std::endl;
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}