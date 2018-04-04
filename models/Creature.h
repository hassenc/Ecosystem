/*
==================================================
 Creature
=================================================
*/

#pragma once


#include "Entity.h"
#include "TLine.h"

class Creature: public Entity
{
  public:

    // Brain *brain_;
    std::string name_;
    TEllipse *visRange1_, *visRange2_, *visRange3_;
    TLine *visPeriphery1_, *visPeriphery2_;
    double visualAngle_;
    int bodyColor_;
    double speed_;
    double worldSize_;
    int debug_;
    int kids_;

  public:

    Creature(std::string type, double x, double y, double theta, double visualAngle, int brainSize, int bodyColor, double speed, std::string name, double worldSize, int debug = 1);
    Creature(Creature *parentCreature, double mu_newNeuron, double mu_newConnection, double mu_modConnection, double mu_visualAngle);
    ~Creature();

    void draw();
    void moveForward();
    void moveBackward();
    // void seeEntity(Entity *entity);
    // void seePlanks(std::vector<Plank*> *planks);
    // void seeCreatures(std::vector<Creature*> *creatures);

    void stepInTime();

    void printBrain();
};
