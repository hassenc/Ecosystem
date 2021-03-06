/*
==================================================
 Creature
=================================================
*/

#pragma once


#include "Plank.h"
#include "Brain.h"
#include "Entity.h"
#include "TLine.h"

class Creature: public Entity
{
  public:

    typedef std::vector<double> Senses;
    typedef std::vector<Plank*> Planks;

    Brain *brain_;
    std::string name_;
    TEllipse *left_eye, *right_eye;
    // TEllipse *visRange1_, *visRange2_, *visRange3_;
    TLine *visPeriphery1_, *visPeriphery2_;
    double visualAngle_;
    int bodyColor_;
    double speed_;
    double worldSize_;
    int debug_;
    int kids_;
    double eyeAngle_;
    double eyeDistance_;
    double numberOfcaptors_;
    bool bonus_watcher_left_;
    bool bonus_watcher_right_;

  public:

    Creature(std::string type, double x, double y, double theta, int brainSize, int bodyColor, double speed, std::string name, double worldSize, int debug = 1);
    Creature(Creature *parentCreature, double mu_newNeuron, double mu_newConnection, double mu_modConnection);
    ~Creature();

    void draw();
    void deleteDraw();
    void moveForward();
    void moveBackward();
    void setColor(int bodyColor);
    // void seeEntity(Entity *entity);
    bool isColliding(Plank *plank);
    Senses getSenses(std::vector<Plank*> planks);
    double getNearestDistanceForAngle(std::vector<Plank*> planks, double angle);
    // void seePlanks(std::vector<Plank*> *planks);
    // void seeCreatures(std::vector<Creature*> *creatures);

    void think(Senses senses);
    void stepInTime();

    void printBrain();
};
