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
	int mLW, mLH;
	unsigned char* mLabelMap;

	ofTexture mLabelTexture;
	vector<ofPoint> mPositions;

	PXCUPipeline_Instance mSession;
	PXCGesture::GeoNode mNode;
};

#endif