#ifndef INC_1_OBSERVER_H
#define INC_1_OBSERVER_H

#pragma once

#include <set>
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

// TODO Нужен ли IObservable. Да, для защиты от записи,
// интерфейс не должен содержать публичных методов уведомления -> генерация события (запись) была в методе NotifyObservers
// Чтобы любые IObserver могли подписаться на любой субъект реализованный IObservable
template <typename T>
class IObservable
{
public:
    virtual ~IObservable() = default;
    virtual void RegisterObserver(IObserver<T> & observer) = 0;
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

    void RegisterObserver(ObserverType & observer) override
    {
        m_observers.insert(&observer);
    }

    void RemoveObserver(ObserverType & observer) override
    {
        m_observers.erase(&observer);
    }

protected:
    void NotifyObservers()
    {
        T data = GetChangedData(); // Генерация события
        for (auto & observer : m_observers)
        {
            observer->Update(data);
        }
    }

    // Классы-наследники должны перегрузить данный метод,
    // в котором возвращать информацию об изменениях в объекте
    virtual T GetChangedData()const = 0;

private:
    std::set<ObserverType *> m_observers;
};

#endif //INC_1_OBSERVER_H
