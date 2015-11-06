#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetBackgroundAuto(false);
    ofBackground(255);
    
    // ------------------------------
    // ------ REFERENCE NOISE -------
    // ------------------------------
    
    // create terrain (black = high, white = low)
    float noiseScale = .003; // 1 = one pixel is one unit
    float noiseOffset = 0.0;
    topoNoise.allocate(ofGetWidth(), ofGetHeight(), OF_IMAGE_GRAYSCALE);
    int nPixels = ofGetWidth() * ofGetHeight();

    // pointer to beginning of pixels array
    // this stores the address of the 0th element
    // (an array is really just a pointer to a contiguous block of memory)
    unsigned char* pixelPointer = topoNoise.getPixels();
    
    // go through all pixels
    for (int i = 0; i < nPixels; i++) {
        // set where the pointer is pointing to a pixel value (perlin noise)
        // note: data type pointed to must be same as pointer type (How is this possible if the pointer index can get larger than char?)
        float px = noiseScale * (i % ofGetWidth());
        float py = noiseScale * ((int)(i / ofGetWidth()));
        *pixelPointer = (unsigned char)(round(ofNoise(px + noiseOffset, py + noiseOffset) * 255.));
        
        // print the value just assigned (the value pointed to by the pointer)
        // note: convert to int since the stored value is char
//        cout << (int)*pixelPointer << endl;
        
        // increment the pointer (the "house" that stores the address)
        pixelPointer++;
    }
    topoNoise.update();
    
    
    // ------------------------------
    // ---------- TOPOLOGY ----------
    // ------------------------------
    
    // create a new pointer (is this necessary??) at beginning
    unsigned char* pointer = topoNoise.getPixels();
    
    // allocate space for directions array
    topoNormals.allocate(ofGetWidth(), ofGetHeight(), OF_IMAGE_GRAYSCALE);
    unsigned char* normals = topoNormals.getPixels();
    
    // based on topoNoise, create a new toplogy map of the direction of declines (i.e. normals projected down into 2d)
    // loop through pixels to find their directions (0 to 255 ~ 0 to 2PI radians)
    for (int i = 0; i < ofGetHeight(); i++) { // rows
        for (int j = 0; j < ofGetWidth(); j++) { // cols
            
            // --------- HORIZONTAL -----------
            
            // pixel to Left: find the index
            int xL = (j - 1) % ofGetWidth();        // x coordinate
            int yL = i;                             // y coordinate
            int indexL = yL * ofGetWidth() + xL;    // index
            // move pointer to this index
            pointer = pointer + indexL;
            // find pixel value at this location
            int pixelL = (int)*pointer;             // pixel value to left
            pointer = pointer - indexL;             // return pointer to start
            
            // pixel to Right
            int xR = (j + 1) % ofGetWidth();
            int yR = i;
            int indexR = yR * ofGetWidth() + xR;
            pointer = pointer + indexR;
            int pixelR = (int)*pointer;
            pointer = pointer - indexR;
            
            // find the x axis normal
            int xNormal = pixelL - pixelR; // facing to right is positive
            
            // ---------- VERTICAL -----------
            
            // pixel Up
            int xU = j;
            int yU = (i - 1) % ofGetHeight();
            int indexU = yU * ofGetWidth() + xU;
            pointer = pointer + indexU;
            // find pixel value at this location
            int pixelU = (int)*pointer;
            pointer = pointer - indexU;
            
            // pixel Down
            int xD = j;
            int yD = (i + 1) % ofGetHeight();
            int indexD = yD * ofGetWidth() + xD;
            pointer = pointer + indexD;
            int pixelD = (int)*pointer;
            pointer = pointer - indexD;
            
            // find the y axis normal
            int yNormal = pixelU - pixelD; // facing down is positive
            
            // ----------- NORMAL -----------
            
            // convert these into a direction
            // NOTE: this discards the amplitude (steepness of incline)
            int angle = round(atan2((double)yNormal, (double)xNormal) / (2 * M_PI) * 255.0);
            
            // set the pixel value to the angle
            *normals = (unsigned char)angle;

            // increment pointer
            normals++;
        }
    }
    topoNormals.update();
    
    
    // ------------------------------
    // -------- SETUP AGENTS --------
    // ------------------------------
    
    // initialize the agents
    for (int i = 0; i < nAgents; i++) {
        turtle tempAgent;
        tempAgent.setPosition(ofRandom(ofGetWidth()), ofRandom(ofGetHeight()));
        tempAgent.angle = ofRandom(2 * PI);
        tempAgent.setWeight(.01);
        tempAgent.setColor(round(ofRandom(1)) * 255);
        agents.push_back(tempAgent);
    }
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
    
//    topoNoise.draw(0, 0);
//    topoNormals.draw(0, 0);
    
    // ------------------------------
    // ---- UPDATE & DRAW AGENTS ----
    // ------------------------------
    
    // agents want to "eat" the mouse; however, their environment influences the path they must take
    
    if (bStart) {
        unsigned char* pointer = topoNormals.getPixels();
        for (int i = 0; i < nAgents; i++) {
            
            // find the slope downward at agent's location
            int px = round(agents[i].x - 1);
            int py = round(agents[i].y - 1);
            int index = px + py * ofGetWidth();
            pointer = pointer + index;
            int tempAngle = (int)*pointer;
            double topoAngle = (double)tempAngle / 255. * 2 * M_PI;
            pointer = pointer - index;
            
            // find direction to mouse
            double mouseAngle = agents[i].angleTo(mouseX, mouseY);
            
            // turn toward mouse by averaging terrain and food source
            double avgAngle = (0.7 * mouseAngle + 0.3 * topoAngle) / 2;
            agents[i].angleToward(avgAngle, 0.75); // low lerps are really interesting
            
            // move forward a bit
            agents[i].forward(10);
            
            // wrap the agents
            agents[i].x = fmod(agents[i].x + ofGetWidth(), ofGetWidth());
            agents[i].y = fmod(agents[i].y + ofGetHeight(), ofGetHeight());
        }
    }
    
//    ofDrawBitmapStringHighlight(ofToString(ofGetFrameRate()) + " fps", 10, 20);

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if (key == 's') {
        bStart = !bStart;
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
