#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QTime>
#include<QDebug>
#include <QDialog>
 #include <QFileDialog>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    currentState(Ui::State::WAITING)
{
    ui->setupUi(this);
    this->setFixedSize(800,820);
    theWorld = new World(50);/*!< create world and initialise it */
    /*!< Declare all possible strategies here */
    baseStrategy = new Strategy(theWorld);
    newSweep= new NewSweepStrategy(theWorld);
    lineByLine= new LineByLineStrategy(theWorld);
    rndAsync= new RndAsyncStrategy(theWorld);
    independent= new IndependentStrategy(theWorld);
    iterativeWrite= new IterativeWriteStrategy(theWorld);
    readDependent= new ReadDependentStrategy(theWorld);
    writeDependent= new WriteStrategy(theWorld);
    /*!< Declare all rules here */
    Rules[Ui::Growback]= new Growback(theWorld,independent);
    Rules[Ui::SeasonalGrowback]= new SeasonalGrowback(theWorld,independent);
    Rules[Ui::PollutionFormation]= new PollutionFormation(theWorld,independent);
    Rules[Ui::Diffusion]= new Diffusion(theWorld,readDependent);
    Rules[Ui::BasicMovement]= new AgentBasicMove(theWorld,writeDependent);
    Rules[Ui::Movement]= new AgentMove(theWorld,writeDependent);
    Rules[Ui::ClosestMovement]= new AgentMoveClosest(theWorld,writeDependent);
    Rules[Ui::StrongestMovement]= new AgentMoveStrongest(theWorld,writeDependent);
    Rules[Ui::Combat]= new AgentCombat(theWorld,writeDependent);
    Rules[Ui::Culture]= new AgentCulture(theWorld,readDependent);
    Rules[Ui::Disease]= new AgentDisease(theWorld,readDependent);
    Rules[Ui::Credit]= new AgentCredit(theWorld,iterativeWrite);
    Rules[Ui::LoanPayments]= new AgentLoanPayments(theWorld,iterativeWrite);
    Rules[Ui::Inheritance]= new AgentInheritance(theWorld,writeDependent);
    Rules[Ui::Trade]= new AgentCredit(theWorld,iterativeWrite);//TO DO: ADD AGENTTRADE
    Rules[Ui::Replacement]= new AgentReplacement(theWorld,writeDependent);
    Rules[Ui::GarbageCollection]= new GarbageCollection(theWorld,independent);
    Rules[Ui::Death]= new AgentDeath(theWorld,readDependent);
    Rules[Ui::Reproduction]= new AgentMating(theWorld,iterativeWrite);
    Rules[Ui::Metabolism]= new AgentMetabolism(theWorld,independent);
    for(int i=0;i<Ui::RuleCount;++i){
        liveRules[i]=false;
    }
    liveRules[Ui::GarbageCollection]=true;
    liveRules[Ui::Metabolism]=true;
    liveRules[Ui::Death]=true;
//!! TO DO remove these!
    //growback= new Growback(theWorld,independent);
    //move= new AgentMove(theWorld,writeDependent);
    //gc= new GarbageCollection(theWorld,independent);
    //agentDeath= new AgentDeath(theWorld,readDependent);
    //agentMating= new AgentMating(theWorld,iterativeWrite);
    //agentMetabolism= new AgentMetabolism(theWorld,independent);

    displaySex=false;
    displayNewBorn=false;
    displayFertility=false;
//!!TO DO change to user selectable files
    SugarDistributionFileName="startup.csv";
    logFileName="log/output.log";
    theWorld->init(logFileName,SugarDistributionFileName);
    myTimer= new QTimer(this);
    myTimer->setInterval(300);
    connect(myTimer,SIGNAL(timeout()),this,SLOT(timerTimeout()));

}

MainWindow::~MainWindow()
{
    delete ui;
    delete myTimer;
    delete baseStrategy;
    delete newSweep;
    delete lineByLine;
    delete rndAsync;
    delete independent;
    delete iterativeWrite;
    delete readDependent;
    delete writeDependent;
    delete theWorld;
    for(int i=0;i<Ui::RuleCount;++i){
        delete Rules[i];
    }
}

