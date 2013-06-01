#pragma once

#include "ofMain.h"
#include "util_pipeline.h"

class testApp : public ofBaseApp
{
public:
	void setup();
	void update();
	void draw();

private:
	UtilPipeline mSession;
};
