#include "ofApp.h"


std::vector<std::string> split(const std::string& s, char delimiter)
{
    std::vector<std::string> tokens;
    std::string token;
    std::istringstream tokenStream(s);
    while (std::getline(tokenStream, token, delimiter))
    {
        tokens.push_back(token);
    }
    return tokens;
}
//--------------------------------------------------------------
void ofApp::setup(){
    for (int q = 0; q < 5; q++) {
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 5; j++) {
                cristales[q][i][j].setup(ofVec3f(j*40,0,i*40));
                cristales[q][i][j].c = ofColor(0);
            }
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

        int module = 0;
        int submodule = MODULE_ALL;
        int submoduleidx = 0;
        std::string command = "";
        
        std::vector<std::string> splitedMessage;
        splitedMessage = split(m.getAddress(), '/');

        if (splitedMessage.size() >= 1) command = splitedMessage[1];
        if (splitedMessage.size() >= 2) module = stoi(splitedMessage[2]);
        if (splitedMessage.size() >= 3) {
            if (splitedMessage[3].find("element") != string::npos) submodule = MODULE_ELEMENT;
            else if (splitedMessage[3].find("column") != string::npos) submodule = MODULE_COL;
            else if (splitedMessage[3].find("row") != string::npos) submodule = MODULE_ROW;
            else if (splitedMessage[3].find("all") != string::npos) submodule = MODULE_ALL;
            else if (splitedMessage[3].find("group") != string::npos) submodule = MODULE_GROUP;
        }
        if (splitedMessage.size() >= 4) submoduleidx = stoi(splitedMessage[4]);

        /*// primero chequeo a qué hace referencia:
        int q, i, j;
        if (m.getAddress().find("element") != string::npos) { // hay una referencia a un elemento en particular
            //int elemPos = m.getAddress().substr(m.getAddress().find("element");
            
            int idx = stoi(m.getAddress().substr(m.getAddress().find("element")+8,m.getAddress().length()-1-m.getAddress().find("element")+8));
            q = 0; //stoi(m.getAddress().substr(m.getAddress().find("element")-2;
            j = idx / 4;
            i = idx - j*4;
        } else if (m.getAddress().find("row") != string::npos) { // hay una referencia a un fila en particular
        } else if (m.getAddress().find("col") != string::npos) { // hay una referencia a un columna en particular
        } else if (m.getAddress().find("all") != string::npos) { // hay una referencia a todos
        } else { // hubo algún error en la indicación.
            
        }*/
        
        switch(submodule) {
            case MODULE_ELEMENT:
                doCommand(command, module, submoduleidx, m);
                break;
            default:
                break;
        }
        
    }
    for (int q = 0; q < 5; q++) {
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 5; j++) {
                cristales[q][i][j].update();
            }
        }
    }
}

void ofApp::doCommand(string command, int module, int moduleidx, ofxOscMessage m) {
    int j = moduleidx / 4;
    int i = moduleidx - j*4;

    if (command.find("setPosition") != string::npos) {
        cristales[module][i][j].goTo(m.getArgAsFloat(0));
    } else if (command.find("setColor") != string::npos) {
        cristales[module][i][j].c = ofColor(m.getArgAsInt(0), m.getArgAsInt(1), m.getArgAsInt(2));
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    cam.begin();
    ofBackground(128);
    ofPushStyle();
    ofPushMatrix();
    ofTranslate(ofPoint(-600,0,-300));
    
    ofRotateYDeg(45);
    for (int q = 0; q < 5; q++) {
        ofTranslate(300,0);
        ofRotateYDeg(-120.0f/5.0f);
        ofPushMatrix();
        ofSetColor(60);
        ofRotateXDeg(90);
        ofTranslate(0,0,250);
        ofDrawRectangle(cristales[q][0][0].pos.x-12, cristales[q][0][0].pos.y-12, 40*5, 40*4);
        ofPopMatrix();

        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 5; j++) {
                cristales[q][i][j].draw();
            }
        }
    }
    ofPopMatrix();
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