void MainWindow::paintEvent(QPaintEvent *)
{
    int agentCount=0;
    QPoint origin(0,20);
    QPoint size(this->width(),this->height()-20);
    QPainter painter(this);
    QBrush brush(Qt::black,Qt::SolidPattern);
    std::pair<int,int> pos;
    Agent *theAgent=nullptr;
    painter.fillRect(origin.x(),origin.y(),size.x(),size.y(),brush);
    if (currentState!=Ui::State::WAITING){
        int cellSize=size.y()/theWorld->getSize();
        QPoint p(origin.x()+cellSize/2,origin.y()+cellSize/2);
        for (int i=0; i<theWorld->getSize(); ++i) {
            for (int k=0; k<theWorld->getSize(); ++k) {
                pos={i,k};
                p.setX(origin.x()+cellSize/2+cellSize*i);
                p.setY(origin.y()+cellSize/2+cellSize*k);
                int radius=-1;
                Location *currLocation=theWorld->getLocation(pos);
                if (currLocation->hasAgent()) {
                    agentCount++;
                    theAgent=theWorld->getLocation(pos)->getAgent();
                    radius=theAgent->getSugar();
                    if (theAgent->getTribe()==affiliation::blue) {
                        brush.setColor(Qt::blue);
                    }
                    else{
                        brush.setColor(Qt::red);
                    }
                    if (displayNewBorn==true && theAgent->getAge()<2){
                        brush.setColor(Qt::white);
                    }
                }
                else{
                    radius=theWorld->getLocation(pos)->getSugar();
                    brush.setColor(Qt::green);
                }
                if (radius>cellSize/2) {
                    radius=cellSize/2;
                }
                painter.setBrush(brush);
                if (displaySex==true && currLocation->hasAgent()){
                    if (theAgent->getSex()==male){
                        QRectF rectangle(p.x()-radius,p.y()-radius,radius*2,radius*2);
                        painter.drawRect(rectangle);
                    }
                    else{
                        painter.drawEllipse(p,radius,radius);
                    }
                }
                else{
                   painter.drawEllipse(p,radius,radius);
                }
                if (displayFertility==true && currLocation->hasAgent()){
                    if (theAgent->isFertile()){
                        brush.setColor(Qt::black);
                        painter.drawEllipse(p,radius/2,radius/2);
                    }
                }

            }
        }

    }
}

void MainWindow::on_actionSetup_triggered()
{


}



void MainWindow::timerTimeout()
{
    if(Ui::State::RUNNING==currentState)
    {
         this->theWorld->applyRules();
         this->repaint();
    }
}



void MainWindow::on_actionStop_triggered()
{
    currentState=Ui::State::PAUSED;
}

void MainWindow::on_actionReset_triggered()
{
    currentState=Ui::State::READY;
    theWorld->init(logFileName,SugarDistributionFileName);/*!< Read from init files */
    theWorld->sync();/*!< sync World before use */
    this->repaint(); /*!< Draw start state */
}

void MainWindow::on_actionStep_triggered()
{
     /*!< If simulation is paused then do one step and redraw */
    if(Ui::State::PAUSED==currentState)
    {
         this->theWorld->applyRules();
         this->repaint();
    }
}

void MainWindow::on_actionGrowback_toggled(bool arg1)
{
    if (Ui::State::WAITING==currentState){
        if(arg1==true){
            liveRules[Ui::Growback]=true;
            liveRules[Ui::SeasonalGrowback]=false;
            ui->actionSeasonal_Growback->setChecked(false);
        }else{
            liveRules[Ui::Growback]=false;
        }
    }
}

void MainWindow::on_actionSeasonal_Growback_toggled(bool arg1)
{
    if (Ui::State::WAITING==currentState){
        if(arg1==true){
            liveRules[Ui::Growback]=false;
            ui->actionGrowback->setChecked(false);
            liveRules[Ui::SeasonalGrowback]=true;
        }else{
            liveRules[Ui::SeasonalGrowback]=false;
        }
    }
}

void MainWindow::on_actionFormation_toggled(bool arg1)
{
    if (Ui::State::WAITING==currentState){
        if(arg1==true){
            liveRules[Ui::PollutionFormation]=true;
        }else{
            liveRules[Ui::PollutionFormation]=false;
            liveRules[Ui::Diffusion]=false;
            ui->actionDiffusion->setChecked(false);
        }
    }
}

void MainWindow::on_actionDiffusion_toggled(bool arg1)
{
    if (Ui::State::WAITING==currentState){
        if(arg1==true){
            liveRules[Ui::Diffusion]=true;
            ui->actionFormation->setChecked(true);
            liveRules[Ui::PollutionFormation]=true;
        }else{
            liveRules[Ui::Diffusion]=false;
        }
    }
}

void MainWindow::on_actionMovement_2_toggled(bool arg1)
{
    if (Ui::State::WAITING==currentState){
        if(arg1==true){
            liveRules[Ui::BasicMovement]=true;
            ui->actionCombat->setChecked(false);
            liveRules[Ui::Combat]=false;
            ui->actionMove_Closest_Wins->setChecked(false);
            liveRules[Ui::ClosestMovement]=false;
            ui->actionMove_Strongest_Wins->setChecked(false);
            liveRules[Ui::StrongestMovement]=false;
        }else{
            liveRules[Ui::BasicMovement]=false;
        }
    }
}


void MainWindow::on_actionMove_Strongest_Wins_toggled(bool arg1)
{
    if (Ui::State::WAITING==currentState){
        if(arg1==true){
            liveRules[Ui::StrongestMovement]=true;
            ui->actionCombat->setChecked(false);
            liveRules[Ui::Combat]=false;
            ui->actionMovement_2->setChecked(false);
            liveRules[Ui::BasicMovement]=false;
            ui->actionMove_Closest_Wins->setChecked(false);
            liveRules[Ui::ClosestMovement]=false;
        }else{
            liveRules[Ui::StrongestMovement]=false;
        }
    }
}

