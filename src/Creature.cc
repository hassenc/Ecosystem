/*
==================================================
 Creature

=================================================
*/

#include "../models/Creature.h"
//#include "../models/NeuralNetwork.h"
// #include "../models/Brain.h"
#include "../models/ToolBox.h"

#include <iostream>

double creature_size = 5.0;
double eye_size = 2.0;
double numberOfcaptors = 8;
double eyeAngle=pi/3;
double eyeDistance= 3.;

bool bonus_watcher_left_= false;
bool bonus_watcher_right_= false;

Creature::Creature(std::string type, double x, double y, double theta, std::string brainType, int brainSize, int bodyColor, double speed, std::string name, double worldSize, int debug): Entity(worldSize)
{
  debug_=debug;
  worldSize_=worldSize;
  type_=type;
  name_=name;
  bodyColor_=bodyColor;
  speed_=speed;
  kids_=0;
  x_=x;
  y_=y;
  theta_=theta;
  numberOfcaptors_ = numberOfcaptors;
  eyeAngle_ = eyeAngle;
  eyeDistance_ = eyeDistance;
  bonus_watcher_left_ = false;
  bonus_watcher_right_ = false;
  // visualAngle_=visualAngle;
  if (brainType == "NN") {
    brain_= new BrainNN(debug_);
  } else {
    brain_= new Brain(brainSize, debug_, name_);
  }

  if (decodeDebug(debug_, 0)==1)
  {
    circle_=new TEllipse(x_, y_, creature_size);
    circle_->SetLineColor(kBlack);
    circle_->SetFillColor(kWhite);
    left_eye=new TEllipse(x_ + eyeDistance_*cos(theta_ - eyeAngle_), y_ + eyeDistance_*sin(theta_ - eyeAngle_), eye_size);
    left_eye->SetLineColor(kBlack);
    left_eye->SetFillColor(bodyColor_);
    right_eye=new TEllipse(x_ + eyeDistance_*cos(theta_ + eyeAngle_), y_ + eyeDistance_*sin(theta_ + eyeAngle_), eye_size);
    right_eye->SetLineColor(kBlack);
    right_eye->SetFillColor(bodyColor_);
    // visRange1_=new TEllipse(x_, y_, 30, 30, 360.+(theta_-visualAngle_/2.)*180./pi, 360.+(theta_+visualAngle_/2.)*180./pi);
    // visRange2_=new TEllipse(x_, y_, 60, 60, 360.+(theta_-visualAngle_/2.)*180./pi, 360.+(theta_+visualAngle_/2.)*180./pi);
    // visRange3_=new TEllipse(x_, y_, 100, 100, 360.+(theta_-visualAngle_/2.)*180./pi, 360.+(theta_+visualAngle_/2.)*180./pi);
    // visPeriphery1_=new TLine(x_, y_, x_+100.*cos(theta_+visualAngle_/6.), y_+100.*sin(theta_+visualAngle_/6.));
    // visPeriphery2_=new TLine(x_, y_, x_+100.*cos(theta_-visualAngle_/6.), y_+100.*sin(theta_-visualAngle_/6.));
    // visRange1_->SetFillStyle(0);
    // visRange2_->SetFillStyle(0);
    // visRange3_->SetFillStyle(0);
    // visRange1_->SetLineColor(bodyColor_);
    // visRange2_->SetLineColor(bodyColor_);
    // visRange3_->SetLineColor(bodyColor_);
    // visPeriphery1_->SetLineColor(bodyColor_);
    // visPeriphery2_->SetLineColor(bodyColor_);
  }
}

