#include "ofxModuleGreenscreen.h"

namespace ofxModule {
    //------------------------------------------------------------------
	ofxModuleGreenscreen::ofxModuleGreenscreen(string moduleName,string settingsPath):ModuleRunnable("Greenscreen", moduleName, settingsPath) {
		//chromakey.setup(640, 480,settings);
		chromaTexPtr = shared_ptr<ofTexture>(&chromaTex);
    }
    
    //------------------------------------------------------------------
    void ofxModuleGreenscreen::update() {

    }
  

	void ofxModuleGreenscreen::proceedChromaKey(shared_ptr<ofTexture> camPic)
	{
		if (!chromakey.isAllocated() || chromakey.getWidth() != camPic->getWidth() || chromakey.getHeight() != camPic->getHeight()) {
					//chromakey.allocate(camPic->getWidth(), camPic->getHeight());
				chromakey.setup(camPic->getWidth(), camPic->getHeight(), settings);
			}
		chromakey.updateChromakeyMask(*camPic);
		chromaTex = chromakey.getFinalImage();

	}

	void ofxModuleGreenscreen::proceedChromaKey(shared_ptr<ofTexture> camPic, shared_ptr<ofTexture> bg)
	{
		if (!chromakey.isAllocated() || chromakey.getWidth() != camPic->getWidth() || chromakey.getHeight() != camPic->getHeight()) {
			chromakey.allocate(camPic->getWidth(), camPic->getHeight());
		}
		chromakey.updateChromakeyMask(*camPic, *bg);
		chromaTex = chromakey.getFinalImage();
	}

	// received module events will be processed here
	void ofxModuleGreenscreen::proceedModuleEvent(ModuleEvent & e)
	{
		// update the cam image 
		if (e.type == ModuleEvent::MODULE_EVENT_TEXTURE) {
			if (e.address== "setBg") {
				bg = e.texture;
			}else{
				if (bg == nullptr) {
					proceedChromaKey(e.texture);
					notifyEvent(chromaTexPtr, "chroma");
				}else {
					proceedChromaKey(e.texture,bg);
					notifyEvent(chromaTexPtr, "chroma");
				}
			}
		}
	}
}
