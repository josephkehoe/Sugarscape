//
//  main.cpp
//  SugarScape
//
//  Created by Joseph P Kehoe on 25/04/2015.
//  Copyright (c) 2015 Joseph P Kehoe. All rights reserved.
//

//
// Disclamer:
// ----------
//
// This code will work only if you selected window, graphics and audio.
//
// Note that the "Run Script" build phase (XCode) will copy the required frameworks
// or dylibs to your application bundle so you can execute it on any OS X
// computer.
//
// Your resource files (images, sounds, fonts, ...) are also copied to your
// application bundle. To get the path to these resource, use the helper
// method resourcePath() from ResourcePath.hpp
//

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

#include <chrono>
#include <iostream>
#include <fstream>



#include "World.h"
#include "Growback.h"
#include "SeasonalGrowback.h"
#include "PollutionFormation.h"
#include "GarbageCollection.h"
#include "AgentMove.h"
#include "AgentCulture.h"
#include "AgentDeath.h"
#include "AgentDisease.h"
#include "Diffusion.h"
#include "AgentCombat.h"
#include "AgentReplacement.h"
#include "AgentMetabolism.h"
#include "AgentMating.h"
#include "AgentLoanPayments.h"
#include "AgentCredit.h"
#include "ViewPort.h"
#include "Strategy.h"
#include "NewSweepStrategy.h"
#include "LineByLineStrategy.h"
#include "IndependentStrategy.h"
#include "IterativeWriteStrategy.h"
#include "ReadDependentStrategy.h"
#include "AgentInheritance.h"

int benchmark(int,int,int,int,int,std::string);
int Gui(int, float);


int Gui(World *theWorld, float pause)
{

    std::ofstream outputFile("log/capacityM1v1.csv",std::ios::out | std::ios::app);

    /*!<  Create the main window */
    sf::RenderWindow window(sf::VideoMode(1024, 768), "SFML window");
    /*!< create viewport for displaying simulation */
    ViewPort theGUI(&window,theWorld,std::pair<int,int>(1024, 768),std::pair<int,int>(0,0),theWorld->getSize());
    /*!< Declare all possible strategies here */
    Strategy baseStrategy(theWorld);
    NewSweepStrategy newSweep(theWorld);
    LineByLineStrategy lineByLine(theWorld);
    RndAsyncStrategy rndAsync(theWorld);
    IndependentStrategy independent(theWorld);
    IterativeWriteStrategy iterativeWrite(theWorld);
    ReadDependentStrategy readDependent(theWorld);
    WriteStrategy writeDependent(theWorld);
    /*!< Declare all rules here */
    Growback growback(theWorld,&independent);
    growback.setStrategy(&independent);
    SeasonalGrowback seasonalGrowback(theWorld,&independent);
    seasonalGrowback.setStrategy(&independent);
    AgentMove move(theWorld,&writeDependent);
    move.setStrategy(&writeDependent);
    PollutionFormation pollForm(theWorld,&independent);
    pollForm.setStrategy(&independent);
    GarbageCollection gc(theWorld,&independent);
    gc.setStrategy(&independent);
    AgentCulture agentCulture(theWorld,&readDependent);
    agentCulture.setStrategy(&readDependent);
    AgentDeath agentDeath(theWorld,&readDependent);
    agentDeath.setStrategy(&readDependent);
    AgentDisease agentDisease(theWorld,&readDependent);
    agentDisease.setStrategy(&readDependent);
    Diffusion diffusion(theWorld,&readDependent);
    diffusion.setStrategy(&readDependent);
    AgentCombat agentCombat(theWorld,&writeDependent);
    agentCombat.setStrategy(&writeDependent);
    AgentReplacement agentReplacement(theWorld,&writeDependent);
    agentReplacement.setStrategy(&writeDependent);
    AgentMating agentMating(theWorld,&iterativeWrite);
    agentMating.setStrategy(&iterativeWrite);
    AgentMetabolism agentMetabolism(theWorld,&independent);
    agentMetabolism.setStrategy(&independent);
    AgentCredit agentCredit(theWorld,&iterativeWrite);
    agentCredit.setStrategy(&iterativeWrite);
    AgentLoanPayments agentLoanPayments(theWorld,&writeDependent);
    agentLoanPayments.setStrategy(&writeDependent);
    AgentInheritance inheritance(theWorld,&readDependent);
    inheritance.setStrategy(&readDependent);
    //!
    /*!
     Add the rules we are using here.
     Ordering of rules is important
     Do death last and metabolism before replacement!!
     */
    /*!< Rules for Lattice are added first (before Agent Rules)*/
    theWorld->addRule(&growback);
    //theWorld.addRule(&seasonalGrowback);
    //theWorld.addRule(&pollForm);
    //theWorld.addRule(&diffusion);
    /*!< Movement Rule for Agents follow next -pick only one!*/
    theWorld->addRule(&move);
    //theWorld.addRule(&agentMating);
    //theWorld.addRule(&agentCombat);
    /*!< Other rules for Agent behaviour go next*/
    theWorld->addRule(&agentCulture);
    //theWorld.addRule(&agentDisease);
    /*!< Finally add Metabolism and (replacement or death) and finish with garbage collection*/
    theWorld->addRule(&agentMetabolism);
    theWorld->addRule(&agentReplacement);
    theWorld->addRule(&agentDeath);
    theWorld->addRule(&gc);

    //!
    /*!
     Start simulation!
     */
    int stepCount=0;
    std::string counter;
    
    // Set the Icon
    sf::Image icon;
    if (!icon.loadFromFile("resources/icon.png")) {
        return EXIT_FAILURE;
    }
    window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
    // Create a graphical text to display
    sf::Font font;
    if (!font.loadFromFile("resources/sansation.ttf")) {
        return EXIT_FAILURE;
    }
    counter = std::to_string(stepCount);
    sf::Text text(counter, font, 50);
    text.setColor(sf::Color::White);
    
    // Load a music to play
    sf::Music music;
    if (!music.openFromFile("resources/nice_music.ogg")) {
        return EXIT_FAILURE;
    }
    
    // Play the music -it never hurts!
    music.play();
    //!
    /*!
     set number of threads here - for testing only. Not needed normally
     */
    //omp_set_num_threads(1);
    // Start the game loop
    while (window.isOpen())
    {
        // Process events
        sf::Event event;
        while (window.pollEvent(event))
        {
            // Close window: exit
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            
            // Escape pressed: exit
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
                window.close();
            }
        }
        
        // Clear screen
        window.clear();
        
        theWorld->applyRules();
        theGUI.draw();
        // Draw the sprite
        //window.draw(sprite);
        
        // Draw the string
        window.draw(text);
        
        // Update the window
        window.display();
        counter = std::to_string(++stepCount);
        text.setString(counter);
        sf::Time t1 = sf::seconds(pause);
        sf::sleep(t1);
        theWorld->incStep();
        //outputFile << theWorld.getStep() << ","  << theWorld.getAgentCount()<< std::endl;
    }
    return stepCount;
}



