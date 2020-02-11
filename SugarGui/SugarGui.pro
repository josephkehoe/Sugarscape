#-------------------------------------------------
#
# Project created by QtCreator 2016-11-14T16:53:17
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SugarGui
TEMPLATE = app

CONFIG +=c++11
QMAKE_CXXFLAGS += -std=c++11
SOURCES += main.cpp\
        mainwindow.cpp \
    ../SugarScape/Location.cpp \
    ../SugarScape/LineByLineStrategy.cpp \
    ../SugarScape/IterativeWriteStrategy.cpp \
    ../SugarScape/IterativeWriteAction.cpp \
    ../SugarScape/IndependentStrategy.cpp \
    ../SugarScape/IndependentAction.cpp \
    ../SugarScape/Growback.cpp \
    ../SugarScape/group.cpp \
    ../SugarScape/GarbageCollection.cpp \
    ../SugarScape/Diffusion.cpp \
    ../SugarScape/AgentReplacement.cpp \
    ../SugarScape/AgentMoveStrongest.cpp \
    ../SugarScape/AgentMoveClosest.cpp \
    ../SugarScape/AgentMove.cpp \
    ../SugarScape/AgentMetabolism.cpp \
    ../SugarScape/AgentMating.cpp \
    ../SugarScape/AgentLoanPayments.cpp \
    ../SugarScape/AgentInheritance.cpp \
    ../SugarScape/AgentDisease.cpp \
    ../SugarScape/AgentDeath.cpp \
    ../SugarScape/AgentCulture.cpp \
    ../SugarScape/AgentCredit.cpp \
    ../SugarScape/AgentCombat.cpp \
    ../SugarScape/AgentBasicMove.cpp \
    ../SugarScape/Agent.cpp \
    ../SugarScape/Action.cpp \
    ../SugarScape/NewSweepStrategy.cpp \
    ../SugarScape/PollutionFormation.cpp \
    ../SugarScape/ReadAction.cpp \
    ../SugarScape/ReadDependentStrategy.cpp \
    ../SugarScape/RndAsyncStrategy.cpp \
    ../SugarScape/SeasonalGrowback.cpp \
    ../SugarScape/Strategy.cpp \
    ../SugarScape/UniformChoice.cpp \
    ../SugarScape/WriteAction.cpp \
    ../SugarScape/WriteStrategy.cpp \
    ../SugarScape/World.cpp

HEADERS  += mainwindow.h \
    ../SugarScape/Location.h \
    ../SugarScape/LineByLineStrategy.h \
    ../SugarScape/IterativeWriteStrategy.h \
    ../SugarScape/IterativeWriteAction.h \
    ../SugarScape/IndependentStrategy.h \
    ../SugarScape/IndependentAction.h \
    ../SugarScape/Growback.h \
    ../SugarScape/group.h \
    ../SugarScape/GarbageCollection.h \
    ../SugarScape/Diffusion.h \
    ../SugarScape/AgentReplacement.h \
    ../SugarScape/AgentMoveStrongest.h \
    ../SugarScape/AgentMoveClosest.h \
    ../SugarScape/AgentMove.h \
    ../SugarScape/AgentMetabolism.h \
    ../SugarScape/AgentMating.h \
    ../SugarScape/AgentLoanPayments.h \
    ../SugarScape/AgentInheritance.h \
    ../SugarScape/AgentDisease.h \
    ../SugarScape/AgentDeath.h \
    ../SugarScape/AgentCulture.h \
    ../SugarScape/AgentCredit.h \
    ../SugarScape/AgentCombat.h \
    ../SugarScape/AgentBasicMove.h \
    ../SugarScape/Agent.h \
    ../SugarScape/Action.h \
    ../SugarScape/NewSweepStrategy.h \
    ../SugarScape/PollutionFormation.h \
    ../SugarScape/ReadAction.h \
    ../SugarScape/ReadDependentStrategy.h \
    ../SugarScape/RndAsyncStrategy.h \
    ../SugarScape/SeasonalGrowback.h \
    ../SugarScape/Strategy.h \
    ../SugarScape/UniformChoice.h \
    ../SugarScape/WriteAction.h \
    ../SugarScape/WriteStrategy.h \
    ../SugarScape/World.h

FORMS    += mainwindow.ui

DISTFILES += \
    ../SugarScape/CMakeCache.txt
