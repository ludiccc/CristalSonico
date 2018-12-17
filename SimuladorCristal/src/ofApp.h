#pragma once

#include "ofMain.h"
#include "cristal.hpp"
#include "ofxOsc.h"

// listening port
#define PORT 12345


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
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);

    ofEasyCam cam; // add mouse controls for camera movement
    bool bHelpText;
    ofLight light;

    Cristal cristales[4][5];

    ofxOscReceiver receiver;

};
