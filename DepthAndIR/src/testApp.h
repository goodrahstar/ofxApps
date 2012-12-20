#pragma once

#include "ofMain.h"
#include "pxcupipeline.h"
class testApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();
		void convertImage(unsigned short *src, unsigned char *dst, int w, int h);

		int mirw,mirh,mdw,mdh;
		short *mIrBuffer, *mDepthBuffer;
		unsigned char *mIrMap, *mDepthMap;
		ofTexture mDepthTex, mIrTex;

		PXCUPipeline_Instance mSession;
};
