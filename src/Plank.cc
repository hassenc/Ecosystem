/*
==================================================
 Plank

=================================================
*/

#include "../models/Plank.h"
#include "../models/ToolBox.h"

#include <iostream>

Plank::Plank(std::string type, double x, double y, double theta, int bodyColor, double speed, std::string name, double length, double worldSize, int debug): Entity(worldSize)
{
  debug_=debug;
  worldSize_=worldSize;
  type_=type;
  name_=name;
  bodyColor_=bodyColor;
  speed_=speed;
  x_=x;
  y_=y;
  length_=length;
  theta_=theta;
  if (decodeDebug(debug_, 0)==1)
  {
    circle_=new TEllipse(x, y, 2.);
    line_=new TLine(x-(length_/2.)*cos(pi/2-theta_), y+(length_/2.)*sin(pi/2-theta_), x+(length_/2.)*cos(pi/2-theta_), y-(length_/2.)*sin(pi/2-theta_));
    circle_->SetLineColor(kBlack);
    circle_->SetFillColor(bodyColor_);
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
  //   visPeriphery1_->SetLineColor(bodyColor_);
  //   visPeriphery2_->SetLineColor(bodyColor_);
  }
}

void Plank::draw()
{
  if (decodeDebug(debug_, 0)==1)
  {
    circle_->SetX1(x_);
    circle_->SetY1(y_);
    line_->SetX1(x1_);
    line_->SetY1(y1_);
    line_->SetX2(x2_);
    line_->SetY2(y2_);
    // double angle1=360.+(theta_-visualAngle_/2.)*180./pi;`
    // double angle2=360.+(theta_+visualAngle_/2.)*180./pi;`
    // visRange1_->SetX1(x_);
    // visRange1_->SetY1(y_);
    // visRange1_->SetPhimin(angle1);
    // visRange1_->SetPhimax(angle2);
    // visRange2_->SetX1(x_);
    // visRange2_->SetY1(y_);
    // visRange2_->SetPhimin(angle1);
    // visRange2_->SetPhimax(angle2);
    // visRange3_->SetX1(x_);
    // visRange3_->SetY1(y_);
    // visRange3_->SetPhimin(angle1);
    // visRange3_->SetPhimax(angle2);
    // visPeriphery1_->SetX1(x_);
    // visPeriphery1_->SetY1(y_);
    // visPeriphery1_->SetX2(x_+100.*cos(theta_+visualAngle_/6.));
    // visPeriphery1_->SetY2(y_+100.*sin(theta_+visualAngle_/6.));
    // visPeriphery2_->SetX1(x_);
    // visPeriphery2_->SetY1(y_);
    // visPeriphery2_->SetX2(x_+100.*cos(theta_-visualAngle_/6.));
    // visPeriphery2_->SetY2(y_+100.*sin(theta_-visualAngle_/6.));

    circle_->Draw();
    line_->Draw();
    // visRange1_->Draw();
    // visRange2_->Draw();
    // visRange3_->Draw();
    // visPeriphery1_->Draw();
    // visPeriphery2_->Draw();
  }
}

void Plank::moveForward()
{
  x_=x_+speed_*cos(theta_);
  y_=y_+speed_*sin(theta_);
  x1_=x_-(length_/2.)*cos(pi/2-theta_);
  y1_=y_+(length_/2.)*sin(pi/2-theta_);
  x2_=x_+(length_/2.)*cos(pi/2-theta_);
  y2_=y_-(length_/2.)*sin(pi/2-theta_);
  circularBoundaries();
}
