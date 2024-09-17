#ifndef INC_1_DUCK_H
#define INC_1_DUCK_H

#include "functional"
#include "iostream"

class Duck
{
public:
    using FlyFunction = std::function<void()>;
    using DanceFunction = std::function<void()>;
    using QuackFunction = std::function<void()>;

    Duck(   FlyFunction flyFunction,
            DanceFunction danceFunction,
            QuackFunction quackFunction
            ) :
            m_flyFunction(std::move(flyFunction)),
            m_danceFunction(std::move(danceFunction)),
            m_quackFunction(std::move(quackFunction))
    {
        // Todo добавить ассерты
    }

    void Fly()
    {
        m_flyFunction();
    }

    void Dance()
    {
        m_danceFunction();
    }

    void Quack()
    {
        m_quackFunction();
    }

    virtual void Display() const = 0;

    void SetFlyBehavior(FlyFunction flyFunction)
    {
        m_flyFunction = std::move(flyFunction);
    }

    void SetDanceBehavior(DanceFunction danceFunction)
    {
        m_danceFunction = std::move(danceFunction);
    }

    void SetQuackBehavior(QuackFunction quackFunction)
    {
        m_quackFunction = std::move(quackFunction);
    }

private:
    FlyFunction m_flyFunction;
    DanceFunction m_danceFunction;
    QuackFunction m_quackFunction;
};

#endif //INC_1_DUCK_H
