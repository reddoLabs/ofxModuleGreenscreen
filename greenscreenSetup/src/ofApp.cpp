#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	//ofSetFullscreen(true);
	bShowGui = true;
	bUpdateBgColor = true;
	bDebugMode = true;
	frameByframe = true;
	neuenFrameFiltern = false;



	settings = ofLoadJson("settings.json");
	chromaSettings = settings["Greenscreen"];

	camW = 1920; 
	camH = 1080;

	isWebcam = false;

	// webcam setup

		webcam.listDevices();
		webcam.setDeviceID(0);
		webcam.setDesiredFrameRate(60);
		webcam.initGrabber(camW, camH);
		int grabW = webcam.getWidth();
		int grabH = webcam.getHeight();
		chromakey = new ofxChromaKeyShader();
		chromakey->setup(camW, camH, chromaSettings);
	

		chromakey->bgColor.addListener(this, &ofApp::onBgColor);
		chromakey->baseMaskStrength.addListener(this, &ofApp::onBaseMaskStrength);
		chromakey->chromaMaskStrength.addListener(this, &ofApp::onChromaMaskStrength);
		chromakey->greenSpillStrength.addListener(this, &ofApp::onGreenSpillStrength);
		chromakey->multiplyFilterHueOffset.addListener(this, &ofApp::onMultiplyFilterHueOffset);
		chromakey->blurValue.addListener(this, &ofApp::onBlurValue);
		chromakey->dilateStep.addListener(this, &ofApp::onDilateStep);
		chromakey->erodeStep.addListener(this, &ofApp::onErodeStep);
		chromakey->photoZoom.addListener(this, &ofApp::onPhotoZoom);

		chromakey->photoOffset.addListener(this, &ofApp::onPhotoOffset);
		chromakey->bgColorPos.addListener(this, &ofApp::onBgColorPos);
		chromakey->baseMaskClip.addListener(this, &ofApp::onBaseMaskClip);
		chromakey->detailMaskClip.addListener(this, &ofApp::onDetailMaskClip);
		chromakey->endMaskClip.addListener(this, &ofApp::onEndMaskClip);
		chromakey->clippingMaskTL.addListener(this, &ofApp::onClippingMaskTL);
		chromakey->clippingMaskBR.addListener(this, &ofApp::onClippingMaskBR);
		chromakey->bgColorSize.addListener(this, &ofApp::onRoiSize);


	
	// maskee
	bg_image.loadImage("img/bg.jpg");

	// GUI
	chromaGui.setDefaultWidth(1920*0.25);
	chromaGui.setup(chromakey->paramGp);
	chromaGui.add(bUpdateBgColor.set("Hintergrundfarbe aktualisieren", true));
	chromaGui.add(bDebugMode.set("alle Masken", false));
	chromaGui.setPosition(0, 0);

	bPhoto.addListener(this, &ofApp::onBPhotoChanged);
}

//--------------------------------------------------------------
void ofApp::exit() {
	delete chromakey;
}

//--------------------------------------------------------------
void ofApp::update(){
	ofSetWindowTitle(ofToString(ofGetFrameRate()));


	if (!bPhoto) webcam.update();
	if (webcam.isFrameNew()) {
		camPixels = webcam.getPixelsRef();
		camTexture = webcam.getTextureReference();
	}
	
	if (bUpdateBgColor) {
		chromakey->updateBgColor(camPixels);
	}
	chromakey->updateChromakeyMask(camTexture, bg_image.getTextureReference());
}

