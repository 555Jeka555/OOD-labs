#include <gtest/gtest.h>
#include "../src/1_2/Observer.h"
#include "../src/1_2/WeatherData.h"

class RemovingObserver : public IObserver<SWeatherInfo>
{
public:
    explicit RemovingObserver(CObservable<SWeatherInfo> &observable) : m_observable(observable)
    {
    }

    void Update(SWeatherInfo const &data) override
    {
        std::cout << "RemovingObserver received update." << std::endl;
        m_observable.RemoveObserver(*this);
    }

private:
    CObservable<SWeatherInfo> &m_observable;
};

TEST(ObserverTests, TestRemoveObserverDuringNotify)
{
    CWeatherData wd;

    CDisplay display1;
    wd.RegisterObserver(display1);
    RemovingObserver selfRemovingObserver(wd);
    wd.RegisterObserver(selfRemovingObserver);

    std::cout << "First measurement update:" << std::endl;
    wd.SetMeasurements(10, 0.8, 761);

    std::cout << "Second measurement update:" << std::endl;
    wd.SetMeasurements(15, 0.6, 765);

}

GTEST_API_ int main(int argc, char **argv) {
    std::cout << "Running tests" << std::endl;
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
