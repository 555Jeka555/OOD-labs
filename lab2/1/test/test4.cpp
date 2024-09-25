#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "../src/1_4/Observer.h"
#include "../src/1_4/WeatherData.h"

class MockDisplay : public IObserver<SWeatherInfo>
{
public:
    MOCK_METHOD(void, Update, (const SWeatherInfo& data, const CObservable<SWeatherInfo>* observable), (override));

    MockDisplay() = default;
};

TEST (observer_test4, duo_observable_success)
{
    CWeatherData weatherDataIn;
    CWeatherData weatherDataOut;
    MockDisplay mockDisplay;

    weatherDataIn.RegisterObserver(mockDisplay, 1);
    weatherDataOut.RegisterObserver(mockDisplay, 2);

    SWeatherInfo dataIn = {50.5, 0.5, 761.0};
    SWeatherInfo dataOut = {24, 0.75, 762.0};

    EXPECT_CALL(mockDisplay, Update(testing::_, &weatherDataIn)).Times(1);
    EXPECT_CALL(mockDisplay, Update(testing::_, &weatherDataOut)).Times(1);

    weatherDataIn.SetMeasurements(dataIn.temperature, dataIn.humidity, dataIn.pressure);
    weatherDataOut.SetMeasurements(dataOut.temperature, dataOut.humidity, dataOut.pressure);
}

GTEST_API_ int main(int argc, char **argv) {
    std::cout << "Running tests" << std::endl;
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
