#ifndef INC_5_WEATHERDATA_H
#define INC_5_WEATHERDATA_H

#pragma once
#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>
#include <cmath>
#include "Observer.h"

struct SWeatherInfo
{
    double temperature = 0;
    double humidity = 0;
    double pressure = 0;
    double windSpeed = 0;
    double windDirection = 0;
};

class CWindStatistics
{
public:
    void Update(double speed, double direction)
    {
        if (m_minSpeed > speed)
        {
            m_minSpeed = speed;
        }
        if (m_maxSpeed   < speed)
        {
            m_maxSpeed = speed;
        }
        m_totalSpeed += speed;

        double radianDirection = direction * M_PI / 180.0;

        double x = speed * cos(radianDirection);
        double y = speed * sin(radianDirection);

        m_sumX += x;
        m_sumY += y;
        ++m_count;
    }

    [[nodiscard]] double GetMaxSpeed() const
    {
        return m_maxSpeed;
    }

    [[nodiscard]] double GetMinSpeed() const
    {
        return m_minSpeed;
    }

    [[nodiscard]] double GetAverageSpeed() const
    {
        if (m_count == 0)
        {
            return 0;
        }

        return m_totalSpeed / m_count;
    }

    [[nodiscard]] double GetAverageDirection() const
    {
        if (m_count == 0)
        {
            return 0;
        }

        double averageDirection = atan2(m_sumY / m_count, m_sumX / m_count) * 180.0 / M_PI;
        return fmod(averageDirection + 360.0, 360.0);
    }

private:
    double m_totalSpeed = 0;
    double m_minSpeed = std::numeric_limits<double>::infinity();
    double m_maxSpeed = -std::numeric_limits<double>::infinity();
    double m_sumX = 0;
    double m_sumY = 0;
    unsigned m_count = 0;
};

class CStatistics
{
public:
    void Update(double value)
    {
        if (m_min > value)
        {
            m_min = value;
        }
        if (m_max < value)
        {
            m_max = value;
        }

        m_acc += value;
        m_countAcc++;
    }

    double GetMin() const
    {
        return m_min;
    }

    double GetMax() const
    {
        return m_max;
    }

    double GetAverage() const
    {
        return m_acc / static_cast<double>(m_countAcc);
    }

private:
    double m_min = std::numeric_limits<double>::infinity();
    double m_max = -std::numeric_limits<double>::infinity();
    double m_acc = 0;
    int m_countAcc = 0;
};

class CDisplay: public IObserver<SWeatherInfo>
{
public:
    CDisplay(
            CObservable<SWeatherInfo>* m_weatherDataIn,
            CObservable<SWeatherInfo>* m_weatherDataOut
        ) : m_weatherDataIn(m_weatherDataIn), m_weatherDataOut(m_weatherDataOut)
    {}

private:
    /* Метод Update сделан приватным, чтобы ограничить возможность его вызова напрямую
        Классу CObservable он будет доступен все равно, т.к. в интерфейсе IObserver он
        остается публичным
    */
    void Update(SWeatherInfo const& data, const CObservable<SWeatherInfo>* observable) override
    {
        std::string location = "unknown";
        if (observable == m_weatherDataIn)
        {
            location = "inside";
        }
        else if (observable == m_weatherDataOut)
        {
            location = "outside";
        }

        std::cout << "Current Location " << location << std::endl;
        std::cout << "Current Temp " << data.temperature << std::endl;
        std::cout << "Current Hum " << data.humidity << std::endl;
        std::cout << "Current Pressure " << data.pressure << std::endl;
        std::cout << "----------------" << std::endl;
    }

    const CObservable<SWeatherInfo>* m_weatherDataIn;
    const CObservable<SWeatherInfo>* m_weatherDataOut;
};

class CWeatherData;

