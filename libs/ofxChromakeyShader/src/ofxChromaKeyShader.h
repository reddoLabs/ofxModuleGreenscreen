/********************************************************************************** 
 
 Copyright (c) 2013- Koo Kin Yat, Eric (musiko)
 
 Permission is hereby granted, free of charge, to any person obtaining a copy of
 this software and associated documentation files (the "Software"), to deal in
 the Software without restriction, including without limitation the rights to
 use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies
 of the Software, and to permit persons to whom the Software is furnished to do
 so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in all
 copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 SOFTWARE.
 
 **********************************************************************************/

#pragma once

#include "ofMain.h"
#include "ofxCv.h"
#include "ChromeKeyShaders.h"
#include "ChromeKeyShaders150.h"

class ofxChromaKeyShader
{
public:
	// ==================== Methods ====================

	ofxChromaKeyShader();
	~ofxChromaKeyShader(void);

	void setup(int width, int height, ofJson settings);
	void allocate(int width, int height);

	void loadShaders();
	void updateBgColorPos(float x, float y);
	void updateBgColor(ofPixelsRef camPixRef);
    void updateChromakeyMask(const ofTexture& input_tex, const ofTexture& bg_tex);
    void updateChromakeyMask(const ofTexture& input_tex);

	void drawDetailMask(float x, float y, float w, float h);
	void drawBaseMask(float x, float y, float w, float h);
	void drawChromaMask(float x, float y, float w, float h);
	void drawFinalMask(float x, float y, float w, float h);
	void drawFinalImage(float x, float y, float w, float h);

	ofTexture getFinalImage();
	ofTexture getFinalMask();
	ofTexture getFinalMask(ofTexture back);
	ofFbo getFinalFbo();
	ofJson getJsonParams();

    // ==================== Setters ======================
    void setbgColor(ofColor c) { bgColor.set(ofFloatColor(c.r/255.0f, c.g/255.0f, c.b/255.0f, 1.0)); }

    void setbaseMaskStrength(float value) { baseMaskStrength.set(value); }
    void setchromaMaskStrength(float value) { chromaMaskStrength.set(value); }
    void setgreenSpillStrength(float value) { greenSpillStrength.set(value); }

    void setblurValue(float value) { blurValue.set(value); }
    void setmultiplyFilterHueOffset(float value) { multiplyFilterHueOffset.set(value); }
	
	int getWidth();
	int getHeight();

	bool isAllocated();

	// Greenscreen params
	ofParameterGroup paramGp;

	ofParameter<ofVec2f> bgColorPos;
	ofParameter<float> bgColorSize;
	ofParameter<ofFloatColor> bgColor;

	ofParameter<ofVec2f> baseMaskClip;
	ofParameter<ofVec2f> detailMaskClip;
	ofParameter<ofVec2f> endMaskClip;

	ofParameter<float> baseMaskStrength;
	ofParameter<float> chromaMaskStrength;
	ofParameter<float> greenSpillStrength;

	ofParameter<float> blurValue;
	ofParameter<float> multiplyFilterHueOffset;

	ofParameter<int> dilateStep;
	ofParameter<int> erodeStep;

	ofParameter<ofVec2f> clippingMaskTL;
	ofParameter<ofVec2f> clippingMaskBR;

	ofParameter<ofVec2f> photoOffset;
	ofParameter<float> photoZoom;

public:

	void proceedChromaMask(const ofTexture& input_tex);

	// ==================== Variables ====================
	ChromaKeyShaders chromakeyshaders;
	ChromaKeyShaders150 chromakeyshaders150;
	int width; 
	int height;
	bool bAllocated = false;

	// Shader & FBO
	ofShader shader_detail, shader_base, shader_hblur, shader_vblur;
	ofShader shader_dilate, shader_erode, shader_chroma, shader_final;
	ofFbo fbo_detail, fbo_base, fbo_pingpong, fbo_chroma, fbo_final;
	ofFbo finalFbo;
};

