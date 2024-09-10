#include <gtest/gtest.h>
#include <sstream>
#include "../../src/2_1/DuckFunctions.h"
#include "../../src/2_1/Duck/MallardDuck.h"
#include "../../src/2_1/Duck/ModelDuck.h"
#include "../../src/2_1/Duck/Fly/FlyNoWay.h"

TEST (duck, departure_number_success)
{
    std::string expectedOutput = "I'm mallard duck\nQuack Quack!!!\nI'm flying with wings!! Departure number:1\nWaltz!!\n\n";

    std::ostringstream mockOutput;
    std::streambuf* originalCoutBuffer = std::cout.rdbuf(mockOutput.rdbuf());

    MallardDuck mallardDuck;
    PlayWithDuck(mallardDuck);

    std::cout.rdbuf(originalCoutBuffer);

    EXPECT_EQ(mockOutput.str(), expectedOutput);
}

TEST (duck, departure_number_no_fly_success)
{
    std::string expectedOutput = "I'm model duck\nQuack Quack!!!\n\n";

    std::ostringstream mockOutput;
    std::streambuf* originalCoutBuffer = std::cout.rdbuf(mockOutput.rdbuf());

    ModelDuck modelDuck;
    PlayWithDuck(modelDuck);

    std::cout.rdbuf(originalCoutBuffer);

    EXPECT_EQ(mockOutput.str(), expectedOutput);
}

TEST (duck, departure_number_change_strategy_no_fly_success)
{
    std::string expectedOutput = "I'm mallard duck\nQuack Quack!!!\nI'm flying with wings!! Departure number:1\nWaltz!!\n\n"
                                 "I'm mallard duck\nQuack Quack!!!\nWaltz!!\n\n";

    std::ostringstream mockOutput;
    std::streambuf* originalCoutBuffer = std::cout.rdbuf(mockOutput.rdbuf());

    MallardDuck mallardDuck;
    PlayWithDuck(mallardDuck);

    FlyNoWay flyNoWay;
    mallardDuck.SetFlyBehavior(std::make_unique<FlyNoWay>(flyNoWay));
    PlayWithDuck(mallardDuck);

    std::cout.rdbuf(originalCoutBuffer);

    EXPECT_EQ(mockOutput.str(), expectedOutput);
}

GTEST_API_ int main(int argc, char **argv) {
    std::cout << "Running tests" << std::endl;
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
