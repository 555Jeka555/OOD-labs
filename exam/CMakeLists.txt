cmake_minimum_required(VERSION 3.26)
project(exam)

set(CMAKE_CXX_STANDARD 20)

add_executable(decorator
        trash/Decorator/main.cpp
        trash/Decorator/IComponent.h
        trash/Decorator/Decorator.h
        trash/Decorator/Component.h
        trash/Decorator/DecoratorMult.h
        trash/Decorator/DecoratorAdd.h
)


add_executable(iterator
        trash/Iterator/main.cpp
        trash/Iterator/main.cpp
        trash/Iterator/Book.h
        trash/Iterator/Library.h
        trash/Iterator/IBookIterator.h
)

add_executable(bridge
        trash/Bridge/Device.h
        trash/Bridge/TV.h
        trash/Bridge/Radio.h
        trash/Bridge/RemoteControl.h
        trash/Bridge/AdvancedRemoteControl.h
        trash/Bridge/main.cpp
        trash/Strategy/main.cpp
        trash/FabricMethod/mainFabricMethod.cpp
        State/mainState.cpp
)

add_executable(templateMethod
        trash/TemplateMethod/Bevarage.h
        trash/TemplateMethod/TeaAndCoffee.h
        trash/TemplateMethod/main.cpp
)

add_executable(strategy
        trash/Strategy/main.cpp
)

add_executable(proxy
        trash/Proxy/mainHeavy.cpp
)

add_executable(fabricMethod
        trash/FabricMethod/mainFabricMethod.cpp
)

add_executable(prototype
        trash/Prototype/mainPrototype.cpp
)


add_executable(state
        State/mainState.cpp
)