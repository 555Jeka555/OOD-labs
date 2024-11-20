```mermaid
classDiagram
    IGumballMachine <|.. GumballMachine : "private"
    GumballMachine o-- IState
    GumballMachine *-- HasQuarterState
    GumballMachine *-- NoQuarterState
    GumballMachine *-- SoldOutState
    GumballMachine *-- SoldState

    class IGumballMachine {
        + ReleaseBall()*
        + GetBallCount() unsigned*
        + SetSoldOutState()*
        + SetNoQuarterState()*
        + SetSoldState()*
        + SetHasQuarterState()*
    }

    class GumballMachine {
        + EjectQuarter()
        + InsertQuarter()
        + InsertQuarter()
        + TurnCrank()
        + ToString()
        - ReleaseBall()
        - GetBallCount() unsigned
        - SetSoldOutState()
        - SetNoQuarterState()
        - SetSoldState()
        - SetHasQuarterState()

        - m_count: unsigned 
        - m_soldState: SoldState 
        - m_soldOutState: SoldOutState
        - m_noQuarterState: NoQuarterState
        - m_hasQuarterState: HasQuarterState
        - m_state: * IState
    }

    IState <|.. HasQuarterState
    IState <|.. NoQuarterState
    IState <|.. SoldOutState
    IState <|.. SoldState

    HasQuarterState o-- IGumballMachine
    NoQuarterState o-- IGumballMachine
    SoldOutState o-- IGumballMachine
    SoldState o-- IGumballMachine

    namespace State {
        class IState {
            + InsertQuarter()*
            + EjectQuarter()*
            + TurnCrank()*
            + Dispense()*
            + ToString() string*
        }

        class HasQuarterState {
            + InsertQuarter()
            + EjectQuarter()
            + TurnCrank()
            + Dispense()
            + ToString() string

            - m_gumballMachine: & IGumballMachine
        }

        class NoQuarterState {
            + InsertQuarter()
            + EjectQuarter()
            + TurnCrank()
            + Dispense()
            + ToString() string

            - m_gumballMachine: & IGumballMachine
        }

        class SoldOutState {
            + InsertQuarter()
            + EjectQuarter()
            + TurnCrank()
            + Dispense()
            + ToString() string

            - m_gumballMachine: & IGumballMachine
        }

        class SoldState {
            + InsertQuarter()
            + EjectQuarter()
            + TurnCrank()
            + Dispense()
            + ToString() string

            - m_gumballMachine: & IGumballMachine
        }
    }
```