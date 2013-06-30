#ifndef TEST_APP_GUARD
#define TEST_APP_GUARD

#include "ofMain.h"
#include "util_pipeline.h"
#include "pxcvoice.h"


class VoiceReco;
class testApp : public ofBaseApp
{
public:
	void setup();
	void update();
	void draw();
	void exit();
	void OnVoiceRecognized(PXCVoiceRecognition::Recognition *data);

private:
	VoiceReco *pipeline;
};


class VoiceReco: public UtilPipeline
{
private:
	testApp *of;
public:
	void SetOFApp(testApp *app) 
	{
		of = app;
	}
	void PXCAPI OnRecognized(PXCVoiceRecognition::Recognition *data)
	{
		of->OnVoiceRecognized(data);
	}
};

#endif