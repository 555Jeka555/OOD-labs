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

    PriorityObserver highPriorityObserver(1, callOrder);
    PriorityObserver lowPriorityObserver(2, callOrder);

    wd.RegisterObserver(highPriorityObserver, 5);
    wd.RegisterObserver(lowPriorityObserver, 1);

    wd.SetMeasurements(10, 0.8, 761);

    ASSERT_EQ(callOrder.size(), 2);

    EXPECT_LT(callOrder[0], callOrder[1]) << "High-priority observer should be called before low-priority observer";
}

GTEST_API_ int main(int argc, char **argv) {
    std::cout << "Running tests" << std::endl;
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
