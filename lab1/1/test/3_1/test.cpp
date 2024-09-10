#include <gtest/gtest.h>
#include <sstream>
#include "../../src/3_1/Duck/MallardDuck.h"
#include "../../src/3_1/Duck/RedHeadDuck.h"
#include "../../src/3_1/Duck/RubberDuck.h"
#include "../../src/3_1/DuckFunctions.h"

TEST (duck, mallard_duck_func_success)
{
    std::string expectedOutput = "I'm mallard duck\nWaltz!!\nI'm flying! Departure number:1\nQuack!\n\n";

    std::ostringstream mockOutput;
    std::streambuf* originalCoutBuffer = std::cout.rdbuf(mockOutput.rdbuf());

    MallardDuck mallardDuck;
    PlayWithDuck(mallardDuck);

    std::cout.rdbuf(originalCoutBuffer);

    EXPECT_EQ(mockOutput.str(), expectedOutput);
}

TEST (duck, red_head_duck_func_success)
{
    std::string expectedOutput = "I'm redhead duck\nMinuet!!\nI'm flying! Departure number:1\nQuack!\n\n";

    std::ostringstream mockOutput;
    std::streambuf* originalCoutBuffer = std::cout.rdbuf(mockOutput.rdbuf());

    RedHeadDuck readHeadDuck;
    PlayWithDuck(readHeadDuck);

    std::cout.rdbuf(originalCoutBuffer);

    EXPECT_EQ(mockOutput.str(), expectedOutput);
}

TEST (duck, no_fly_duck_func_success)
{
    std::string expectedOutput = "I'm rubber duck\nSqueak!\n\n";

    std::ostringstream mockOutput;
    std::streambuf* originalCoutBuffer = std::cout.rdbuf(mockOutput.rdbuf());

    RubberDuck rubberDuck;
    PlayWithDuck(rubberDuck);

    std::cout.rdbuf(originalCoutBuffer);

    EXPECT_EQ(mockOutput.str(), expectedOutput);
}

TEST (duck, change_strategy_no_fly_func_success)
{
    std::string expectedOutput = "I'm redhead duck\nMinuet!!\nI'm flying! Departure number:1\nQuack!\n\n"
                                 "I'm redhead duck\nMinuet!!\nQuack!\n\n";

    std::ostringstream mockOutput;
    std::streambuf* originalCoutBuffer = std::cout.rdbuf(mockOutput.rdbuf());

    RedHeadDuck readHeadDuck;
    PlayWithDuck(readHeadDuck);

    readHeadDuck.SetFlyBehavior(CreateFlyNoWay());
    PlayWithDuck(readHeadDuck);

    std::cout.rdbuf(originalCoutBuffer);

    EXPECT_EQ(mockOutput.str(), expectedOutput);
}


GTEST_API_ int main(int argc, char **argv) {
    std::cout << "Running tests" << std::endl;
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
