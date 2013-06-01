#ifndef TEST_APP_GUARD
#define TEST_APP_GUARD

#include "ofMain.h"
#include "pxcupipeline.h"

class testApp : public ofBaseApp
{
public:
	void setup();
	void update();
	void draw();
	void exit();

private:
	int mCW, mCH, mLW, mLH;
	unsigned char *mRGBMap, *mLabelMap, *mIRMap, *mDepthMap;
	short *mIRBuffer, *mDepthBuffer;

	ofTexture mRGBTexture;
	ofTexture mLabelTexture;
	ofTexture mDepthTexture;
	ofTexture mIRTexture;

	PXCUPipeline_Instance mSession;
};

#endif