int benchmark(int numRepeats, int stepCount, int dimStart, int increment, int runs, std::string fileName){
    std::ofstream outputFile(fileName,std::ios::out | std::ios::app);
    for (int i=0; i<runs; ++i) {
        std::chrono::duration <double, std::milli> min;
        std::chrono::duration <double, std::milli> max;   
        for (int k=0;k<numRepeats; ++k) {
            // create everything
            std::cout << "SIZE" << dimStart+i*increment << ": ";
            outputFile  << dimStart+i*increment << ",";
            World theWorld(dimStart+i*increment);
            theWorld.init();
            theWorld.sync();
            //theWorld.sanityCheck();
            /*!< Declare all possible strategies here */
            Strategy baseStrategy(&theWorld);
            NewSweepStrategy newSweep(&theWorld);
            LineByLineStrategy lineByLine(&theWorld);
            RndAsyncStrategy rndAsync(&theWorld);
            IndependentStrategy independent(&theWorld);
            IterativeWriteStrategy iterativeWrite(&theWorld);
            ReadDependentStrategy readDependent(&theWorld);
            WriteStrategy writeDependent(&theWorld);
            /*!< Declare all rules here */
            Growback growback(&theWorld,&independent);
            SeasonalGrowback seasonalGrowback(&theWorld,&independent);
            AgentMove move(&theWorld,&writeDependent);
            PollutionFormation pollForm(&theWorld,&independent);
            GarbageCollection gc(&theWorld,&independent);
            AgentCulture agentCulture(&theWorld,&readDependent);
            AgentDeath agentDeath(&theWorld,&readDependent);
            AgentDisease agentDisease(&theWorld,&readDependent);
            Diffusion diffusion(&theWorld,&readDependent);
            AgentCombat agentCombat(&theWorld,&writeDependent);
            AgentReplacement agentReplacement(&theWorld,&writeDependent);
            AgentMating agentMating(&theWorld,&iterativeWrite);
            AgentMetabolism agentMetabolism(&theWorld,&independent);
            AgentCredit agentCredit(&theWorld,&iterativeWrite);
            AgentLoanPayments agentLoanPayments(&theWorld,&writeDependent);
            AgentInheritance inheritance(&theWorld,&readDependent);


            
            //!
            /*!
             Add the rules we are using here.
             */
            theWorld.addRule(&growback);
            //theWorld.addRule(&seasonalGrowback);
            //theWorld.addRule(&pollForm);
            //theWorld.addRule(&diffusion);
            theWorld.addRule(&agentMetabolism);
            theWorld.addRule(&move);
            //theWorld.addRule(&agentCombat);
            //theWorld.addRule(&agentCulture);
            //theWorld.addRule(&agentDisease);
            theWorld.addRule(&agentMating);
            //theWorld.addRule(&agentReplacement);
            theWorld.addRule(&agentDeath);

            
            
            auto start = std::chrono::steady_clock::now();
            for (int m=0; m<stepCount; ++m) {
                //step
                theWorld.applyRules();
            }
            auto end = std::chrono::steady_clock::now();
            auto diff = end - start;
            if (k==0) {
                min=max=diff;
            }else{
                if (diff<min) min=diff;
                else if (diff>max) max=diff;
            }
            std::cout << std::chrono::duration <double, std::milli> (diff).count() << " ms ";
            std::cout  << std::chrono::duration <double, std::nano> (diff).count() << " ns " ;
            std::cout << "Agents:" << theWorld.getAgentCount() <<std::endl;
            outputFile  << std::chrono::duration <double, std::milli> (diff).count() << ",";
            outputFile  << std::chrono::duration <double, std::nano> (diff).count() << ","
                        << theWorld.getAgentCount() <<std::endl;
        }
        std::cout << "MIN:" << std::chrono::duration <double, std::milli> (min).count()
                <<" MAX:" << std::chrono::duration <double, std::milli> (max).count()
            << std::endl;
        
    }
    outputFile.close();
    return 0;
}


bool init(int dimensions){
    return true;
}

int main(int, char const**)
{
    /*!< create world and initialise it */
    World theWorld(50);
    theWorld.init("log/output.log");
    theWorld.sync();
    init(50);
    Gui(&theWorld,0.5f);
    //benchmark(1,50, 18, 18, 6, "/Users/joseph/test18-108.txt");
    return EXIT_SUCCESS;   
}