//--------------------------------------------------------------
void ofApp::draw(){
	ofSetColor(255);
	ofBackground(0);


	//draw video from file 

	float scale = 0.5 * 1920 / (float)camW;

	ofPushMatrix();
	ofScale(scale);
	// draw Cam mask
	
	//fingerMovie.draw(333, 333);
	if (bDebugMode) {
		chromakey->drawFinalImage(camW / 2, 0, camW, camH);
		drawDebugMasks();
	}
	else
	{
		drawNormalView();
	}
	ofPopMatrix();
	// GUI
	if(bShowGui) {		
		chromaGui.draw();

		// draw bg color's reference Rect
		if(bUpdateBgColor) {
			ofPushStyle();
			ofNoFill();
			ofSetLineWidth(3);
			ofSetColor(255);
			ofVec2f bgColorPos = chromakey->bgColorPos.get();

			float scale = 1920 / (float)camW;

			int xMin;
			int xMax;
			int yMin;
			int yMax;

			if (bDebugMode) {
				xMin = camW * 0.25 * scale;
				xMax = camW *0.75* scale;
				yMin = 0;
				yMax = camH *0.5* scale;
			} else {
				xMin = camW * 0.25* scale;
				xMax = 1920;
				yMin = 0;
				yMax = camH *0.75* scale;
			}
			float ratio = bDebugMode ? 0.5 : 0.75;

				float px = ofMap(bgColorPos.x, 0, camW, xMin, xMax );
				float py = ofMap(bgColorPos.y, 0, camH, yMin, yMax);

				ofRect(px, py, chromakey->bgColorSize.get()*ratio, chromakey->bgColorSize.get()*ratio);
				ofDrawBitmapString("bgColor", px - 2, py - 5);

			ofPopStyle();
		}
	}
}

//--------------------------------------------------------------
void ofApp::drawDebugMasks() {				//debug Mask an und ausschaltbar machen über Einstellungen TODO
	ofSetColor(255);
	int previewW = camW/2, previewH = camH/2, labelOffset = 10;
	
	chromakey->drawBaseMask(camW + previewW, 0, previewW, previewH);
	ofDrawBitmapStringHighlight("Base mask", camW + previewW, labelOffset, ofColor(0, 125), ofColor::yellowGreen);

	chromakey->drawDetailMask(camW + previewW, previewH, previewW, previewH);
	ofDrawBitmapStringHighlight("Detailed mask", camW + previewW, previewH + labelOffset, ofColor(0, 125), ofColor::yellowGreen);
		
	chromakey->drawChromaMask(previewW, camH, previewW, previewH);
	ofDrawBitmapStringHighlight("Chroma mask", previewW, camH + labelOffset, ofColor(0, 125), ofColor::yellowGreen);
				
	drawCheckerboard(camW, camH, previewW, previewH, 5);
	chromakey->drawFinalMask(camW, camH, previewW, previewH);
	ofDrawBitmapStringHighlight("Final mask", camW, camH + labelOffset, ofColor(0, 125), ofColor::yellowGreen);
	
	camTexture.draw(camW + previewW, camH, previewW, previewH);
	ofDrawBitmapStringHighlight("RGB image", camW + previewW, camH + labelOffset, ofColor(0, 125), ofColor::yellowGreen);

	chromakey->drawFinalImage(camW / 2, 0, camW, camH);
}
void ofApp::drawNormalView() { //Sensor, wenn angezeigt an falscher Stelle
	ofSetColor(255);
	int LiveHeight = camH, LiveWidth = camW;

	chromakey->drawFinalImage(camW / 2, 0, camW * 1.5f, camH * 1.5f);   // TODO entsprechende Faktoren automatisch auslesen.

}

//--------------------------------------------------------------
void ofApp::drawCheckerboard(float x, float y, int width, int height, int size) {
    if (!checkerboardTex.isAllocated()) {
        checkerboardTex.allocate(width, height);
        
        ofPushStyle();
        checkerboardTex.begin();
        ofClear(255, 255, 255, 255);
        int numWidth = width/size;
        int numHeight = height/size;
        for(int h=0; h<numHeight; h++) {
            for(int w=0; w<numWidth; w++) {
                if ((h+w)%2 == 0) {
                    ofSetColor(ofColor::black);
                    ofDrawRectangle(w*size, h*size, size, size);
                }
            }
        }
        checkerboardTex.end();
        ofPopStyle();
    }

    ofSetColor(255, 255);
    checkerboardTex.draw(x, y);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
	switch(key){
	case 'a':
		bUpdateBgColor = !bUpdateBgColor;
		
		break;
	case 'g':
		bShowGui = !bShowGui;
		break;
	case 'd':
		bDebugMode = !bDebugMode;
		break;
	case 'p':
		bPhoto = !bPhoto;
		
		break;
	/*case OF_KEY_ESC:
		ofExit();
		break;
		*/
	case 'c':
		//camera.close();
		break;
	case 's':
		cout << chromakey->getJsonParams().dump(4) << endl;
		settings["Greenscreen"] = chromakey->getJsonParams();
		ofSavePrettyJson("settings.json", settings);
		break;
	
	}
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}


