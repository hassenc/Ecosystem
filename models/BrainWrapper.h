/*
==================================================
 BrainWrapper
=================================================
*/

#pragma once

#include <vector>

class BrainWrapper
{
  public:
    virtual ~BrainWrapper() {};
    virtual void stepInTime() {};
    virtual double left_output() = 0;
    virtual double right_output() = 0;
    virtual void think(std::vector<double> input) {};
};
