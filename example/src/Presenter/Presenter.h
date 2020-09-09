#ifndef _Presenter
#define _Presenter

#include "ofMain.h"
#include "ModuleDrawable.h"

namespace ofxModule {
	// Basic example of a ModuleDrawable with communication
class Presenter : public ModuleDrawable{
	
  public:
	
	  Presenter(string moduleName = "Presenter");
	
    void update();
	void draw();

	void mouseMoved(ofMouseEventArgs & mouse) {};
	void mouseDragged(ofMouseEventArgs & mouse) {};
	void mousePressed(ofMouseEventArgs & mouse);
	void mouseReleased(ofMouseEventArgs & mouse);
	void mouseScrolled(ofMouseEventArgs & mouse) {};
	void mouseEntered(ofMouseEventArgs & mouse) {};
	void mouseExited(ofMouseEventArgs & mouse) {};

    
	
protected:
    void proceedModuleEvent(ModuleEvent& e);
    
    private:
		shared_ptr<ofTexture> camImage;
		shared_ptr<ofPixels> pixelImage;
		shared_ptr<ofTexture> bgTex;
		ofImage bg;
};
}

#endif
