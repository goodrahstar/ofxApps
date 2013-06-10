#ifndef TEST_APP_GUARD
#define TEST_APP_GUARD

#include <vector>
#include "ofMain.h"
#include "ofxUI.h"
#include "pxcupipeline.h"

class testApp : public ofBaseApp {
public:
	void setup();
	void update();
	void draw();
	void exit();
	
private:
	bool mColor;
	int mDW, mDH, mCW, mCH, mSkip, mTotal;
	float mScale, mXOffset, mYOffset;
	short *mDepthMap;

	float *mUVMap;
	unsigned char *mRGBMap;
	vector<ofVec3f> mVerts;
	vector<ofFloatColor> mColors;
	vector<string> mSteps;

	ofEasyCam cam;
	ofVbo mVBO;

	ofxUICanvas *mGUI;
	void setupGUI();
	void guiEvent(ofxUIEventArgs &e);

	PXCUPipeline_Instance mSession;
};

#endif