#include "testApp.h"

//--------------------------------------------------------------

// ---------- comment this out to command and control  ---------//
// you cannot use both at the same time unfortunately...
//#define DICTATION 1


void testApp::setup()
{
	ofSetWindowShape(640,480);
	ofSetLogLevel(OF_LOG_NOTICE);

	// create a list of our commands we want recognized
	vector<wstring> commands;
	commands.push_back(L"i like robots");
	commands.push_back(L"hello");
	commands.push_back(L"hello new york");

	// start the PCSDK voice recognition
	pipeline = new VoiceReco();
	pipeline->SetOFApp(this);  // this will allow us to call 
	pipeline->EnableVoiceRecognition();

#ifndef DICTATION
	pipeline->SetVoiceCommands(commands);
#endif

	pipeline->Init();
}

//--------------------------------------------------------------
void testApp::update()
{
	// still need this for grabbing audio and letting the SDK fire off OnRecognized events
	if(pipeline->AcquireFrame(false))
	{
		pipeline->ReleaseFrame();
	}
}

void testApp::OnVoiceRecognized(PXCVoiceRecognition::Recognition *data)
{
	wcout << data->dictation << endl;
}


//--------------------------------------------------------------
void testApp::draw()
{
}

//--------------------------------------------------------------
void testApp::exit()
{ 
	pipeline->Close();
}
