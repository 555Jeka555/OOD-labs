#ifndef INC_3_OBSERVER_H
#define INC_3_OBSERVER_H

#pragma once

#include <set>
#include <unordered_set>
#include <functional>

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
    virtual void Update(T const& data) = 0;
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
    virtual void RegisterObserver(IObserver<T> & observer, int priority = 0) = 0;
    virtual void NotifyObservers() = 0;
    virtual void RemoveObserver(IObserver<T> & observer) = 0;
};

// Реализация интерфейса IObservable
template <class T>
class CObservable : public IObservable<T>
{
public:
    typedef IObserver<T> ObserverType;

    void RegisterObserver(ObserverType & observer, int priority = 0) override
    {
        if (!m_priorityToObservers.contains(priority))
        {
            m_priorityToObservers.insert({priority, {}});
        }

        m_priorityToObservers.at(priority).insert(&observer);
    }

    void NotifyObservers() override
    {
        T data = GetChangedData();
        auto observersCopy = m_priorityToObservers;
        for (auto it = observersCopy.rbegin(); it != observersCopy.rend(); ++it)
        {
            for (auto& observer : it->second)
            {
                observer->Update(data);
            }
        }
    }

    void RemoveObserver(ObserverType & observer) override
    {
        for (auto& [priority, observers] : m_priorityToObservers)
        {
            if (observers.erase(&observer) > 0)
            {
                return;
            }
        }
    }

protected:
    // Классы-наследники должны перегрузить данный метод,
    // в котором возвращать информацию об изменениях в объекте
    virtual T GetChangedData()const = 0;

private:
    std::map<int, std::unordered_set<ObserverType *>> m_priorityToObservers;
};

#endif //INC_3_OBSERVER_H