Creature::Creature(Creature *parentCreature, double mu_newNeuron, double mu_newConnection, double mu_modConnection): Entity(parentCreature->worldSize_)
{
  ++(parentCreature->kids_);
  debug_=parentCreature->debug_;
  worldSize_=parentCreature->worldSize_;
  type_=parentCreature->type_;
  name_=parentCreature->name_+"_"+itoa(parentCreature->kids_);
  bodyColor_=parentCreature->bodyColor_;
  speed_=parentCreature->speed_;
  numberOfcaptors_ = numberOfcaptors;
  eyeAngle_ = eyeAngle;
  eyeDistance_ = eyeDistance;
  kids_=0;
  x_=worldSize_/4 + r3->Rndm()*parentCreature->worldSize_/2;
  y_=worldSize_/4 + r3->Rndm()*parentCreature->worldSize_/2;
  theta_=parentCreature->theta_;

  bonus_watcher_left_ = false;
  bonus_watcher_right_ = false;
  // std::cout<<"old visual angle = "<<visualAngle_<<std::endl;
  // visualAngle_=parentCreature->visualAngle_+mu_visualAngle*(-0.5+r3->Uniform());
  // std::cout<<" new visual angle = "<<visualAngle_<<std::endl;
  // if (visualAngle_<0) visualAngle_=0;
  // if (visualAngle_>pi) visualAngle_=pi;
  if (decodeDebug(debug_, 0)==1)
  {
    circle_=new TEllipse(x_, y_, creature_size);
    circle_->SetLineColor(kBlack);
    circle_->SetFillColor(kWhite);
    left_eye=new TEllipse(x_ + eyeDistance_*cos(theta_ - eyeAngle_), y_ + eyeDistance_*sin(theta_ - eyeAngle_), eye_size);
    left_eye->SetLineColor(kBlack);
    left_eye->SetFillColor(bodyColor_);
    right_eye=new TEllipse(x_ + eyeDistance_*cos(theta_ + eyeAngle_), y_ + eyeDistance_*sin(theta_ + eyeAngle_), eye_size);
    right_eye->SetLineColor(kBlack);
    right_eye->SetFillColor(bodyColor_);
  }


  brain_=new Brain( dynamic_cast<Brain*>(parentCreature->brain_), 0, debug_, name_, mu_newConnection, mu_modConnection, mu_newNeuron);
}

Creature::Creature(Creature *parentCreature, Creature *parentCreature_2): Entity(parentCreature->worldSize_)
{
  ++(parentCreature->kids_);
  debug_=parentCreature->debug_;
  worldSize_=parentCreature->worldSize_;
  type_=parentCreature->type_;
  name_=parentCreature->name_+"_"+itoa(parentCreature->kids_);
  bodyColor_=parentCreature->bodyColor_;
  speed_=parentCreature->speed_;
  numberOfcaptors_ = numberOfcaptors;
  eyeAngle_ = eyeAngle;
  eyeDistance_ = eyeDistance;
  kids_=0;
  x_=worldSize_/4 + r3->Rndm()*parentCreature->worldSize_/2;
  y_=worldSize_/4 + r3->Rndm()*parentCreature->worldSize_/2;
  theta_=parentCreature->theta_;

  if (decodeDebug(debug_, 0)==1)
  {
    circle_=new TEllipse(x_, y_, creature_size);
    circle_->SetLineColor(kBlack);
    circle_->SetFillColor(kWhite);
    left_eye=new TEllipse(x_ + eyeDistance_*cos(theta_ - eyeAngle_), y_ + eyeDistance_*sin(theta_ - eyeAngle_), eye_size);
    left_eye->SetLineColor(kBlack);
    left_eye->SetFillColor(bodyColor_);
    right_eye=new TEllipse(x_ + eyeDistance_*cos(theta_ + eyeAngle_), y_ + eyeDistance_*sin(theta_ + eyeAngle_), eye_size);
    right_eye->SetLineColor(kBlack);
    right_eye->SetFillColor(bodyColor_);
  }

  brain_= new BrainNN(debug_, dynamic_cast<BrainNN*>(parentCreature->brain_), dynamic_cast<BrainNN*>(parentCreature_2->brain_));
}

Creature::~Creature()
{
  if (decodeDebug(debug_, 0)==1)
  {
    circle_->Delete();
    left_eye->Delete();
    right_eye->Delete();
    // visRange1_->Delete();
    // visRange2_->Delete();
    // visRange3_->Delete();
    // visPeriphery1_->Delete();
    // visPeriphery2_->Delete();
  }
  delete brain_;
}

void Creature::deleteDraw()
{
  if (decodeDebug(debug_, 0)==1)
  {
    circle_->Delete();
    left_eye->Delete();
    right_eye->Delete();
  }
}

void Creature::draw()
{
  if (decodeDebug(debug_, 0)==1)
  {
    circle_->SetX1(x_);
    circle_->SetY1(y_);
    left_eye->SetX1(x_ + eyeDistance_*cos(theta_ - eyeAngle_));
    left_eye->SetY1(y_ + eyeDistance_*sin(theta_ - eyeAngle_));
    right_eye->SetX1(x_ + eyeDistance_*cos(theta_ + eyeAngle_));
    right_eye->SetY1(y_ + eyeDistance_*sin(theta_ + eyeAngle_));

    circle_->Draw();
    left_eye->Draw();
    right_eye->Draw();
  }
}

