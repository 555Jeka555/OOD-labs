#ifndef INC_7_OBSERVER_H
#define INC_7_OBSERVER_H

#pragma once

#include <set>
#include <unordered_set>
#include <map>
#include <unordered_map>

enum class EventType
{
    Temperature,
    Pressure,
    Humidity,
};

template <typename T>
class CObservable;

/*
Шаблонный интерфейс IObserver. Его должен реализовывать класс,
желающий получать уведомления от соответствующего IObservable
Параметром шаблона является тип аргумента,
передаваемого Наблюдателю в метод Update
*/
template <typename T>
class IObserver
{
public:
    virtual void Update(T const& data, EventType eventType) = 0;
    virtual ~IObserver() = default;
};

/*
Шаблонный интерфейс IObservable. Позволяет подписаться и отписаться на оповещения, а также
инициировать рассылку уведомлений зарегистрированным наблюдателям.
*/
template <typename T>
class IObservable
{
public:
    virtual ~IObservable() = default;
    virtual void RegisterObserver(IObserver<T> & observer, EventType eventType, int priority) = 0;
    virtual void RemoveObserver(IObserver<T> & observer, EventType eventType) = 0;

protected:
    virtual void NotifyObservers(EventType eventType) = 0;
};

// Реализация интерфейса IObservable
template <class T>
class CObservable : public IObservable<T>
{
public:
    typedef IObserver<T> ObserverType;

    void RegisterObserver(ObserverType & observer, EventType eventType, int priority) override
    {
        if (!m_observers.contains(eventType))
        {
            m_observers.insert({eventType, {}});
        }
        if (!m_observers.at(eventType).contains(priority))
        {
            m_observers.at(eventType).insert({priority, {}});
        }

        m_observers.at(eventType).at(priority).insert(&observer);
    }

    void RemoveObserver(ObserverType & observer, EventType eventType) override
    {
        for (auto& [priority, observers] : m_observers[eventType])
        {
            if (observers.erase(&observer))
            {
                return;
            }
        }
    }

protected:
    void NotifyObservers(EventType eventType)
    {
        T data = GetChangedData();
        auto observersCopy = m_observers;
        for (auto& [priority, observers] : m_observers[eventType])
        {
            for (auto& observer : observers)
            {
                observer->Update(data, eventType);
            }
        }
    }

    // Классы-наследники должны перегрузить данный метод,
    // в котором возвращать информацию об изменениях в объекте
    virtual T GetChangedData() const = 0;

private:
    std::map<EventType, std::map<int, std::unordered_set<ObserverType*>>> m_observers;
};

#endif //INC_7_OBSERVER_H