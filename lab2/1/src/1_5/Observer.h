#ifndef INC_5_OBSERVER_H
#define INC_5_OBSERVER_H

#pragma once

#include <set>
#include <unordered_set>
#include <map>
#include <unordered_map>

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
    virtual void Update(T const& data, const CObservable<T>* observable) = 0;
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
    virtual void RegisterObserver(IObserver<T> & observer, int priority) = 0;
    virtual void RemoveObserver(IObserver<T> & observer) = 0;

protected:
    virtual void NotifyObservers() = 0;
};

// Реализация интерфейса IObservable
template <class T>
class CObservable : public IObservable<T>
{
public:
    typedef IObserver<T> ObserverType;

    void RegisterObserver(ObserverType & observer, int priority) override
    {
        auto result = m_priorityToObservers.insert({priority, {}});
        result.first->second.insert(&observer);
        m_observerToPriority[&observer] = priority;
    }

    void RemoveObserver(ObserverType & observer) override
    {
        auto it = m_observerToPriority.find(&observer);
        if (it != m_observerToPriority.end())
        {
            int priority = it->second;
            m_priorityToObservers[priority].erase(&observer);

            if (m_priorityToObservers[priority].empty())
            {
                m_priorityToObservers.erase(priority);
            }

            m_observerToPriority.erase(it);
        }
    }

protected:
    void NotifyObservers()
    {
        T data = GetChangedData();
        auto observersCopy = m_priorityToObservers;
        for (auto it = observersCopy.rbegin(); it != observersCopy.rend(); ++it)
        {
            for (auto& observer : it->second)
            {
                observer->Update(data, this);
            }
        }
    }

    // Классы-наследники должны перегрузить данный метод,
    // в котором возвращать информацию об изменениях в объекте
    virtual T GetChangedData() const = 0;

private:
    std::map<int, std::unordered_set<ObserverType *>> m_priorityToObservers;
    std::unordered_map<ObserverType*, int> m_observerToPriority;
};

#endif //INC_5_OBSERVER_H