void Creature::setColor(int color)
{
  circle_->SetFillColor(color);
}
// void Creature::draw()
// {
//   if (decodeDebug(debug_, 0)==1)
//   {
//     circle_->SetX1(x_);
//     circle_->SetY1(y_);
//     double angle1=360.+(theta_-visualAngle_/2.)*180./pi;
//     double angle2=360.+(theta_+visualAngle_/2.)*180./pi;
//     visRange1_->SetX1(x_);
//     visRange1_->SetY1(y_);
//     visRange1_->SetPhimin(angle1);
//     visRange1_->SetPhimax(angle2);
//     visRange2_->SetX1(x_);
//     visRange2_->SetY1(y_);
//     visRange2_->SetPhimin(angle1);
//     visRange2_->SetPhimax(angle2);
//     visRange3_->SetX1(x_);
//     visRange3_->SetY1(y_);
//     visRange3_->SetPhimin(angle1);
//     visRange3_->SetPhimax(angle2);
//     visPeriphery1_->SetX1(x_);
//     visPeriphery1_->SetY1(y_);
//     visPeriphery1_->SetX2(x_+100.*cos(theta_+visualAngle_/6.));
//     visPeriphery1_->SetY2(y_+100.*sin(theta_+visualAngle_/6.));
//     visPeriphery2_->SetX1(x_);
//     visPeriphery2_->SetY1(y_);
//     visPeriphery2_->SetX2(x_+100.*cos(theta_-visualAngle_/6.));
//     visPeriphery2_->SetY2(y_+100.*sin(theta_-visualAngle_/6.));
//
//     circle_->Draw();
//     visRange1_->Draw();
//     visRange2_->Draw();
//     visRange3_->Draw();
//     visPeriphery1_->Draw();
//     visPeriphery2_->Draw();
//   }
// }



void Creature::moveForward()
{
  x_=x_+speed_*cos(theta_);
  y_=y_+speed_*sin(theta_);
  // bouncyBoundaries();
  circularBoundaries();
}

void Creature::moveBackward()
{
  x_=x_-speed_*cos(theta_);
  y_=y_-speed_*sin(theta_);
  // bouncyBoundaries();
}

bool Creature::isColliding(Plank *plank)
{
  // TODO make circle_->GetX1 more generic
  double x1;
  double y1;
  double x2;
  double y2;
  double x0;
  double y0;
  double distance_to_plank;
  double distance_to_plank_center;
  double max_distance_to_line;
  double max_distance_to_plank_center;
  x1 = plank->x1_;
  y1 = plank->y1_;
  x2 = plank->x2_;
  y2 = plank->y2_;
  x0 = this->x_;
  y0 = this->y_;
  distance_to_plank = fabs((y2-y1)*x0-(x2-x1)*y0+x2*y1-y2*x1)/distance(x1,y1,x2,y2); // this is the distance from point to line
  max_distance_to_line = (plank->speed_ + this->speed_)/2; // if line and plank are going toward each other, they get closer by the sum of speeds every step
  max_distance_to_plank_center = sqrt(pow(max_distance_to_line,2) + pow(plank->length_/2,2)); //max distance when going toward each other and point is at the edge of the plank
  distance_to_plank_center = distance(x0,y0,(x2 + x1)/2.,(y1 + y2)/2.);
  return round(distance_to_plank) <= max_distance_to_line && distance_to_plank_center <= max_distance_to_plank_center;
}


Creature::Senses Creature::getSenses(std::vector<Plank*> planks) {
  // Creature::Senses senses;
  std::vector<double> senses;
  double angle;
  double sens = 0;
  for (unsigned int i=0; i<this->numberOfcaptors_; ++i)
  {

    angle = i * pi * 2 / this->numberOfcaptors_;
    double res = this->getNearestDistanceForAngle(planks,  angle);
    // sens = 1 - (res/ (worldSize_*sqrt(2)))*2;
    sens = 1 - (res/ (worldSize_*sqrt(2)));
    // if (res < (worldSize_/2)) {
    //   // sens = 1;
    // } else {
    //   sens = -1;
    // }
    senses.push_back(sens);
  }
  // std::cout<<"----------------"<<std::endl;
  // std::cout<<"getSenses."<<senses.at(0)<<std::endl;
  // std::cout<<"getSenses."<<senses.at(1)<<std::endl;
  // std::cout<<"getSenses."<<senses.at(2)<<std::endl;
  // std::cout<<"getSenses."<<senses.at(3)<<std::endl;
  // std::cout<<"getSenses."<<senses.at(4)<<std::endl;
  // std::cout<<"getSenses."<<senses.at(5)<<std::endl;
  // std::cout<<"getSenses."<<senses.at(6)<<std::endl;
  // std::cout<<"getSenses."<<senses.at(7)<<std::endl;
  // std::cout<<"----------------"<<std::endl;
  return senses;
}

