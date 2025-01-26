cmake_minimum_required(VERSION 3.26)
project(exam)

set(CMAKE_CXX_STANDARD 20)

add_executable(decorator
        Decorator/main.cpp
        Decorator/IComponent.h
        Decorator/Decorator.h
        Decorator/Component.h
        Decorator/DecoratorMult.h
        Decorator/DecoratorAdd.h
)


add_executable(iterator
        Iterator/main.cpp
        Iterator/main.cpp
        Iterator/Book.h
        Iterator/Library.h
        Iterator/IBookIterator.h
)

add_executable(bridge
        Bridge/Device.h
        Bridge/TV.h
        Bridge/Radio.h
        Bridge/RemoteControl.h
        Bridge/AdvancedRemoteControl.h
        Bridge/main.cpp
        Strategy/main.cpp
)

add_executable(templateMethod
        TemplateMethod/Bevarage.h
        TemplateMethod/TeaAndCoffee.h
        TemplateMethod/main.cpp
)

add_executable(strategy
        Strategy/main.cpp
)

add_executable(proxy
        Proxy/mainHeavy.cpp
)
