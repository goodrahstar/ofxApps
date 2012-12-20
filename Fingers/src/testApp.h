#pragma once

#include "ofMain.h"
#include "pxcupipeline.h"

class testApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		
		int mlw,mlh;
		
		bool mDraw[10];
		unsigned char *mLabelMap;

		ofTexture mLabelTex;
		ofPoint mFingers[10];
		PXCUPipeline_Instance mSession;
		PXCGesture::GeoNode mNode;

};
