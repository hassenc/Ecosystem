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
  std::cout<<"xx."<<std::endl;
  // neuralNet_ = nn;
}

BrainNN::BrainNN(int debug, BrainNN *parentBrain, BrainNN *parentBrain_2): BrainWrapper()
{
  debug_=debug;
  std::vector<double> brain_1_weights = parentBrain->neuralNet_->getWeights();
  std::vector<double> brain_2_weights = parentBrain_2->neuralNet_->getWeights();
  std::vector<double> crossover_weigths = getCrossOverWeights(brain_1_weights, brain_2_weights);

  BPN::Network::Settings networkSettings{ 8, 16, 2 };
  std::cout<<"yy."<<std::endl;
  neuralNet_ = new BPN::Network( networkSettings,  crossover_weigths);
  std::cout<<"zz."<<std::endl;
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
  // std::cout<<"Evaluate."<<inputs_.size()<<std::endl;
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
  std::cout<<"crossover_split."<<crossover_split<<std::endl;
  for (size_t i = 0; i < crossover_split; i++) {
    weights.push_back(w1[i]);
  }
  for (size_t i = crossover_split; i < w1.size(); i++) {
    weights.push_back(w2[i]);
  }
  return weights;
}
