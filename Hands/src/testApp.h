#pragma once

#include "ofMain.h"
#include "pxcupipeline.h"

class testApp : public ofBaseApp
{
	public:
		void setup();
		void update();
		void draw();

		int mlw,mlh;
		bool mDraw[2];
		unsigned char *mLabelMap;

		ofTexture mLabelTex;
		ofPoint mHands[2];

		PXCGesture::GeoNode mNode;
		PXCUPipeline_Instance mSession;
};
