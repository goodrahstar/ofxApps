#ifndef TEST_APP_GUARD
#define TEST_APP_GUARD

#include <vector>
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
	int mCW, mCH;
	unsigned char *mRGBMap;

	vector<ofRectangle> mFaceLocs;
	vector<ofPoint> mFaceLMs;
	
	ofTexture mRGBTexture;

	PXCUPipeline_Instance mSession;
	pxcUID mFaceId;
	pxcU64 mTimestamp;
	PXCFaceAnalysis::Detection::Data mFaceData;
	PXCFaceAnalysis::Landmark::LandmarkData mLMData;
};

#endif