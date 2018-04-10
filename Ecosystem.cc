/*
==================================================
 Ecosystem
=================================================
*/
//
#include <TApplication.h>
// #include <TROOT.h>
#include <TStyle.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
// #include <math.h>
// #include <string.h>
// #include <TFile.h>
//
#include <TCanvas.h>
#include <TEllipse.h>
#include <TLine.h>
#include <TText.h>
#include <TRandom3.h>
// #include <TTimer.h>
//
// #include <TH1F.h>
// #include <TH2F.h>
#include <TGraph.h>
//
#include "models/Creature.h"
#include "models/Plank.h"
// #include "interface/Neuron.h"
// #include "interface/Brain.h"
// #include "interface/Fire.h"
// #include "interface/Food.h"
#include "models/ToolBox.h"
#include "interface/CommandLineArguments.h"

int timeStep=2000;
int nCreatures=100;
int nPlanks=20;
double plankLength=100.;
double worldSize=500.;
double speed=2.0;

int seed=90;

// Debug Levels
// bits: xxxx
// bit 0 = TCanvas visualization
// bit 1 = Verbalization
// bit 2 = Fill histograms
// bit 3 = Draw the histograms
int debug = 0x2;

// Mutation parameters
double mu_newNeuron=0; // 0.001;
double mu_newConnection=0.05;
double mu_modConnection=0.05;

int main(int argc, char *argv[])
{
  std::map<std::string, int> cmdMap=commandLineArguments(argc, argv);
  if (cmdMap.find("-debug")!=cmdMap.end())           debug=cmdMap["-debug"];

  r3->SetSeed(seed);
  std::cout<<"debug = "<<debug<<std::endl;
  std::cout<<"visualization = "<<decodeDebug(debug, 0)<<std::endl;

  TApplication *myapp=new TApplication("myapp",0,0);
  gStyle->SetCanvasPreferGL(true);
  gStyle->SetPalette(1);

  typedef std::vector<Creature*> Creatures;
  typedef std::vector<Plank*> Planks;
  Creatures creatures;

  Planks planks;
  for (unsigned int i=0; i<nCreatures; ++i)
  {
    // Spped must be < 1 otherwise collision detection problem
    Creature *creature=new Creature("Creature", r3->Rndm()*worldSize, r3->Rndm()*worldSize, r3->Rndm()*2.*pi, 30, kBlue, speed, "Bot_"+itoa(i), worldSize, debug);
    creatures.push_back(creature);
  }
  std::cout<<"Instantiated creatures."<<std::endl;
  for (unsigned int i=0; i<nPlanks; ++i)
  {
    Plank *plank=new Plank("Plank", r3->Rndm()*worldSize, r3->Rndm()*worldSize, r3->Rndm()*2.*pi, kBlue, speed, "Plank_"+itoa(i), plankLength, worldSize, debug);
    planks.push_back(plank);
  }
  std::cout<<"Instantiated planks."<<std::endl;


  std::vector <double> time_vector;
  std::vector <double> dtime_vector;

  TCanvas *c_World;
  TText *text=new TText(0.01, 0.01, "Generation 0");
  text=new TText(0.01, 0.01, "Generation 0");
  text->SetNDC();
  text->SetTextFont(42);
  if (decodeDebug(debug, 0)==1)
  {
    c_World=new TCanvas("c_World", "Natural Neural Network in Genetic Algorithm", 700, 700);
    // Safety Circle
    // TEllipse *e_safe=new TEllipse(worldSize/2., worldSize/2., 70, 70);
    // e_safe->Draw();
    c_World->Range(0,0,worldSize,worldSize);
  }


  int time=0;
  int dtime=0;
  int generation=0;

  std::cout<<"Starting."<<std::endl;
  // Time loop
  while (generation<100) {
    std::cout<<"Generation: "<<generation<<std::endl;
    std::cout<<"Start generation with: creatures "<<creatures.size()<<std::endl;
    std::cout<<"max creatures "<<nCreatures*0.3<<std::endl;
    while (creatures.size() > nCreatures*0.3) {
      // std::cin>>dtime;
      // std::cout<<"--------------------------------------------: "<<time<<std::endl;
      ++time;
      ++dtime;

      for (unsigned int i=0; i<planks.size(); i++) {
        planks.at(i)->moveForward();
      }
      if (!creatures.empty()) {
        for (int i = creatures.size() - 1; i >= 0; i--) {
          Creature::Senses senses = creatures.at(i)->getSenses(planks);
          creatures.at(i)->think(senses);
          creatures.at(i)->stepInTime();
          for (unsigned int j=0; j<planks.size(); j++) {
            bool isColliding = creatures.at(i)->isColliding(planks.at(j));
            if (isColliding) {
              std::cout<<"Collision for creature "<<i<<std::endl;

              // delete *(creatures.begin() + i);
              creatures.at(i)->deleteDraw();
              creatures.erase(creatures.begin() + i);
              std::cout<<"erased creature "<<i<<std::endl;
              std::cout<<"after collision : creatures "<<creatures.size()<<std::endl;
              break;
            }
          }
        }
      }

      // if (generation%5 == 0)
      if (true)
      {
        c_World->cd();
        for (unsigned int i=0; i<creatures.size(); ++i) creatures.at(i)->draw();
        for (unsigned int i=0; i<planks.size(); ++i) planks.at(i)->draw();
        text->Draw();
        c_World->Update();
        // c_World->SaveAs(("Movie/c_World_"+itoa(time)+".png").c_str());
        // c_World->Print("Movie/Movie_basic.gif+");
      }

      // if (true)
      // {
      //
      //   TGraph *g_dtime_time=new TGraph(dtime_vector.size(), &time_vector[0], &dtime_vector[0]);
      //   g_dtime_time->SetName("g_dtime_time");
      //   g_dtime_time->SetTitle("; time steps; Time to next meal");
      //
      //
      //   delete g_dtime_time;
      // }
    }//end alive creatures : generation
    generation++;
    // std::cout<<"creatures "<<creatures.size()<<std::endl;
    for (unsigned int i=0 ; i<70 ; ++i) {
      Creature *creature=new Creature(creatures.at(i%30), mu_newNeuron, mu_newConnection, mu_modConnection);
      creatures.push_back(creature);
    }
    // creatures.resize(100);
    std::cout<<"create new creatures "<<creatures.size()<<std::endl;
    for (unsigned int i=0; i<creatures.size(); ++i) {
      std::cout<<"draw new creature "<<i<<std::endl;
      creatures.at(i)->draw();
    };


    // Draw visualization

  }// end main loop


  delete text;
  delete myapp;
  return 0;
}
