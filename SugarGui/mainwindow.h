#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtGui>
#include <QtCore>
#include <QDialog>
#include <chrono>
#include <iostream>
#include <fstream>
#include <omp.h>

#include "../SugarScape/World.h"
#include "../SugarScape/Growback.h"
#include "../SugarScape/SeasonalGrowback.h"
#include "../SugarScape/PollutionFormation.h"
#include "../SugarScape/GarbageCollection.h"
#include "../SugarScape/AgentMove.h"
#include "../SugarScape/AgentCulture.h"
#include "../SugarScape/AgentDeath.h"
#include "../SugarScape/AgentDisease.h"
#include "../SugarScape/Diffusion.h"
#include "../SugarScape/AgentCombat.h"
#include "../SugarScape/AgentReplacement.h"
#include "../SugarScape/AgentMetabolism.h"
#include "../SugarScape/AgentMating.h"
#include "../SugarScape/AgentLoanPayments.h"
#include "../SugarScape/AgentCredit.h"
#include "../SugarScape/Strategy.h"
#include "../SugarScape/NewSweepStrategy.h"
#include "../SugarScape/LineByLineStrategy.h"
#include "../SugarScape/IndependentStrategy.h"
#include "../SugarScape/IterativeWriteStrategy.h"
#include "../SugarScape/ReadDependentStrategy.h"
#include "../SugarScape/AgentInheritance.h"
#include "../SugarScape/AgentMoveClosest.h"
#include "../SugarScape/AgentMoveStrongest.h"

namespace Ui {
class MainWindow;
enum class State {READY,RUNNING,WAITING,PAUSED};
enum class Strategy {SYNC,LINEBYLINE,NEWSWEEP,RNDASYNC};
const int Growback=0;
const int SeasonalGrowback=1;
const int PollutionFormation=2;
const int Diffusion=3;
const int BasicMovement=4;
const int Movement=5;
const int ClosestMovement=6;
const int StrongestMovement=7;
const int Combat=8;
const int Culture=9;
const int Disease=10;
const int Credit=11;
const int LoanPayments=12;
const int Inheritance=13;
const int Trade=14;
const int Replacement=15;
const int Reproduction=16;
const int Metabolism=17;
const int Death=18;
const int GarbageCollection=19;
const int RuleCount=20;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    Ui::State currentState;
    QTimer *myTimer;
    std::ofstream *outputFile;
    World *theWorld;/*!< create world and initialise it */
    /*!< Declare all possible strategies here */
    Strategy *baseStrategy;
    NewSweepStrategy *newSweep;
    LineByLineStrategy *lineByLine;
    RndAsyncStrategy *rndAsync;
    IndependentStrategy *independent;
    IterativeWriteStrategy *iterativeWrite;
    ReadDependentStrategy *readDependent;
    WriteStrategy *writeDependent;
    /*!< Declare all rules here */
    //Growback *growback;
    //AgentMove *move;
    //GarbageCollection *gc;
    //AgentDeath *agentDeath;
    //AgentMating *agentMating;
    //AgentMetabolism *agentMetabolism;
    std::string logFileName;
    std::string configFileName;
    std::string SugarDistributionFileName;
    bool liveRules[Ui::RuleCount];
    Action *Rules[Ui::RuleCount];
    bool displaySex;
    bool displayFertility;
    bool displayNewBorn;

protected:
    void paintEvent(QPaintEvent *);

private slots:
    void on_actionSetup_triggered();
    void timerTimeout();
    void on_actionStop_triggered();
    void on_actionReset_triggered();
    void on_actionStep_triggered();
    void on_actionGrowback_toggled(bool arg1);
    void on_actionSeasonal_Growback_toggled(bool arg1);
    void on_actionFormation_toggled(bool arg1);
    void on_actionDiffusion_toggled(bool arg1);
    void on_actionMovement_2_toggled(bool arg1);
    void on_actionCombat_toggled(bool arg1);
    void on_actionReplacement_toggled(bool arg1);
    void on_actionReproduction_toggled(bool arg1);
    void on_actionCulture_toggled(bool arg1);
    void on_actionDisease_toggled(bool arg1);
    void on_actionCredit_toggled(bool arg1);
    void on_actionInheritance_toggled(bool arg1);
    void on_actionConfig_File_triggered();
    void on_actionResource_File_triggered();
    void on_actionStart_triggered();
    void on_actionInitialise_All_triggered();
    void on_actionMove_Strongest_Wins_toggled(bool arg1);
    void on_actionMove_Closest_Wins_toggled(bool arg1);
    void on_actionSex_toggled(bool arg1);
    void on_actionFertility_toggled(bool arg1);
    void on_actionNewBorn_toggled(bool arg1);
    void on_actionReplacement_triggered();
};

#endif // MAINWINDOW_H
