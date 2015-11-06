//
//  turtle.cpp
//  reactive_agents
//
//  Created by Ben Snell on 11/5/15.
//
//

#include "turtle.h"

void turtle::setPosition(double x_, double y_) {
    x = x_;
    y = y_;
}

void turtle::left(double angle_) {
    angle -= angle_;
}

void turtle::right(double angle_) {
    angle += angle_;
}

void turtle::forward(double dist_) {
    double newX = x + cos(angle) * dist_;
    double newY = y + sin(angle) * dist_;
    if (penIsDown) {
        ofSetColor(color);
        ofSetLineWidth(weight);
        ofLine(x, y, newX, newY);
    }
    x = newX;
    y = newY;
}

void turtle::back(double dist_) {
    double newX = x - cos(angle) * dist_;
    double newY = y - sin(angle) * dist_;
    if (penIsDown) {
        ofSetColor(color);
        ofSetLineWidth(weight);
        ofLine(x, y, newX, newY);
    }
    x = newX;
    y = newY;
}

void turtle::penDown() {
    penIsDown = true;
}

void turtle::penUp() {
    penIsDown = false;
}

void turtle::goTo(double x_, double y_) {
    if (penIsDown) {
        ofSetColor(color);
        ofSetLineWidth(weight);
        ofLine(x, y, x_, y_);
    }
    x = x_;
    y = y_;
}

double turtle::distanceTo(double x_, double y_) {
    return sqrt(pow(x - x_, 2) + pow(y - y_, 2));
}

double turtle::angleTo(double x_, double y_) {
    double absAngle = atan2(y_ - y, x_ - x);
    double thisAngle = fmod(absAngle - angle + 2 * M_PI, 2 * M_PI);
    return thisAngle;
}

void turtle::turnToward(double x_, double y_, double angle_) {
    double absAngle = atan2(y_ - y, x_ - x);
    double thisAngle = fmod(absAngle - angle + 2 * M_PI, 2 * M_PI);
    if (thisAngle < M_PI) {
        angle += angle_;
    } else {
        angle -= angle_;
    }
}

void turtle::angleToward(double angle_, double amount_) {
    double angle1 = angle + 2 * M_PI;
    double angle2 = angle_ + 2 * M_PI;
    double newAngle = ofLerpRadians(angle1, angle2, amount_);
    angle += newAngle;
    angle = fmod(angle, 2 * M_PI);
//    if (angle_ < M_PI) {
//        angle += amount_;
//    } else {
//        angle -= amount_;
//    }
    
}


void turtle::setColor(ofColor color_) {
    color = color_;
}

void turtle::setWeight(double weight_) {
    weight = weight_;
}

void turtle::face(double angle_) {
    angle = angle_;
}