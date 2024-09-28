#include "WeatherData.h"

int main()
{
    CWeatherData wd;

    CFishermanDisplay display;
    wd.RegisterObserver(display, EventType::Temperature, 5);

    wd.SetMeasurements(25, 0.4, 760);

    wd.SetMeasurements(10, 0.8, 761);

    return 0;
}

