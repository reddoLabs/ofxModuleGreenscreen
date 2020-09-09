#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	if (webModule.getModuleLoader()->getCountModulesConfig("Webcam")) {
		webModule.getModuleLoader()->addModule(new ofxModuleWebcam());
	}
	if (webModule.getModuleLoader()->getCountModulesConfig("Presenter")) {
		webModule.getModuleLoader()->addModule(new Presenter());
	}
	if (webModule.getModuleLoader()->getCountModulesConfig("Greenscreen")) {
		webModule.getModuleLoader()->addModule(new ofxModuleGreenscreen());
	}

	webModule.getModuleLoader()->initModuleCommunication();
}

//--------------------------------------------------------------
void ofApp::update(){
	webModule.getModuleRunner()->updateModules();
}

//--------------------------------------------------------------
void ofApp::draw(){
	webModule.getModuleRunner()->drawModules();
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
