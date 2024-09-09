#include <gtest/gtest.h>
#include <sstream>
#include "../../src/1_1/DuckFunctions.h"
#include "../../src/1_1/Duck/MallardDuck.h"
#include "../../src/1_1/Duck/RedheadDuck.h"
#include "../../src/1_1/Duck/ModelDuck.h"
#include "../../src/1_1/Duck/RubberDuck.h"

TEST (duck, dance_walts_mallard_duck_success)
{
    std::string expectedOutput = "I'm mallard duck\nQuack Quack!!!\nI'm flying with wings!!\nWaltz!!\n\n";

    std::ostringstream mockOutput;
    std::streambuf* originalCoutBuffer = std::cout.rdbuf(mockOutput.rdbuf());

    MallardDuck mallardDuck;
    PlayWithDuck(mallardDuck);

    std::cout.rdbuf(originalCoutBuffer);

    EXPECT_EQ(mockOutput.str(), expectedOutput);
}

TEST (duck, dance_minuet_red_head_duck_success)
{
    std::string expectedOutput = "I'm redhead duck\nQuack Quack!!!\nI'm flying with wings!!\nMinuet!!\n\n";

    std::ostringstream mockOutput;
    std::streambuf* originalCoutBuffer = std::cout.rdbuf(mockOutput.rdbuf());

    RedheadDuck redheadDuck;
    PlayWithDuck(redheadDuck);

    std::cout.rdbuf(originalCoutBuffer);

    EXPECT_EQ(mockOutput.str(), expectedOutput);
}

TEST (duck, no_dance_model_duck_success)
{
    std::string expectedOutput = "I'm model duck\nQuack Quack!!!\n\n";

    std::ostringstream mockOutput;
    std::streambuf* originalCoutBuffer = std::cout.rdbuf(mockOutput.rdbuf());

    ModelDuck modelDuck;
    PlayWithDuck(modelDuck);

    std::cout.rdbuf(originalCoutBuffer);

    EXPECT_EQ(mockOutput.str(), expectedOutput);
}

TEST (duck, no_dance_rubber_duck_success)
{
    std::string expectedOutput = "I'm rubber duck\nSqueek!!!\n\n";

    std::ostringstream mockOutput;
    std::streambuf* originalCoutBuffer = std::cout.rdbuf(mockOutput.rdbuf());

    RubberDuck rubberDuck;
    PlayWithDuck(rubberDuck);

    std::cout.rdbuf(originalCoutBuffer);

    EXPECT_EQ(mockOutput.str(), expectedOutput);
}

GTEST_API_ int main(int argc, char **argv) {
    std::cout << "Running tests" << std::endl;
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
