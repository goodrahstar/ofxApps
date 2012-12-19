#pragma once

#include "ofMain.h"
#include "pxcupipeline.h"

class testApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		bool mDraw;
		int mlw, mlh, mcw, mch;
		unsigned char *mLabelMap, *mRgbMap;
		ofTexture mRgbTex, mLabelTex;
		PXCUPipeline_Instance mSession;

		
};
