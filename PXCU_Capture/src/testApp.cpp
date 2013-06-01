#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup()
{
	ofSetWindowShape(640,480);
	ofSetLogLevel(OF_LOG_NOTICE);

	mSession = PXCUPipeline_Create();
	if(!PXCUPipeline_Init(mSession, (PXCUPipeline)(PXCU_PIPELINE_COLOR_VGA|PXCU_PIPELINE_DEPTH_QVGA|PXCU_PIPELINE_GESTURE)))
	{
		ofLogNotice() << "Unable to initialize session" << endl;
		return;
	}

	if(PXCUPipeline_QueryRGBSize(mSession, &mCW, &mCH))
	{
		mRGBMap = new unsigned char[mCW*mCH*4];
		mRGBTexture.allocate(mCW,mCH,GL_RGBA);
	}
	if(PXCUPipeline_QueryLabelMapSize(mSession, &mLW, &mLH))
	{
		mLabelMap = new unsigned char[mLW*mLH];
		mLabelTexture.allocate(mLW,mLH,GL_LUMINANCE);
	}
	if(PXCUPipeline_QueryDepthMapSize(mSession, &mLW, &mLH))
	{
		mDepthBuffer = new short[mLW*mLH];
		mDepthMap = new unsigned char[mLW*mLH];
		mDepthTexture.allocate(mLW,mLH,GL_LUMINANCE);
	}
	if(PXCUPipeline_QueryIRMapSize(mSession, &mLW, &mLH))
	{
		mIRBuffer = new short[mLW*mLH];
		mIRMap = new unsigned char[mLW*mLH];
		mIRTexture.allocate(mLW,mLH,GL_LUMINANCE);
	}
}

//--------------------------------------------------------------
void testApp::update()
{
	if(PXCUPipeline_AcquireFrame(mSession, false))
	{
		if(PXCUPipeline_QueryRGB(mSession, mRGBMap))
			mRGBTexture.loadData(mRGBMap, mCW, mCH, GL_RGBA);
		if(PXCUPipeline_QueryLabelMap(mSession, mLabelMap, 0))
			mLabelTexture.loadData(mLabelMap, mLW, mLH, GL_LUMINANCE);
		bool getDepth = PXCUPipeline_QueryDepthMap(mSession, mDepthBuffer);
		bool getIR = PXCUPipeline_QueryIRMap(mSession, mIRBuffer);
		if(getDepth||getIR)
		{
			for(int i=0;i<mLW*mLH;++i)
			{
				if(getDepth)
					mDepthMap[i] = (unsigned char)ofMap((float)mDepthBuffer[i],0,2000,0,255);
				if(getIR)
					mIRMap[i] = (unsigned char)ofMap((float)mIRBuffer[i],0,3000,0,255);
			}
			if(getDepth)
				mDepthTexture.loadData(mDepthMap, mLW, mLH, GL_LUMINANCE);
			if(getIR)
				mIRTexture.loadData(mIRMap, mLW, mLH, GL_LUMINANCE);
		}
		PXCUPipeline_ReleaseFrame(mSession);
	}
}

//--------------------------------------------------------------
void testApp::draw()
{
	mRGBTexture.draw(0,0,320,240);
	mLabelTexture.draw(320,0,320,240);
	mDepthTexture.draw(0,240,320,230);
	mIRTexture.draw(320,240,320,240);
}

//--------------------------------------------------------------
void testApp::exit()
{ 
	PXCUPipeline_Close(mSession);
}