void MainWindow::on_actionMove_Closest_Wins_toggled(bool arg1)
{
    if (Ui::State::WAITING==currentState){
        if(arg1==true){
            liveRules[Ui::ClosestMovement]=true;
            ui->actionCombat->setChecked(false);
            liveRules[Ui::Combat]=false;
            ui->actionMovement_2->setChecked(false);
            liveRules[Ui::BasicMovement]=false;
            ui->actionMove_Strongest_Wins->setChecked(false);
            liveRules[Ui::StrongestMovement]=false;
        }else{
            liveRules[Ui::ClosestMovement]=false;
        }
    }
}


void MainWindow::on_actionCombat_toggled(bool arg1)
{
    if (Ui::State::WAITING==currentState){
        if(arg1==true){
            liveRules[Ui::Combat]=true;
            ui->actionMovement_2->setChecked(false);
            liveRules[Ui::BasicMovement]=false;
            ui->actionMove_Closest_Wins->setChecked(false);
            liveRules[Ui::ClosestMovement]=false;
            ui->actionMove_Strongest_Wins->setChecked(false);
            liveRules[Ui::StrongestMovement]=false;
        }else{
            liveRules[Ui::Combat]=false;
        }
    }
}

void MainWindow::on_actionReplacement_toggled(bool arg1)
{
    if (Ui::State::WAITING==currentState){
        if(arg1==true){
            liveRules[Ui::Replacement]=true;
            liveRules[Ui::Death]=false;
        }else{
            liveRules[Ui::Replacement]=false;
            liveRules[Ui::Death]=true;
        }
    }
}

void MainWindow::on_actionReproduction_toggled(bool arg1)
{
    if (Ui::State::WAITING==currentState){
        if(arg1==true){
            liveRules[Ui::Reproduction]=true;
        }else{
            liveRules[Ui::Reproduction]=false;
        }
    }
}

void MainWindow::on_actionCulture_toggled(bool arg1)
{
    if (Ui::State::WAITING==currentState){
        if(arg1==true){
            liveRules[Ui::Culture]=true;
        }else{
            liveRules[Ui::Culture]=false;
        }
    }
}

void MainWindow::on_actionDisease_toggled(bool arg1)
{
    if (Ui::State::WAITING==currentState){
        if(arg1==true){
            liveRules[Ui::Disease]=true;
        }else{
            liveRules[Ui::Disease]=false;
        }
    }
}

void MainWindow::on_actionCredit_toggled(bool arg1)
{
    if (Ui::State::WAITING==currentState){
        if(arg1==true){
            liveRules[Ui::Credit]=true;
            liveRules[Ui::LoanPayments]=true;
        }else{
            liveRules[Ui::Credit]=false;
            liveRules[Ui::LoanPayments]=false;
        }
    }
}

void MainWindow::on_actionInheritance_toggled(bool arg1)
{
    if (Ui::State::WAITING==currentState){
        if(arg1==true){
            liveRules[Ui::Inheritance]=true;
        }else{
            liveRules[Ui::Inheritance]=false;
        }
    }
}

void MainWindow::on_actionConfig_File_triggered()
{
    QString fileName= QFileDialog::getOpenFileName(this, tr("Open Configuration File"), QString(),
                                                   tr("Config Files (*.cfg)"));
    if(!fileName.isEmpty()) configFileName = fileName.toUtf8().constData();
}

void MainWindow::on_actionResource_File_triggered()
{
        QString fileName= QFileDialog::getOpenFileName(this, tr("Open Resource File"), QString(),
                                                       tr("Config Files (*.csv)"));
    if(!fileName.isEmpty()) SugarDistributionFileName = fileName.toUtf8().constData();
    theWorld->init(logFileName,SugarDistributionFileName);
}

void MainWindow::on_actionStart_triggered()
{
    if (currentState==Ui::State::WAITING){
        on_actionInitialise_All_triggered();
    }
    if (currentState==Ui::State::READY){
        currentState=Ui::State::RUNNING;
        myTimer->start();
    }
}

void MainWindow::on_actionInitialise_All_triggered()
{
    if (currentState==Ui::State::WAITING){
        outputFile= new std::ofstream("fileName.cfg",std::ios::out | std::ios::app);
        theWorld->init(logFileName,SugarDistributionFileName);/*!< Read from init files */
        theWorld->sync();/*!< sync World before use */
        theWorld->clearRules();
        for(int i=0;i<Ui::RuleCount;++i){
            if (liveRules[i]==true) theWorld->addRule(Rules[i]);
        }
        currentState=Ui::State::READY;
        this->repaint();
    }
}





void MainWindow::on_actionSex_toggled(bool arg1)
{
    if (arg1==true){
        displaySex=true;
    }
    else{
        displaySex=false;
    }
}

void MainWindow::on_actionFertility_toggled(bool arg1)
{
    if (arg1==true){
        displayFertility=true;
    }
    else{
        displayFertility=false;
    }
}

void MainWindow::on_actionNewBorn_toggled(bool arg1)
{
    if (arg1==true){
        displayNewBorn=true;
    }
    else{
        displayNewBorn=false;
    }
}

void MainWindow::on_actionReplacement_triggered()
{

}
