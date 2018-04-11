/*
==================================================
 Plank
=================================================
*/

#pragma once

#include "Entity.h"
#include "TLine.h"

class Plank: public Entity
{
  public:

    std::string name_;
    TLine *line_;
    double angle_;
    double length_;
    int bodyColor_;
    double speed_;
    double worldSize_;
    int debug_;
    int x1_;
    int y1_;
    int x2_;
    int y2_;

  public:

    Plank(std::string type, double x, double y, double theta, int bodyColor, double speed, std::string name, double plankLength, double worldSize, int debug = 1);

    void draw();
    void moveForward();
};
