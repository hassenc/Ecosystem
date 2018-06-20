/*
==================================================
 Creature
=================================================
*/

#pragma once


#include "Plank.h"
#include "BrainWrapper.h"
#include "Brain.h"
#include "BrainNN.h"
#include "Entity.h"
#include "TLine.h"

class Creature: public Entity
{
  public:

    typedef std::vector<double> Senses;
    typedef std::vector<Plank*> Planks;

    BrainWrapper *brain_;
    std::string name_;
    TEllipse *left_eye, *right_eye;
    // TEllipse *visRange1_, *visRange2_, *visRange3_;
    TLine *visPeriphery1_, *visPeriphery2_;
    double visualAngle_;
    int bodyColor_;
    double speed_;
    double worldSize_;
    int life_time_ = 0;
    int nbr_actions_ = 0;
    int debug_;
    int kids_;
    double eyeAngle_;
    double eyeDistance_;
    double numberOfcaptors_;
    bool bonus_watcher_left_;
    bool bonus_watcher_right_;

  public:

    Creature(std::string type, double x, double y, double theta, std::string brainType, int brainSize, int bodyColor, double speed, std::string name, double worldSize, int debug = 1);
    Creature(Creature *parentCreature, double mu_newNeuron, double mu_newConnection, double mu_modConnection);
    Creature(Creature *parentCreature, Creature *parentCreature_2);
    ~Creature();

    void draw();
    void deleteDraw();
    void moveForward();
    void moveBackward();
    void setColor(int bodyColor);
    // void seeEntity(Entity *entity);
    bool isColliding(Plank *plank);
    bool isHiding();
    Senses getSenses(std::vector<Plank*> planks);
    double getNearestDistanceForAngle(std::vector<Plank*> planks, double angle);
    // void seePlanks(std::vector<Plank*> *planks);
    // void seeCreatures(std::vector<Creature*> *creatures);

    void think(Senses senses);
    void stepInTime();

    void printBrain();
};
