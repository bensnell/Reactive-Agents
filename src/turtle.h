//
//  turtle.h
//  reactive_agents
//
//  Created by Ben Snell on 11/5/15. Taken directly from Roger's and Golan's Turtle class found here: http://cmuems.com/2015c/deliverables/turtle-graphics/
//
//

#ifndef __reactive_agents__turtle__
#define __reactive_agents__turtle__

#include <ofMain.h>


class turtle {
    
public:
    double x;
    double y;
    double angle;
    Boolean penIsDown = true;
    ofColor color = ofColor(0);
    double weight = 1;
    
    void setPosition (double x_, double y_);
    
    void left (double angle_);  // radians
    void right (double angle_); // radians
    void forward (double dist_);
    void back (double dist_);
    
    void penDown();
    void penUp();
    
    void goTo (double x_, double y_);
    double distanceTo (double x_, double y_);
    double angleTo (double x_, double y_);
    void turnToward (double x_, double y_, double angle_);
    void angleToward (double angle_, double amount_);
    
    void setColor (ofColor color_);
    void setWeight (double weight_);
    void face (double angle_);
};














#endif /* defined(__reactive_agents__turtle__) */
