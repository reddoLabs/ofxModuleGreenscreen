#pragma once

#include "ofMain.h"

#include "ofxGui.h"
#include "ofxChromaKeyShader.h"


class ofApp : public ofBaseApp{

public:
	void setup();
	void update();
	void draw();
	void exit();

	void drawDebugMasks();
	void drawCheckerboard(float x, float y, int width, int height, int size);
	void drawNormalView();   //wenn debug Modus ausgeschaltet, dann normaler Live modus aktiv
	void innerhalbDerAnzeigeGeklickt(int x, int y);

	void keyPressed(int key);
	void keyReleased(int key);
	void mouseMoved(int x, int y );
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
	void windowResized(int w, int h);
	void dragEvent(ofDragInfo dragInfo);
	void gotMessage(ofMessage msg);

	void onBPhotoChanged(bool& isPhoto);

	
	
	void onBgColor(ofFloatColor& v);
	void onBaseMaskStrength(float& v);
	void onChromaMaskStrength(float& v);
	void onGreenSpillStrength(float& v);
	void onMultiplyFilterHueOffset(float& v);
	void onBlurValue(float& v);
	void onDilateStep(int& v);
	void onErodeStep(int & v);
	void onPhotoZoom(float& v);

	void onPhotoOffset(ofVec2f& v);
	void onBgColorPos(ofVec2f& v);
	void onBaseMaskClip(ofVec2f& v);
	void onDetailMaskClip(ofVec2f& v);
	void onEndMaskClip(ofVec2f& v);
	void onClippingMaskTL(ofVec2f& v);
	void onClippingMaskBR(ofVec2f& v);
	void onRoiSize(float& v);


private:
	void switchParams(ofxChromaKeyShader *src, ofxChromaKeyShader *dst);

	bool isWebcam = true;
	// === Variables =============================
	ofImage bg_image;
	
	ofxChromaKeyShader *chromakey;
	ofVideoGrabber webcam;

	int camW, camH;
    
    ofFbo checkerboardTex;   //container für Texturern und optional depth buffer
	
	ofxPanel chromaGui;
	ofParameterGroup values;
	bool bShowGui;
	ofParameter<bool> bUpdateBgColor;
	ofParameter<bool> bDebugMode;
	ofParameter<bool> bPhoto = false;

	ofPixels camPixels;
	ofTexture camTexture;

	ofVideoPlayer		fingerMovie;
	bool                frameByframe;
	bool				neuenFrameFiltern;

	ofJson settings;
	ofJson chromaSettings;

};
