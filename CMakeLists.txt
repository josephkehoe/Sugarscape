cmake_minimum_required(VERSION 3.3)
project(Sugarscape)
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules" ${CMAKE_MODULE_PATH})
find_package(sfml-window)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++11   -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio")
set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio")
set(CMAKE_MODULE_LINKER_FLAGS "${CMAKE_MODULE_LINKER_FLAGS} -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio")
set(SOURCE_FILES
    SugarScape/Action.cpp
    SugarScape/Action.h
    SugarScape/Agent.cpp
    SugarScape/Agent.h
    SugarScape/AgentBasicMove.cpp
    SugarScape/AgentBasicMove.h
    SugarScape/AgentCombat.cpp
    SugarScape/AgentCombat.h
    SugarScape/AgentCredit.cpp
    SugarScape/AgentCredit.h
    SugarScape/AgentCulture.cpp
    SugarScape/AgentCulture.h
    SugarScape/AgentDeath.cpp
    SugarScape/AgentDeath.h
    SugarScape/AgentDisease.cpp
    SugarScape/AgentDisease.h
    SugarScape/AgentLoanPayments.cpp
    SugarScape/AgentLoanPayments.h
    SugarScape/AgentMating.cpp
    SugarScape/AgentMating.h
    SugarScape/AgentMetabolism.cpp
    SugarScape/AgentMetabolism.h
    SugarScape/AgentMove.cpp
    SugarScape/AgentMove.h
    SugarScape/AgentReplacement.cpp
    SugarScape/AgentReplacement.h
    SugarScape/Diffusion.cpp
    SugarScape/Diffusion.h
    SugarScape/GarbageCollection.cpp
    SugarScape/GarbageCollection.h
    SugarScape/group.cpp
    SugarScape/group.h
    SugarScape/Growback.cpp
    SugarScape/Growback.h
    SugarScape/IndependentAction.cpp
    SugarScape/IndependentAction.h
    SugarScape/AgentInheritance.cpp
    SugarScape/AgentInheritance.h
    SugarScape/IterativeWriteAction.cpp
    SugarScape/IterativeWriteAction.h
    SugarScape/Location.cpp
    SugarScape/Location.h
    SugarScape/main.cpp
    SugarScape/PollutionFormation.cpp
    SugarScape/PollutionFormation.h
    SugarScape/ReadAction.cpp
    SugarScape/ReadAction.h
    SugarScape/SeasonalGrowback.cpp
    SugarScape/SeasonalGrowback.h

    SugarScape/World.cpp
    SugarScape/World.h
    SugarScape/WriteAction.cpp
    SugarScape/WriteAction.h
        SugarScape/Strategy.cpp
        SugarScape/Strategy.h
        SugarScape/IndependentStrategy.cpp
        SugarScape/IndependentStrategy.h
        SugarScape/ReadDependentStrategy.cpp
        SugarScape/ReadDependentStrategy.h
        SugarScape/WriteStrategy.cpp
        SugarScape/WriteStrategy.h
        SugarScape/IterativeWriteStrategy.cpp
        SugarScape/IterativeWriteStrategy.h
    SugarScape/LineByLineStrategy.cpp
        SugarScape/LineByLineStrategy.h
        SugarScape/RndAsyncStrategy.cpp
        SugarScape/RndAsyncStrategy.h
        SugarScape/NewSweepStrategy.cpp
        SugarScape/NewSweepStrategy.h
        SugarScape/IterativeWriteStrategy.cpp
        SugarScape/IterativeWriteStrategy.h
        SugarScape/LineByLineStrategy.cpp
        SugarScape/LineByLineStrategy.h
        SugarScape/RndAsyncStrategy.cpp
        SugarScape/RndAsyncStrategy.h
        SugarScape/NewSweepStrategy.cpp
        SugarScape/NewSweepStrategy.h SugarScape/AgentMoveClosest.cpp SugarScape/AgentMoveClosest.h SugarScape/AgentMoveStrongest.cpp SugarScape/AgentMoveStrongest.h SugarScape/UniformChoice.cpp SugarScape/UniformChoice.h)

add_executable(Sugarscape ${SOURCE_FILES})