class CStatsDisplayDuoPro : public IObserver<SWeatherInfo>
{
public:
    CStatsDisplayDuoPro(
            CObservable<SWeatherInfo>* m_weatherDataIn,
    CObservable<SWeatherInfo>* m_weatherDataOut
    ) : m_weatherDataIn(m_weatherDataIn), m_weatherDataOut(m_weatherDataOut)
    {}

private:
    /* Метод Update сделан приватным, чтобы ограничить возможность его вызова напрямую
    Классу CObservable он будет доступен все равно, т.к. в интерфейсе IObserver он
    остается публичным
    */
    void Update(SWeatherInfo const& data, const CObservable<SWeatherInfo>* observable) override
    {
        std::string location;

        if (observable == m_weatherDataIn)
        {
            location = "inside";
            m_statisticsTemperature.Update(data.temperature);
            m_statisticsHumidity.Update(data.humidity);
            m_statisticsPressure.Update(data.pressure);

            std::cout << "Current Location " << location << std::endl;

            std::cout << "Max Temp " << m_statisticsTemperature.GetMax() << std::endl;
            std::cout << "Min Temp " << m_statisticsTemperature.GetMin() << std::endl;
            std::cout << "Average Temp " << m_statisticsTemperature.GetAverage() << std::endl;

            std::cout << "Max Hum " << m_statisticsHumidity.GetMax() << std::endl;
            std::cout << "Min Hum " << m_statisticsHumidity.GetMin() << std::endl;
            std::cout << "Average Hum " << m_statisticsHumidity.GetAverage() << std::endl;

            std::cout << "Max Pressure " << m_statisticsPressure.GetMax() << std::endl;
            std::cout << "Min Pressure " << m_statisticsPressure.GetMin() << std::endl;
            std::cout << "Average Pressure " << m_statisticsPressure.GetAverage() << std::endl;
        }
        else if (observable == m_weatherDataOut)
        {
            location = "outside";
            m_statisticsTemperature.Update(data.temperature);
            m_statisticsHumidity.Update(data.humidity);
            m_statisticsPressure.Update(data.pressure);
            m_windStatistics.Update(data.windSpeed, data.windDirection);

            std::cout << "Current Location " << location << std::endl;

            std::cout << "Max Temp " << m_statisticsTemperature.GetMax() << std::endl;
            std::cout << "Min Temp " << m_statisticsTemperature.GetMin() << std::endl;
            std::cout << "Average Temp " << m_statisticsTemperature.GetAverage() << std::endl;

            std::cout << "Max Hum " << m_statisticsHumidity.GetMax() << std::endl;
            std::cout << "Min Hum " << m_statisticsHumidity.GetMin() << std::endl;
            std::cout << "Average Hum " << m_statisticsHumidity.GetAverage() << std::endl;

            std::cout << "Max Pressure " << m_statisticsPressure.GetMax() << std::endl;
            std::cout << "Min Pressure " << m_statisticsPressure.GetMin() << std::endl;
            std::cout << "Average Pressure " << m_statisticsPressure.GetAverage() << std::endl;

            std::cout << "Wind Speed Stats: Max " << m_windStatistics.GetMaxSpeed()
                      << ", Min " << m_windStatistics.GetMinSpeed()
                      << ", Avg " << m_windStatistics.GetAverageSpeed() << std::endl;

            std::cout << "Average Wind Direction: " << m_windStatistics.GetAverageDirection()
                      << " degrees" << std::endl;
        }
        else
        {
            std::cout << "Unknown weather stations" << std::endl;
        }

        std::cout << "----------------" << std::endl;
    }

    CStatistics m_statisticsTemperature;
    CStatistics m_statisticsHumidity;
    CStatistics m_statisticsPressure;
    CWindStatistics m_windStatistics;

    const CObservable<SWeatherInfo>* m_weatherDataIn;
    const CObservable<SWeatherInfo>* m_weatherDataOut;
};

class CWeatherData : public CObservable<SWeatherInfo>
{
public:
    // Температура в градусах Цельсия
    double GetTemperature()const
    {
        return m_temperature;
    }
    // Относительная влажность (0...100)
    double GetHumidity()const
    {
        return m_humidity;
    }
    // Атмосферное давление (в мм.рт.ст)
    double GetPressure()const
    {
        return m_pressure;
    }

    double GetWindSpeed()const
    {
        return m_windSpeed;
    }

    double GetWindDirection()const
    {
        return m_windDirection;
    }

    void MeasurementsChanged()
    {
        NotifyObservers();
    }

    void SetMeasurements(double temp, double humidity, double pressure, double windSpeed = 0, double windDirection = 0)
    {
        m_humidity = humidity;
        m_temperature = temp;
        m_pressure = pressure;
        m_windSpeed = windSpeed;
        m_windDirection = windDirection;

        MeasurementsChanged();
    }
protected:
    SWeatherInfo GetChangedData()const override
    {
        SWeatherInfo info;
        info.temperature = GetTemperature();
        info.humidity = GetHumidity();
        info.pressure = GetPressure();
        info.windSpeed = GetWindSpeed();
        info.windDirection = GetWindDirection();
        return info;
    }
private:
    double m_temperature = 0.0;
    double m_humidity = 0.0;
    double m_pressure = 760.0;
    double m_windSpeed = 0.0;
    double m_windDirection = 0.0;
};

#endif //INC_5_WEATHERDATA_H
