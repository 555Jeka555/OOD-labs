```mermaid
classDiagram
    Duck *-- IFlyBehavior
    Duck *-- IQuackBehavior
    Duck *-- IDanceBehavior

    Duck <|-- MallardDuck
    Duck <|-- ModelDuck
    Duck <|-- RedheadDuck
    Duck <|-- RubberDuck

    MallardDuck *-- FlyWithWings
    MallardDuck *-- QuackBehavior
    MallardDuck *-- DanceWaltzBehavior

    RedheadDuck *-- FlyWithWings
    RedheadDuck *-- QuackBehavior
    RedheadDuck *-- DanceMinuetBehavior

    ModelDuck *-- FlyNoWay
    ModelDuck *-- QuackBehavior
    ModelDuck *-- NoDanceBehavior

    ModelDuck *-- FlyNoWay
    ModelDuck *-- SqueakBehavior
    ModelDuck *-- NoDanceBehavior

    IFlyBehavior <|.. FlyNoWay
    IFlyBehavior <|.. FlyWithWings

    IQuackBehavior <|.. MuteQuackBehavior
    IQuackBehavior <|.. QuackBehavior
    IQuackBehavior <|.. SqueakBehavior

    IDanceBehavior <|.. DanceMinuetBehavior
    IDanceBehavior <|.. DanceWaltzBehavior
    IDanceBehavior <|.. NoDanceBehavior

    class Duck {
        + Quack()
        + Swim()
        + Fly()
        + Dance()
        + SetFlyBehavior(IFlyBehavior)
        + SetDanceBehavior(IDanceBehavior)
        + Display()
    }

    class MallardDuck {

    }

    class ModelDuck {

    }

    class RedheadDuck {

    }

    class RubberDuck {

    }

    class IFlyBehavior {
        + Fly()
    }

    class IQuackBehavior {
        + Quack()
    }

    class IDanceBehavior {
        + Dance()
    }
    
    class DanceMinuetBehavior {
        + Dance()
    }

    class DanceWaltzBehavior {
        + Dance()
    }

    class NoDanceBehavior {
        + Dance()
    }

    class MuteQuackBehavior {
        + Quack()
    }

    class QuackBehavior {
        + Quack()
    }

    class SqueakBehavior {
        + Quack()
    }

    class FlyNoWay {
        + Fly()
    }

    class FlyWithWings {
        + Fly()
    }

```

```mermaid
classDiagram
    Duck *-- IFlyBehavior
    Duck *-- IQuackBehavior
    Duck *-- IDanceBehavior

    Duck <|-- MallardDuck
    Duck <|-- ModelDuck
    Duck <|-- RedheadDuck
    Duck <|-- RubberDuck

    IFlyBehavior <|.. FlyNoWay
    IFlyBehavior <|.. FlyWithWings

    IQuackBehavior <|.. MuteQuackBehavior
    IQuackBehavior <|.. QuackBehavior
    IQuackBehavior <|.. SqueakBehavior

    IDanceBehavior <|.. DanceMinuetBehavior
    IDanceBehavior <|.. DanceWaltzBehavior
    IDanceBehavior <|.. NoDanceBehavior

    class Duck {
        + Quack()
        + Swim()
        + Fly()
        + Dance()
        + SetFlyBehavior(IFlyBehavior)
        + SetDanceBehavior(IDanceBehavior)
        + Display()
    }

    class MallardDuck {

    }

    class ModelDuck {

    }

    class RedheadDuck {

    }

    class RubberDuck {

    }

    class IFlyBehavior {
        + Fly()
    }

    class IQuackBehavior {
        + Quack()
    }

    class IDanceBehavior {
        + Dance()
    }
    
    class DanceMinuetBehavior {
        + Dance()
    }

    class DanceWaltzBehavior {
        + Dance()
    }

    class NoDanceBehavior {
        + Dance()
    }

    class MuteQuackBehavior {
        + Quack()
    }

    class QuackBehavior {
        + Quack()
    }

    class SqueakBehavior {
        + Quack()
    }

    class FlyNoWay {
        + Fly()
    }

    class FlyWithWings {
        + Fly()
    }

```