double Creature::getNearestDistanceForAngle(std::vector<Plank*> planks, double angle) {
  double ax;
  double ay;
  double x;
  double y;
  double max_dist = worldSize_*sqrt(2);
  double dist = max_dist;
  ax = cos(this->theta_ + angle);
	ay = sin(this->theta_ + angle);
  x = this->x_ + ax;
	y = this->y_ + ay;
  // std::cout<<"x."<<x<<std::endl;
  while (x < worldSize_ && x >= 0 && y < worldSize_ && y >= 0 && dist == max_dist)
  {
    // TEllipse *circle =new TEllipse(x, y, 0.1);
    //TODO test if x,y is on segment by looping on segments here
    for (unsigned int i=0; i<planks.size(); ++i) {
      if (isOnSegment(x,y, planks.at(i)->x1_, planks.at(i)->y1_, planks.at(i)->x2_, planks.at(i)->y2_)) {
        dist = distance(this->x_ , this->y_, x, y);
        break;
      };
    };
		x = x + ax;
		y = y + ay;
  };
  // std::cout<<"x last."<<x<<std::endl;
  // std::cout<<"y. last"<<y<<std::endl;
  return dist;
}
//
// void Creature::seeEntity(Entity *entity)
// {
//   if (entity!=this)
//   {
//     double x=entity->x_;
//     double y=entity->y_;
//     double distsq=pow(x_-x, 2)+pow(y_-y, 2);
//     if (distsq<10000) // If beyond this, it doesn't see it
//     {
//       double thetac=convertToZeroToPi(atan2((y-y_), (x-x_)));
//       bool seen=false;
//       if (inBetween(thetac, theta_-visualAngle_/6., theta_-visualAngle_/2.))
//       {
//         brain_->neurons_.at(3)->receive(1);
//         seen=true;
//       }
//       else if (inBetween(thetac, theta_+visualAngle_/6., theta_-visualAngle_/6.))
//       {
//         brain_->neurons_.at(4)->receive(1);
//         seen=true;
//       }
//       else if (inBetween(thetac, theta_+visualAngle_/2., theta_+visualAngle_/6.))
//       {
//         brain_->neurons_.at(5)->receive(1);
//         seen=true;
//       }
//
//       if (seen)
//       {
//         // std::cout<<"Seen within fov"<<std::endl;
//         // std::cout<<"theta_ = "<<theta_<<", thetac = "<<thetac<<" (x = "<<x<<", y = "<<y<<", x_ = "<<x_<<", y_ = "<<y<<")"<<std::endl;
//         if (distsq<900)
//         {
//           brain_->neurons_.at(0)->receive(1);
//         }
//         else if (distsq<3600)
//         {
//           brain_->neurons_.at(1)->receive(1);
//         }
//         else
//         {
//           brain_->neurons_.at(2)->receive(1);
//         }
//
//         // What kind of an entity is seen?
//         std::string type=entity->type_;
//         if (type=="Plank")
//         {
//           brain_->neurons_.at(6)->receive(1);
//         }
//         else if (type=="Creature")
//         {
//           brain_->neurons_.at(7)->receive(1);
//         }
//         else if (type=="Predator")
//         {
//           brain_->neurons_.at(8)->receive(1);
//         }
//         else
//         {
//           std::cout<<"ERROR: Entity seen has no known type!"<<std::endl;
//         }
//       }
//     }
//   }
// }
//
// void Creature::seePlanks(std::vector<Plank*> *planks)
// {
//   for (unsigned int i=0; i<planks->size(); ++i)
//   {
//     seeEntity((Entity*)planks.at(i));
//   }
// }
//
// void Creature::seeCreatures(std::vector<Creature*> *bots)
// {
//   for (unsigned int i=0; i<bots->size(); ++i)
//   {
//     seeEntity((Entity*)bots->at(i));
//   }
// }

void Creature::think(Senses senses)
{
  brain_->think(senses);
}

void Creature::stepInTime()
{
  brain_->stepInTime();
  // brain_->print();
  // if (brain_->neurons_.at(12)->potential()>0.4) moveForward();
  // std::cout<<" at 14 = "<<brain_->neurons_.at(13)->potential()<<std::endl;
  if (brain_->left_output()>0.2) {
    bonus_watcher_left_ = true;
    turnLeft();
    moveForward();
  }
  if (brain_->right_output()>0.2) {
    bonus_watcher_right_ = true;
    turnRight();
    moveForward();
  }
  // if (brain_->neurons_.at(15)->potential()>0.4) moveBackward();
}
//
// void Creature::printBrain()
// {
//   brain_->print();
// }
