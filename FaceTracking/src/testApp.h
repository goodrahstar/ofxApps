#pragma once

#include "ofMain.h"
#include "pxcupipeline.h"

class testApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		int mcw,mch;
		bool mDraw[6];
		unsigned char *mRgbMap;
		ofTexture mRgbTex;
		ofPoint mLandmarks[6];
		PXCFaceAnalysis::Landmark::LandmarkData mFaceLM;
		PXCFaceAnalysis::Detection::Data mFaceLoc;
		PXCUPipeline_Instance mSession;
};