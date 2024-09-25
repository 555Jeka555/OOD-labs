#ifndef INC_2_WEATHERDATA_H
#define INC_2_WEATHERDATA_H

#pragma once
#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>
#include "Observer.h"

struct SWeatherInfo
{
    double temperature = 0;
    double humidity = 0;
    double pressure = 0;
};

class CDisplay: public IObserver<SWeatherInfo>
{
private:
    /* Метод Update сделан приватным, чтобы ограничить возможность его вызова напрямую
        Классу CObservable он будет доступен все равно, т.к. в интерфейсе IObserver он
        остается публичным
    */
    void Update(SWeatherInfo const& data) override
    {
        std::cout << "Current Temp " << data.temperature << std::endl;
        std::cout << "Current Hum " << data.humidity << std::endl;
        std::cout << "Current Pressure " << data.pressure << std::endl;
        std::cout << "----------------" << std::endl;
    }
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

class CStatsDisplay : public IObserver<SWeatherInfo>
{
private:
    /* Метод Update сделан приватным, чтобы ограничить возможность его вызова напрямую
    Классу CObservable он будет доступен все равно, т.к. в интерфейсе IObserver он
    остается публичным
    */
    void Update(SWeatherInfo const& data) override
    {
        m_statisticsTemperature.Update(data.temperature);
        m_statisticsHumidity.Update(data.humidity);
        m_statisticsPressure.Update(data.pressure);

        std::cout << "Max Temp " << m_statisticsTemperature.GetMax() << std::endl;
        std::cout << "Min Temp " << m_statisticsTemperature.GetMin() << std::endl;
        std::cout << "Average Temp " << m_statisticsTemperature.GetAverage() << std::endl;

        std::cout << "Max Hum " << m_statisticsHumidity.GetMax() << std::endl;
        std::cout << "Min Hum " << m_statisticsHumidity.GetMin() << std::endl;
        std::cout << "Average Hum " << m_statisticsHumidity.GetAverage() << std::endl;

        std::cout << "Max Pressure " << m_statisticsPressure.GetMax() << std::endl;
        std::cout << "Min Pressure " << m_statisticsPressure.GetMin() << std::endl;
        std::cout << "Average Pressure " << m_statisticsPressure.GetAverage() << std::endl;

        std::cout << "----------------" << std::endl;
    }

    CStatistics m_statisticsTemperature;
    CStatistics m_statisticsHumidity;
    CStatistics m_statisticsPressure;
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

    void MeasurementsChanged()
    {
        NotifyObservers();
    }

    void SetMeasurements(double temp, double humidity, double pressure)
    {
        m_humidity = humidity;
        m_temperature = temp;
        m_pressure = pressure;

        MeasurementsChanged();
    }
protected:
    SWeatherInfo GetChangedData()const override
    {
        SWeatherInfo info;
        info.temperature = GetTemperature();
        info.humidity = GetHumidity();
        info.pressure = GetPressure();
        return info;
    }
private:
    double m_temperature = 0.0;
    double m_humidity = 0.0;
    double m_pressure = 760.0;
};

#endif //INC_2_WEATHERDATA_H
