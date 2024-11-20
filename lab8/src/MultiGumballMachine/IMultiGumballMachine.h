#ifndef LAB8_IMULTIGUMBALLMACHINE_H
#define LAB8_IMULTIGUMBALLMACHINE_H

namespace multiGumballMachine
{
    class IMultiGumballMachine
    {
    public:
        virtual void ReleaseBall() = 0;
        [[nodiscard]] virtual unsigned GetBallCount()const = 0;
        [[nodiscard]] virtual unsigned GetQuarterCount() const = 0;
        [[nodiscard]] virtual unsigned GetMaxQuarterCount() const = 0;
        virtual void AddQuarter() = 0;
        virtual void ReturnAllQuarters() =0;

        virtual void SetSoldOutState() = 0;
        virtual void SetNoQuarterState() = 0;
        virtual void SetSoldState() = 0;
        virtual void SetHasQuarterState() = 0;

        virtual ~IMultiGumballMachine() = default;
    };
}

#endif //LAB8_IMULTIGUMBALLMACHINE_H
