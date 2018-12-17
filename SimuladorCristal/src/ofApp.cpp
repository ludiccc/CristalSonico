#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 5; j++) {
            cristales[i][j].setup(ofVec3f(j*40,0,i*40));
            cristales[i][j].c = ofColor(0);
        }
    }
    ofEnableDepthTest();

    // listen on the given port
    ofLog() << "listening for osc messages on port " << PORT;
    receiver.setup(PORT);
}

//--------------------------------------------------------------
void ofApp::update(){
    // check for waiting messages
    while(receiver.hasWaitingMessages()){
        
        // get the next message
        ofxOscMessage m;
        receiver.getNextMessage(m);

        // primero chequeo a qué hace referencia:
        int i, j;
        if (m.getAddress().find("element") != string::npos) { // hay una referencia a un elemento en particular
            int idx = stoi(m.getAddress().substr(m.getAddress().find("element")+8,m.getAddress().length()-1-m.getAddress().find("element")+8));
            j = idx / 4;
            i = idx - j*4;
        } else if (m.getAddress().find("row") != string::npos) { // hay una referencia a un fila en particular
        } else if (m.getAddress().find("col") != string::npos) { // hay una referencia a un columna en particular
        } else if (m.getAddress().find("all") != string::npos) { // hay una referencia a todos
        } else { // hubo algún error en la indicación.
            
        }
        if (m.getAddress().find("setPosition") != string::npos) {
            cristales[i][j].goTo(m.getArgAsFloat(0));
        } else if (m.getAddress().find("setColor") != string::npos) {
            cristales[i][j].c = ofColor(m.getArgAsInt(0), m.getArgAsInt(1), m.getArgAsInt(2));
        }
    }
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 5; j++) {
            cristales[i][j].update();
        }
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    cam.begin();
    ofBackground(128);
    ofPushStyle();
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 5; j++) {
            cristales[i][j].draw();
        }
    }
    ofPopStyle();
    cam.end();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    switch(key) {
        case ' ':
            cam.getOrtho() ? cam.disableOrtho() : cam.enableOrtho();
            break;
        case 'C':
        case 'c':
            cam.getMouseInputEnabled() ? cam.disableMouseInput() : cam.enableMouseInput();
            break;
        case 'F':
        case 'f':
            ofToggleFullscreen();
            break;
        case 'H':
        case 'h':
            bHelpText ^=true;
            break;
        case 'I':
        case 'i':
            cam.getInertiaEnabled() ? cam.disableInertia() : cam.enableInertia();
            break;
        case 'Y':
        case 'y':
            cam.setRelativeYAxis(!cam.getRelativeYAxis());
            break;
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
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

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
