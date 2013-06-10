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
	mScale = 1;
	mSkip = 1;
	mColor = false;
	mSteps.push_back("1");mSteps.push_back("2");mSteps.push_back("4");mSteps.push_back("8");mSteps.push_back("16");mSteps.push_back("20");
	
	mSession = PXCUPipeline_Create();
	if(!PXCUPipeline_Init(mSession, (PXCUPipeline)(PXCU_PIPELINE_COLOR_VGA|PXCU_PIPELINE_DEPTH_QVGA)))
		ofLogNotice() << "Unable to initialize session" << endl;
	if(PXCUPipeline_QueryDepthMapSize(mSession, &mDW, &mDH))
	{
		mDepthMap = new short[mDW*mDH];
		mUVMap = new float[mDW*mDH*2];
	}
	if(PXCUPipeline_QueryRGBSize(mSession, &mCW, &mCH))
		mRGBMap = new unsigned char[mCW*mCH*4];
	
	for(int y = 0; y < mDH - mSkip; y += mSkip)
	{
		for(int x = 0; x < mDW - mSkip; x += mSkip)
		{
			mVerts.push_back(ofVec3f(x-mDW*0.5f,y-mDH*0.5f,0));
		}
	}
	mTotal = mVerts.size();
	mVBO.setVertexData(&mVerts[0], mTotal, GL_STREAM_DRAW);
	
	mGUI = new ofxUICanvas(0,0,200,200);
	
	mGUI->addFPS();
	mGUI->addSpacer(150,2);
	mGUI->addSlider("SCALE",0.1f,2,mScale,150,10);
	mGUI->addSpacer(150,2);
	mGUI->addLabelToggle("COLOR", false, 150,10);
	mGUI->addDropDownList("RES", mSteps,150);
	ofAddListener(mGUI->newGUIEvent,this,&testApp::guiEvent);	
}

//--------------------------------------------------------------
void testApp::update()
{
	if(PXCUPipeline_AcquireFrame(mSession,false))
	{
		mVerts.clear();
		mColors.clear();
		if(PXCUPipeline_QueryDepthMap(mSession, mDepthMap))
		{
			PXCUPipeline_QueryUVMap(mSession, mUVMap);
			if(mColor)
				PXCUPipeline_QueryRGB(mSession, mRGBMap);
			for(int y=0;y<mDH-mSkip;y+=mSkip)
			{
				for(int x=0;x<mDW-mSkip;x+=mSkip)
				{
					int di = y*mDW+x;
					float d = (float)mDepthMap[di];
					if(d<32000)
					{
						float xoffs = mDW*0.5f;
						float yoffs = mDH*0.5f;
						float vx = ofMap(x,0,mDW,-xoffs,xoffs);
						float vy = ofMap(y,0,mDH,-yoffs,yoffs);
						mVerts.push_back(ofVec3f(vx,vy,ofMap((float)mDepthMap[di],0,1800,-240,240)));
						
						if(mColor)
						{
							int sx=(int)(mUVMap[(y*mDW+x)*2+0]*mDW+0.5) * 2;
							int sy=(int)(mUVMap[(y*mDW+x)*2+1]*mDH+0.5) * 2;
							if(sx>=0&&sx<mCW&&sy>=0&&sy<mCH)
							{
								//crack out individual color vals and scale
								float _r = mRGBMap[(sy*mCW+sx)*4]/255.0f;
								float _g = mRGBMap[(sy*mCW+sx)*4+1]/255.0f;
								float _b = mRGBMap[(sy*mCW+sx)*4+2]/255.0f;
								mColors.push_back(ofFloatColor(_r,_g,_b,1.0f));
							}
						}
						else
							mColors.push_back(ofFloatColor(1,1,1,1));
					}
				}
			}
		}
		PXCUPipeline_ReleaseFrame(mSession);
		mTotal = mColors.size();
		mVBO.setColorData(&mColors[0],mTotal, GL_STREAM_DRAW);

		mTotal = mVerts.size();
		if(mTotal>0)
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
	if(mTotal>0)
		mVBO.draw(GL_POINTS, 0, mTotal);

	glDisable(GL_DEPTH_TEST);
	cam.end();
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
		ofxUIDropDownList *sender = (ofxUIDropDownList *)e.widget;
		vector<ofxUIWidget *> &dlist = sender->getSelected();
		if(dlist.size()>0)
		{
			stringstream convert(dlist[0]->getName());
			convert >> mSkip;
		}
	}
	if(name=="COLOR")
	{
		ofxUILabelToggle *sender = (ofxUILabelToggle *)e.widget;
		mColor = sender->getValue();
	}
}