//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){ // verschieben des Rectagles durch klicken im Bild TODO
	ofVec2f neuePosition;
	
	neuenFrameFiltern = true;
	//printf("Kamera Breite %i und XKlickKoordinate %i \n", camW, x);


	int xMin;
	int xMax;
	int yMin;
	int yMax;

	float scale = 1920 / (float)camW;

		if (bDebugMode) {
			xMin = camW * 0.25 * scale;
			xMax = camW * 0.75* scale;
			yMin = 0;
			yMax = camH * 0.5* scale;
		} else {
			xMin = camW * 0.25* scale;
			xMax = 1920;
			yMin = 0;
			yMax = camH * 0.75* scale;
		}

	if (x >= xMin && x < xMax && y < yMax) {
		float px = ofMap(x, xMin, xMax, 0, camW);
		float py = ofMap(y, yMin, yMax, 0, camH);

		chromakey->bgColorPos.set(ofVec2f(px,py));
	}
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

void ofApp::onBPhotoChanged(bool & isPhoto)
{
}

void ofApp::onBgColor(ofFloatColor & v)
{
	chromakey->bgColor = v;
}

void ofApp::onBaseMaskStrength(float & v)
{
	chromakey->baseMaskStrength = v;
}

void ofApp::onChromaMaskStrength(float & v)
{
	chromakey->chromaMaskStrength = v;
}

void ofApp::onGreenSpillStrength(float & v)
{
	chromakey->greenSpillStrength = v;
}

void ofApp::onMultiplyFilterHueOffset(float & v)
{
	chromakey->multiplyFilterHueOffset = v;
}

void ofApp::onBlurValue(float & v)
{
	chromakey->blurValue = v;
}

void ofApp::onDilateStep(int & v)
{
	chromakey->dilateStep = v;
}

void ofApp::onErodeStep(int & v)
{
	chromakey->erodeStep = v;
}

void ofApp::onPhotoZoom(float & v)
{
	chromakey->photoZoom = v;
}

void ofApp::onPhotoOffset(ofVec2f & v)
{
	chromakey->photoOffset = v;
}

void ofApp::onBgColorPos(ofVec2f & v)
{
	chromakey->bgColorPos = v;
}

void ofApp::onBaseMaskClip(ofVec2f & v)
{
	chromakey->baseMaskClip = v;
}

void ofApp::onDetailMaskClip(ofVec2f & v)
{
	chromakey->detailMaskClip = v;
}

void ofApp::onEndMaskClip(ofVec2f & v)
{
	chromakey->endMaskClip = v;
}

void ofApp::onClippingMaskTL(ofVec2f & v)
{
	chromakey->clippingMaskTL = v;
}

void ofApp::onClippingMaskBR(ofVec2f & v)
{
	chromakey->clippingMaskBR = v;
}

void ofApp::onRoiSize(float & v)
{
	chromakey->bgColorSize = v;
}

void ofApp::switchParams(ofxChromaKeyShader * src, ofxChromaKeyShader *dst)
{
	/*dst->photoOffset = src->photoOffset;
	dst->photoOffset = src->photoOffset;
	dst->photoOffset = src->photoOffset;
	dst->photoOffset = src->photoOffset;
	dst->photoOffset = src->photoOffset;
	dst->photoOffset = src->photoOffset;
	dst->photoOffset = src->photoOffset;
	dst->photoOffset = src->photoOffset;
	
	chromaGui.add(chromakey->photoOffset);    // DONE Funktion zum verschieben des Bildes, könnte verbessert werden. Rect Sensor wird nicht mit verschoben. Masken möglicherweise auch nicht
	chromaGui.add(chromakey->bgColorPos.set("bgColorPos", ofVec2f(0, 0)));     // Anzeigen der Koordinaten des Sensors für Grün
	chromaGui.add(chromakey->baseMaskClip);
	chromaGui.add(chromakey->detailMaskClip);
	chromaGui.add(chromakey->endMaskClip);
	chromaGui.add(chromakey->clippingMaskTL);
	chromaGui.add(chromakey->clippingMaskBR);*/
}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
