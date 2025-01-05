cmake_minimum_required(VERSION 3.26)
project(exam)

set(CMAKE_CXX_STANDARD 20)

add_executable(decorator Decorator/main.cpp
        Decorator/IComponent.h
        Decorator/Decorator.h
        Decorator/Component.h
        Decorator/DecoratorMult.h
        Decorator/DecoratorAdd.h)
