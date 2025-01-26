```mermaid
classDiagram
    BattleSityGame o--> LevelProvider
    BattleSityGame *--> Level
    BattleSityGame ..|>  GamepadListener
    
    Gamepad o--> GamepadListener

    Level *--> Wall
    Level *--> Bonus
    Level *--> Tank

    LevelBuilder ..> Level : create

    LevelProvider *--> LevelBuilder

    Tank ..> Bullet: Create

    InProgressBatleSityGamestateState ..|> BatleSityGamestateState
    FinishBatleSityGamestateState ..|> BatleSityGamestateState
    PauseBatleSityGamestateState ..|> BatleSityGamestateState

    BattleSityGame *--> InProgressBatleSityGamestateState
    BattleSityGame *--> FinishBatleSityGamestateState
    BattleSityGame *--> PauseBatleSityGamestateState

    InProgressBatleSityGamestateState o--> BattleSityGame 
    FinishBatleSityGamestateState o--> BattleSityGame 
    PauseBatleSityGamestateState o--> BattleSityGame

    BattleSityGame *--> Player
    BattleSityGame *--> Bot

    Player *--> Tank
    Bot *--> Tank

    class BatleSityGamestateState {
        <<interface>>
        +Next()
        +Start()
        +Pause()
        +Finish()
        +Continue()
    }

    class InProgressBatleSityGamestateState {
        -game: BattleSityGame

        +Next()
        +Start()
        +Pause()
        +Finish()
        +Continue()
    }

    class FinishBatleSityGamestateState {
        -game: BattleSityGame

        +Next()
        +Start()
        +Pause()
        +Finish()
        +Continue()
    }

    class PauseBatleSityGamestateState {
        -game: BattleSityGame

        +Next()
        +Start()
        +Pause()
        +Finish()
        +Continue()
    }

    class BattleSityGame {
        -player1: * Player
        -player2: * Player
        -boots: list~Bot~
        -level: Level

        +SetPlayerOne(gamepad: Gamepad)
        +SetPlayerTwo(gamepad: Gamepad)
        +SetLevel(int levelIndex)
        +Next()
        +Start()
        +Pause()
        +Finish()
        +Continue()
        +SetInProgressState()
        +SetInFinishState()
        +SetPauseState()
    }

    class LevelProvider {
        +GetLevel(idnex: int) Level
    }
    
    class Level {
        +ListWalls() list~Wall~
        +ListBonuses() list~Bonus~
        +ListBots() list~Tank~
        -DeleteWall(wallID: string)
        -DeleteBonuse(bonuseID: string)
        -DeleteBot(tankID: string)
    }

    class LevelBuilder {
        +BuildWall()
        +BuildBonus()
        +BuildTank()
        +GetResult() Level
    }

    class Tank {
        - id: string

        +GetId() string
        +Move() 
        +TakeDamage(damage: uint)
        +RotateTo(type: DirectionType)
        +Shot() Bullet
        +GetPosition() Point
        +GetHealth() uint
        +SetHelth(uint helth)
        +UpgradeDamage(uint damage)
    }

    class Bullet {
        - id: string

        +GetId() string
        +Move() Point
        +GetPosition() Point
    }

    class Bonus {
        - id: string

        +GetId() string
        +GetType() string
        +ApplyEffect(tank: Tank)
    }

    class GamepadListener {
        <<interface>>
        +OnChange()
    }

    class Gamepad {
        +SetListener(listener: GamepadListener)
    }

    class Wall {
        - id: string

        +GetId() string
        +GetPosition() Point
        +GetHealth() uint
        +TakeDamage(damage: uint)
    }

    class Player {
        +UpdateInput()
    }

    class Bot {
        +UpdateAI(target: const Tank &)
        -CalculateDirectionToTarget()
        -IsPlayerInSight()
    }

    class Point {
        +x: int
        +y: int
    }

    class DirectionType {
        <<enumeration>>
        UP
        DOWN
        LEFT
        RIGHT
    }
```