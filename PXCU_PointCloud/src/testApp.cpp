#include <sstream>
#include "testApp.h"

/*
PerC SDK point cloud example based on ofx vboExample
*/
//--------------------------------------------------------------
void testApp::setup()
{
	ofSetWindowShape(840,480);
	ofSetFrameRate(60);
	ofEnableBlendMode(OF_BLENDMODE_ALPHA);
	mDH=240;
	mDW=320;
	mScale=1;
	mSteps.push_back("1");
	mSteps.push_back("2");
	mSteps.push_back("4");
	mSteps.push_back("8");
	mSteps.push_back("16");
	mSteps.push_back("20");
	/*
	mSession = PXCUPipeline_Create();
	PXCUPipeline_Init(mSession, (PXCUPipeline)PXCU_PIPELINE_DEPTH_QVGA);
	PXCUPipeline_QueryDepthMapSize(mSession, &mDW, &mDH);
	*/
	mSkip = mPSkip = 1;

	for(int y = 0; y < mDH - mSkip; y += mSkip)
	{
		for(int x = 0; x < mDW - mSkip; x += mSkip)
		{
			mVerts.push_back(ofVec3f(x-mDW*0.5f,y-mDH*0.5f,0));
		}
	}
	mTotal = mVerts.size();
	mVBO.setVertexData(&mVerts[0], mTotal, GL_STREAM_DRAW);
	
	mGUI = new ofxUICanvas(0,0,200,100);
	
	mGUI->addFPS();
	mGUI->addSpacer(150,2);
	mGUI->addSlider("SCALE",0.1f,2,mScale,150,10);
	mGUI->addSpacer(150,2);
	mGUI->addDropDownList("RES", mSteps,150);
	ofAddListener(mGUI->newGUIEvent,this,&testApp::guiEvent);	
}

//--------------------------------------------------------------
void testApp::update()
{/*
	if(PXCUPipeline_AcquireFrame(mSession,false))
	{
		mVerts.clear();
		if(PXCUPipeline_QueryDepthMap(mSession, mDepthMap))
		{
			for(int y=0;y<mDH-mSkip;y+=mSkip)
			{
				for(int x=0;x<mDW-mSkip;x+=mSkip)
				{
					float d = (float)mDepthMap[y*mDW+x];
					if(d<32000)
					{
						mVerts.push_back(ofVec3f(x,y,ofMap(d,0,1800,-240,240)));
					}
				}
			}
		}
		PXCUPipeline_ReleaseFrame(mSession);
		mTotal = mVerts.size();
		mVBO.setVertexData(&mVerts[0], mTotal, GL_STREAM_DRAW);
	}*/
	if(true) //testing GL_STREAM_DRAW
	{
		mVerts.clear();
		for(int y = 0; y < mDH - mSkip; y += mSkip)
		{
			for(int x = 0; x < mDW - mSkip; x += mSkip)
			{
				mVerts.push_back(ofVec3f(x-mDW*0.5f,y-mDH*0.5f,0));
			}
		}
		mTotal = mVerts.size();
		mVBO.setVertexData(&mVerts[0], mTotal, GL_STREAM_DRAW);
	}
}

//--------------------------------------------------------------
void testApp::draw()
{
	ofBackground(64);
	cam.begin();
	glEnable(GL_DEPTH_TEST);	
	ofScale(mScale, -mScale, mScale); // make y point down

	int pTotal = mVerts.size();
	mVBO.draw(GL_POINTS, 0, mTotal);
	glDisable(GL_DEPTH_TEST);
	cam.end();
	
	// draw the framerate in the top left corner
}

void testApp::guiEvent(ofxUIEventArgs &e)
{
	string name = e.widget->getName();
	if(name=="SCALE")
	{
		ofxUISlider *sender = (ofxUISlider *)e.widget;
		mScale = sender->getScaledValue();
	}
	if(name=="RES")
	{
		mPSkip = mSkip;
		ofxUIDropDownList *sender = (ofxUIDropDownList *)e.widget;
		vector<ofxUIWidget *> &dlist = sender->getSelected();
		if(dlist.size()>0)
		{
			stringstream convert(dlist[0]->getName());
			convert >> mSkip;
		}
	}
}