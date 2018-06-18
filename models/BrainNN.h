/*
==================================================
 BrainNN
=================================================
*/

#pragma once

#include "BrainWrapper.h"
#include "NeuralNetwork.h"

class BrainNN : public BrainWrapper
{
  public:

    std::vector<double> inputs_;
    std::vector<int32_t> outputs_;
    BPN::Network * neuralNet_;

    int debug_;
    std::string name_;

  public:

    BrainNN(int debug);
    BrainNN(int debug, BrainNN *parentBrain, BrainNN *parentBrain_2);
    ~BrainNN();

    std::string getName();

    void think(std::vector<double> input);
    double left_output();
    double right_output();
    void stepInTime();

    void print();

  private:
    std::vector<double> getCrossOverWeights(std::vector<double> b1, std::vector<double> b2);
};
