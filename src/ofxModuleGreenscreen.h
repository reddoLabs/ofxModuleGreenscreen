#ifndef _ofxModuleGreenscreen
#define _ofxModuleGreenscreen

#include "ofMain.h"
#include "ModuleRunnable.h"
#include "ofxChromaKeyShader.h"

namespace ofxModule {

// A Module for Chromakeying
class ofxModuleGreenscreen : public ModuleRunnable{
	
  public:
	
	ofxModuleGreenscreen(string moduleName = "Greenscreen", string settingsPath = "settings.json");
    void update();

	void proceedChromaKey(shared_ptr<ofTexture> camPic, shared_ptr<ofTexture> bg);
	void proceedChromaKey(shared_ptr<ofTexture> camPic);
    
protected:
    void proceedModuleEvent(ModuleEvent& e);
    
private:
	ofxChromaKeyShader chromakey;
	
	shared_ptr<ofTexture> bg;
	
	ofTexture chromaTex; /// \ holds the rendered texture
	shared_ptr<ofTexture> chromaTexPtr; /// \ pointer to the texture for notification events
};
}
#endif
