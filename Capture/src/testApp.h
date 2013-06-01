#pragma once

#include "ofMain.h"
#include "util_pipeline.h"

class testApp : public ofBaseApp
{
public:
	void setup();
	void update();
	void draw();
	void exit();

private:
	pxcU32 mRGBW, mRGBH, mLW, mLH;
	PXCGesture *mGesture;
	PXCImage *mImage;
	PXCImage::ImageData mImageData;
	UtilPipeline mSession;

	ofTexture mRGBTexture;
	ofTexture mLabelTexture;
};
