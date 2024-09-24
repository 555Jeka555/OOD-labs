#include <gtest/gtest.h>
#include "../src/1_3/Observer.h"
#include "../src/1_3/WeatherData.h"

class PriorityObserver : public IObserver<SWeatherInfo>
{
public:
    PriorityObserver(int id, std::vector<int>& callOrder)
            : m_id(id), m_callOrder(callOrder)
    {
    }

    void Update(SWeatherInfo const& data) override
    {
        m_callOrder.push_back(m_id);
    }

private:
    int m_id;
    std::vector<int>& m_callOrder;
};

TEST(observer_test3, priority_observer_success)
{
    CWeatherData wd;

    std::vector<int> callOrder;

    PriorityObserver highPriority(1, callOrder);
    PriorityObserver lowPriority(2, callOrder);

    wd.RegisterObserver(highPriority, 5);
    wd.RegisterObserver(lowPriority, 1);

    wd.SetMeasurements(5, 1, 761);

    ASSERT_EQ(callOrder.size(), 2);

    EXPECT_TRUE(callOrder[0] < callOrder[1]);
}

GTEST_API_ int main(int argc, char **argv) {
    std::cout << "Running tests" << std::endl;
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
