#include <gtest/gtest.h>
#include <sstream>
#include "../../src/1_1/DuckFunctions.h"
#include "../../src/1_1/Duck/MallardDuck.h"
#include "../../src/1_1/Duck/RedheadDuck.h"
#include "../../src/1_1/Duck/ModelDuck.h"
#include "../../src/1_1/Duck/RubberDuck.h"

const std::string danceNoWayOutput;
const std::string danceMinuetOutput = "Minuet!!\n";
const std::string danceWaltzOutput = "Waltz!!\n";

void assertDance(Duck &duck, const std::string& danceOutput)
{
    std::stringstream buffer;
    std::cout.rdbuf(buffer.rdbuf());
    duck.Dance();
    ASSERT_EQ(buffer.str(), danceOutput);
}

TEST (dance, dance_with_mallard_duck)
{
    MallardDuck duck;
    assertDance(duck, danceWaltzOutput);
}

TEST (dance, dance_with_model_duck)
{
    ModelDuck duck;
    assertDance(duck, danceNoWayOutput);
}

TEST (dance, dance_with_readhead_duck)
{
    RedheadDuck duck;
    assertDance(duck, danceMinuetOutput);
}

TEST (dance, dance_with_rubber_duck)
{
    RubberDuck duck;
    assertDance(duck, danceNoWayOutput);
}

GTEST_API_ int main(int argc, char **argv) {
    std::cout << "Running tests" << std::endl;
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
