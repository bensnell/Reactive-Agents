#pragma once

#include "ofMain.h"
#include "turtle.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
    
    ofImage topoNoise;      // stores topology (terrain) of perlin noise
    ofImage topoNormals;    // stores the tangents to surfaces
    
    vector<turtle> agents;  // all the agents
    int nAgents = 10000;  // number of agents
    
    Boolean bStart = false;
		
};
