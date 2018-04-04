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
// #include "interface/Neuron.h"
// #include "interface/Brain.h"
// #include "interface/Fire.h"
// #include "interface/Food.h"
#include "models/ToolBox.h"
#include "interface/CommandLineArguments.h"

int timeStep=200;
int nCreatures=1;
double worldSize=700;

int seed=100;

// Debug Levels
// bits: xxxx
// bit 0 = TCanvas visualization
// bit 1 = Verbalization
// bit 2 = Fill histograms
// bit 3 = Draw the histograms
int debug = 0x2;

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
  Creatures creatures;
  for (unsigned int i=0; i<nCreatures; ++i)
  {
    Creature *creature=new Creature("Creature", r3->Rndm()*worldSize, r3->Rndm()*worldSize, r3->Rndm()*2.*pi, pi/4., 30, kBlue, 1.0, "Bot_"+itoa(i), worldSize, debug);
    creatures.push_back(creature);
  }
  std::cout<<"Instantiated creatures."<<std::endl;


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
  std::cout<<"Starting."<<std::endl;
  // Time loop
  while (time<1000)
  {
    // std::cout<<"Time: "<<time<<std::endl;
    ++time;
    ++dtime;

    for (unsigned int i=0; i<creatures.size(); ++i)
    {
      // creatures.at(i)->seeFoods(&foods);
      // creatures.at(i)->seeBots(&creatures);
      // creatures.at(i)->seeBots(&predators);
      creatures.at(i)->moveForward();
      creatures.at(i)->stepInTime();
    }

    // Draw visualization
    if (true)
    {
      c_World->cd();
      for (unsigned int i=0; i<creatures.size(); ++i) creatures.at(i)->draw();
      text->Draw();
      c_World->Update();
      // c_World->SaveAs(("Movie/c_World_"+itoa(time)+".png").c_str());
      // c_World->Print("Movie/Movie_basic.gif+");
    }

    if (true)
    {

      TGraph *g_dtime_time=new TGraph(dtime_vector.size(), &time_vector[0], &dtime_vector[0]);
      g_dtime_time->SetName("g_dtime_time");
      g_dtime_time->SetTitle("; time steps; Time to next meal");


      delete g_dtime_time;
    }
  }


  delete text;
  delete myapp;
  return 0;
}
