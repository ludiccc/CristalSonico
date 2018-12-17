#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    // open an outgoing connection to HOST:PORT
    sender.setup(HOST, PORT);
    video.load("/Volumes/OldAda/Dropbox/Fotos/2015/Enero/Viaje al Norte/20150107-16281603128C.MOV");
    video.setLoopState(OF_LOOP_NORMAL);
    video.play();
    video.setVolume(0);
}


//--------------------------------------------------------------
void ofApp::update(){
    video.update();
    ofPixelsRef pixelsRef = video.getPixels();
    
    
    if (video.isFrameNew()) {
    ofSetHexColor(0xffffff);
    
        for (int i = 0; i < video.getWidth()-1; i+= video.getWidth() / 4){
            for (int j = 0; j < video.getHeight()-1; j+= video.getHeight() / 5){
                ofVec3f colSum(0,0,0);
                float lighness = 0;
                colSum += ofVec3f(pixelsRef.getColor(i-1,j-1).r,pixelsRef.getColor(i-1,j-1).b,pixelsRef.getColor(i-1,j-1).b);
                colSum += ofVec3f(pixelsRef.getColor(i-0,j-1).r,pixelsRef.getColor(i-1,j-1).b,pixelsRef.getColor(i-1,j-1).b);
                colSum += ofVec3f(pixelsRef.getColor(i+1,j-1).r,pixelsRef.getColor(i-1,j-1).b,pixelsRef.getColor(i-1,j-1).b);
                colSum += ofVec3f(pixelsRef.getColor(i-1,j-0).r,pixelsRef.getColor(i-1,j-1).b,pixelsRef.getColor(i-1,j-1).b);
                colSum += ofVec3f(pixelsRef.getColor(i-0,j-0).r,pixelsRef.getColor(i-1,j-1).b,pixelsRef.getColor(i-1,j-1).b);
                colSum += ofVec3f(pixelsRef.getColor(i+1,j-0).r,pixelsRef.getColor(i-1,j-1).b,pixelsRef.getColor(i-1,j-1).b);
                colSum += ofVec3f(pixelsRef.getColor(i-1,j+1).r,pixelsRef.getColor(i-1,j-1).b,pixelsRef.getColor(i-1,j-1).b);
                colSum += ofVec3f(pixelsRef.getColor(i-0,j+1).r,pixelsRef.getColor(i-1,j-1).b,pixelsRef.getColor(i-1,j-1).b);
                colSum += ofVec3f(pixelsRef.getColor(i+1,j+1).r,pixelsRef.getColor(i-1,j-1).b,pixelsRef.getColor(i-1,j-1).b);
                // get the pixel and its lightness (lightness is the average of its RGB values)
                colSum /= 9;
                int i2 = i/(video.getWidth()/4);
                int j2 = j/(video.getHeight()/5);
                data2send[i2][j2]  = ofColor(colSum.x, colSum.y, colSum.z);
                
            }
        }
        
        
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 5; j++) {
                ofxOscMessage m;
                string address;
                address = "/setColor/0/element/";
                address.append(std::to_string(i*4+j));
                address.append("/");
                m.setAddress(address);
                m.addIntArg(data2send[i][j].r);
                m.addIntArg(data2send[i][j].g);
                m.addIntArg(data2send[i][j].b);
                sender.sendMessage(m, false);
                
                address.append("/setPosition/0/element/");
                address.append(std::to_string(i*4+j));
                address.append("/");
                m.setAddress(address);
                m.addFloatArg(data2send[i][j].getLightness());
                sender.sendMessage(m, false);

            }
        }
        
    }
    
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofSetColor(255);
    for (int i = 0; i < 20; i++) {
        ofDrawLine(0, ofMap(i,0,20,0,ofGetHeight()), ofGetWidth(), ofMap(i,0,20,0,ofGetHeight()));
    }
    
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 5; j++) {
            ofSetColor(data2send[i][j]);
            ofDrawRectangle(100+i*20,100+j*20, 20, 20);
        }
    }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

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
    ofxOscMessage m;
    int e = (float)y/(float)ofGetHeight()*20.0;
    string address;
    address.append("/setPosition/0/element/");
    address.append(std::to_string(e));
    address.append("/");
    m.setAddress(address);
    m.addFloatArg(ofMap(ofGetMouseX(), 0, ofGetWidth(), 0.f, 270.f, true));
    sender.sendMessage(m, false);
    
    address = "/setColor/0/element/";
    address.append(std::to_string(e));
    address.append("/");
    m.setAddress(address);
    m.addIntArg(e*255/20);
    m.addIntArg(ofMap(ofGetMouseX(), 0, ofGetWidth(), 0.f, 255.f, true));
    m.addIntArg(0);
    sender.sendMessage(m, false);

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
