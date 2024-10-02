```mermaid
classDiagram
    ICompoment <|.. Component

    ICompoment <|.. ComponentDecorator
    ComponentDecorator o-- ICompoment

    ComponentDecorator <|-- ComponentDecoratorA
    ComponentDecorator <|-- ComponentDecoratorB

    class ICompoment {
        + Operation()
    }

    class Component {
        + Operation()
    }

    class ComponentDecorator {
        + Operation()
        - ICompomemt m_component
    }

    class ComponentDecoratorA {
        + Operation()
        - SomeA()
    }

    class ComponentDecoratorB {
        + Operation()
        - SomeB()
    }
```

```mermaid
classDiagram

    IBeverage <|.. CBeverage

    CBeverage <|-- CCoffee

    CBeverage <|-- CTea
    TeaType <.. CTea : "Use"

    CBeverage <|-- CMilkshake
    MilkshakeSizeType <.. CMilkshake : "Use"

    CCoffee <|-- CCappuccino
    CCoffee <|-- CLatte

    namespace Beverage {
        class IBeverage {
            + GetDescription() string
            + GetCost() double
        }

        class CBeverage {
            + GetDescription() string
            - string m_description
        }

        class CCoffee {
            + GetCost() double
        }

        class CCappuccino {
            + GetCost() double
            - bool m_isDoublePortion
        }

        class CLatte {
            + GetCost() double
            - bool m_isDoublePortion
        }

        class TeaType {
            <<Enumuration>>
            BLACK,
            GREEN,
            RED
        }

        class CTea {
            + GetCost() double
            - TeaType m_type
        }

        class MilkshakeSizeType {
            <<Enumuration>>
            SMALL,
            MEDIUM,
            LARGE
        }

        class CMilkshake {
            + GetCost() double
            - MilkshakeSize m_size
        }
    }

    IBeverage <|.. CCondimentDecorator

    CCondimentDecorator o-- IBeverage

    CCondimentDecorator <|-- CCinnamon
    CCinnamon o-- IBeverage

    CCondimentDecorator <|-- CLemon
    CLemon o-- IBeverage

    CCondimentDecorator <|-- CIceCubes
    CIceCubes o-- IBeverage
    IceCubeType <.. CIceCubes : "Use"

    CCondimentDecorator <|-- CSyrup
    SyrupType <.. CSyrup : "Use"

    CCondimentDecorator <|-- CChocolateCrumbs

    CCondimentDecorator <|-- CCoconutFlakes

    namespace Condiment {
        class CCondimentDecorator {
            + GetDescription() string
            + GetCost() double
            + GetCondimentCost() double*
            + GetCondimentDescription() string*
            - IBeveragePtr m_beverage
        }

        class CCinnamon {
            # GetCondimentCost() double
            # GetCondimentDescription() string
        }

        class CLemon {
            # GetCondimentCost() double
            # GetCondimentDescription() string
            - unsigned m_quantity
        }

        class IceCubeType {
            <<Enumuration>>
            Dry,
            Water
        }

        class CIceCubes {
            # GetCondimentCost() double
            # GetCondimentDescription() string
            - unsigned m_quantity
            - IceCubeType m_type
        }

        class SyrupType {
            <<Enumuration>>
            Chocolate,
            Maple
        }

        class CSyrup {
            # GetCondimentCost() double
            # GetCondimentDescription() string
            - SyrupType m_syrupType
        }

        class CChocolateCrumbs {
            + GetCondimentCost() double
            + GetCondimentDescription() string
            - unsigned m_mass
        }

        class CCoconutFlakes {
            # GetCondimentCost() double
            # GetCondimentDescription() string
            - unsigned m_mass
        }
    }   
```