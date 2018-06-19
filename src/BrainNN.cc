/*
==================================================
 BrainNN
=================================================
*/

#include <iostream>

#include "../models/BrainNN.h"
#include "../models/NeuralNetwork.h"
#include "../models/ToolBox.h"

// BPN::Network *  nn;

BrainNN::BrainNN(int debug): BrainWrapper()
{
  debug_=debug;
  if (decodeDebug(debug_, 2)==1)
  {
  }
  // Create neural network
  BPN::Network::Settings networkSettings{ 8, 16, 2 };
  neuralNet_ = new BPN::Network( networkSettings );
  // std::cout<<"xx."<<std::endl;
  // neuralNet_ = nn;
}

BrainNN::BrainNN(int debug, BrainNN *parentBrain, BrainNN *parentBrain_2): BrainWrapper()
{
  debug_=debug;
  double mutation_rnd = 0.2;
  std::vector<double> brain_1_weights = parentBrain->neuralNet_->getWeights();
  std::vector<double> brain_2_weights = parentBrain_2->neuralNet_->getWeights();
  std::vector<double> crossover_weigths = getCrossOverWeights(brain_1_weights, brain_2_weights);

  for (int i = 0; i < crossover_weigths.size(); i++) {
    double rnd=r3->Rndm();
    if (rnd <= mutation_rnd) {
      crossover_weigths.at(i) = -1 * crossover_weigths.at(i);
    }

    double rnd2=r3->Rndm();
    if (rnd2 <= mutation_rnd) {
      crossover_weigths.at(i) = crossover_weigths.at(i) + r3->Rndm();
    }

    double rnd3=r3->Rndm();
    if (rnd3 <= mutation_rnd) {
      crossover_weigths.at(i) = crossover_weigths.at(i) - r3->Rndm();
    }

    double rnd4=r3->Rndm();
    if (rnd4 <= mutation_rnd) {
      crossover_weigths.at(i) = crossover_weigths.at(i) * (0.5 + r3->Rndm());
    }
  }
  BPN::Network::Settings networkSettings{ 8, 16, 2 };
  neuralNet_ = new BPN::Network( networkSettings,  crossover_weigths);
  // neuralNet_ = nn;
}

BrainNN::~BrainNN()
{
  delete neuralNet_;
}

void BrainNN::think(std::vector<double> input)
{
  inputs_ = input;
}

double BrainNN::left_output()
{
  return outputs_.at(0);
}

double BrainNN::right_output()
{
  return outputs_.at(1);
}


void BrainNN::stepInTime()
{
  outputs_ = neuralNet_->Evaluate(inputs_);
}

void BrainNN::print()
{
  // for (unsigned int i=0; i<neurons_.size(); ++i)
  // {
  //   neurons_.at(i)->printSimple();
  // }
  // std::cout<<std::endl;
}


std::vector<double> BrainNN::getCrossOverWeights(std::vector<double> w1, std::vector<double> w2)
{
  std::vector<double> weights;
  int crossover_split = 0 + (rand() % static_cast<int>(w1.size() - 0 + 1)); //VERIFY INDEX RAND
  // std::cout<<"crossover_split."<<crossover_split<<std::endl;
  for (size_t i = 0; i < crossover_split; i++) {
    weights.push_back(w1[i]);
  }
  for (size_t i = crossover_split; i < w1.size(); i++) {
    weights.push_back(w2[i]);
  }
  return weights;
}
