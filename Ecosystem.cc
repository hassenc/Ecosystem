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
#include <string>
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

std::string brainType="XX";

int timeStep=2000;
int nCreatures=2;
int nPlanks=30;
double plankLength=120.;
double worldSize=500.;
double plank_speed=1.0;
double creature_speed=3.0;
int max_generation=200;
double percent_kept=0.1;
double brain_size=30;
// int timeStep=2000;
// int nCreatures=300;
// int nPlanks=30;
// double plankLength=120.;
// double worldSize=500.;
// double plank_speed=1.0;
// double creature_speed=3.0;
// int max_generation=20000;
// double percent_kept=0.1;
// double brain_size=30;

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
double mu_newConnection=0.07; //0.05
double mu_modConnection=0.07;

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
    Creature *creature=new Creature("Creature", (worldSize/4 + r3->Rndm()*worldSize/2), (worldSize/4 + r3->Rndm()*worldSize/2), r3->Rndm()*2.*pi, brainType, brain_size, kBlue, creature_speed, "Bot_"+itoa(i), worldSize, debug);
    creatures.push_back(creature);
  }
  std::cout<<"Instantiated creatures."<<std::endl;
  for (unsigned int i=0; i<nPlanks; ++i)
  {
    Plank *plank=new Plank("Plank", r3->Rndm()*worldSize, r3->Rndm()*worldSize, r3->Rndm()*2.*pi, kBlue, plank_speed, "Plank_"+itoa(i), plankLength, worldSize, debug);
    // Plank *plank=new Plank("Plank", r3->Rndm()*worldSize, r3->Rndm()*worldSize, pi, kBlue, plank_speed, "Plank_"+itoa(i), plankLength, worldSize, debug);
    planks.push_back(plank);
  }
  std::cout<<"Instantiated planks."<<std::endl;


  std::vector <double> time_vector;
  std::vector <double> dtime_vector;

  TCanvas *c_World;
  TText *text=new TText(0.01, 0.01, "Generation 0");
  // text=new TText(0.01, 0.01, "Generation 0");
  text->SetNDC();
  text->SetTextFont(42);

  TText *neuron_text_left=new TText(0.01, 0.01, "Generation 0");
  neuron_text_left->SetNDC();
  neuron_text_left->SetTextFont(10);
  TText *neuron_text_right=new TText(0.01, 0.01, "Generation 0");
  neuron_text_right->SetNDC();
  neuron_text_right->SetTextFont(10);
  TText *neuron_text_a=new TText(0.01, 0.01, "Generation 0");
  neuron_text_a->SetNDC();
  neuron_text_a->SetTextFont(10);
  TText *neuron_text_b=new TText(0.01, 0.01, "Generation 0");
  neuron_text_b->SetNDC();
  neuron_text_b->SetTextFont(10);
  TText *neuron_text_c=new TText(0.01, 0.01, "Generation 0");
  neuron_text_c->SetNDC();
  neuron_text_c->SetTextFont(10);

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
  // while (generation<=max_generation) {
  while (true) {
    std::cout<<"Generation: "<<generation<<std::endl;
    std::cout<<"Start generation with: creatures "<<creatures.size()<<std::endl;
    // bool stop_condition = creatures.size() <= nCreatures*percent_kept;
    // while (!stop_condition ||  generation == max_generation) { //generation
      // std::cin>>dtime;
      // std::cout<<"--------------------------------------------: "<<time<<std::endl;
      ++time;
      ++dtime;



      for (unsigned int i=0; i<planks.size(); i++) {
        planks.at(i)->moveForward();
      }
      creatures.at(0)->setColor(kRed);

      if (!creatures.empty()) {
        for (int i = creatures.size() - 1; i >= 0; i--) {
          std::cout<<"moving creat: "<<i<<std::endl;
          Creature::Senses senses = creatures.at(i)->getSenses(planks);
          // std::cout<<"moving creat2: "<<i<<std::endl;
          creatures.at(i)->think(senses);
          // std::cout<<"moving creat3: "<<i<<std::endl;
          creatures.at(i)->stepInTime();
          // std::cout<<"checking creature2"<<i<<std::endl;

          // creatures.at(i)->deleteDraw();
          for (unsigned int j=0; j<planks.size(); j++) {
            bool isColliding = creatures.at(i)->isColliding(planks.at(j));
            if (isColliding) {
              // std::cout<<"Collision for creature "<<i<<std::endl;
              std::cout<<"creatures.begin() "<<((dynamic_cast<BrainNN*>(creatures.at(0)->brain_))->neuralNet_->getWeights().at(0))<<std::endl;
              std::cout<<"creatures.begin() "<<((dynamic_cast<BrainNN*>(creatures.at(1)->brain_))->neuralNet_->getWeights().at(0))<<std::endl;
              std::cout<<"creatures.begin() "<<(i)<<std::endl;
              delete *(creatures.begin() + i);
              creatures.erase(creatures.begin() + i);
              int rand_best = 0 + (rand() % static_cast<int>(1 - 0));
              std::cout<<"rand_best."<<rand_best<<std::endl;

              Creature *creature;
              // std::cout<<"Instantiated planks."<<std::endl;
              if (brainType == "NN") {
                int rand_best_2 = 0 + (rand() % static_cast<int>(1 - 0));
                std::cout<<"rand2."<<rand_best_2<<std::endl;
                std::cout<<"name."<<creatures.at(0)<<std::endl;
                creature=new Creature(creatures.at(rand_best), creatures.at(rand_best_2));
                // std::cout<<"Brain created."<<std::endl;
              } else {
                creature=new Creature(creatures.at(rand_best), mu_newNeuron, mu_newConnection, mu_modConnection);
              }
              creatures.push_back(creature);
              generation++;
              break;
            }
          }
          // stop_condition = creatures.size() <= nCreatures*percent_kept;
          // if (stop_condition && generation!=max_generation) {
          //   break;
          // }
        }
      } else {
        std::cout<<"Empty creatures !!"<<std::endl;
      }


      if (generation > max_generation) {
        c_World->cd();
        for (unsigned int i=0; i<creatures.size(); ++i) creatures.at(i)->draw();
        for (unsigned int i=0; i<planks.size(); ++i) planks.at(i)->draw();
        text->SetText(0.01, 0.01, ("Generation "+itoa(generation)).c_str());


        // TString n_0 = std::to_string(creatures.at(0)->brain_->neurons_.at(0)->potential());
        // TString n_1 = std::to_string(creatures.at(0)->brain_->neurons_.at(1)->potential());
        // TString n_2 = std::to_string(creatures.at(0)->brain_->neurons_.at(2)->potential());
        // TString n_13 = std::to_string(creatures.at(0)->brain_->neurons_.at(13)->potential());
        // TString n_14 = std::to_string(creatures.at(0)->brain_->neurons_.at(14)->potential());
        // neuron_text_left->SetText(0.5, 0.01, n_0);
        // neuron_text_right->SetText(0.5, 0.03, n_1);
        // neuron_text_a->SetText(0.5, 0.06, n_2);
        // neuron_text_b->SetText(0.5, 0.09, n_13);
        // neuron_text_c->SetText(0.5, 0.12, n_14);

        text->Draw();
        neuron_text_left->Draw();
        neuron_text_right->Draw();
        neuron_text_a->Draw();
        neuron_text_b->Draw();
        neuron_text_c->Draw();
        c_World->Update();
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
    // }//end alive creatures : generation

    // std::cout<<"creatures "<<creatures.size()<<std::endl;
    // for (unsigned int i=0 ; i<(nCreatures-percent_kept*nCreatures) ; ++i) {
    //   Creature *creature=new Creature(creatures.at(i% int(percent_kept*nCreatures)), mu_newNeuron, mu_newConnection, mu_modConnection);
    //   creatures.push_back(creature);
    // }


    // Draw visualization

  }// end main loop


  delete text;
  delete myapp;
  return 0;
}
