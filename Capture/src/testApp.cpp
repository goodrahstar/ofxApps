#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup()
{
	mSession = PXCUPipeline_Init((PXCUPipeline)(PXCU_PIPELINE_GESTURE|PXCU_PIPELINE_COLOR_VGA));
	if(!mSession)
		return;

	if(PXCUPipeline_QueryLabelMapSize(mSession, &mlw, &mlh))
	{
		mLabelMap = new unsigned char[mlw*mlh];
		mLabelTex = ofTexture();
		mLabelTex.allocate(mlw,mlh,GL_LUMINANCE);
	}
	if(PXCUPipeline_QueryRGBSize(mSession, &mcw, &mch))
	{
		mRgbMap = new unsigned char[mcw*mch*4];
		mRgbTex = ofTexture();
		mRgbTex.allocate(mcw,mch,GL_RGBA);
	}
	ofSetWindowShape(mcw*2,mch);
	mDraw = false;
}

//--------------------------------------------------------------
void testApp::update()
{
	if(PXCUPipeline_AcquireFrame(mSession, true))
	{
		if(PXCUPipeline_QueryRGB(mSession, mRgbMap))
			mRgbTex.loadData(mRgbMap,mcw,mch,GL_RGBA);
		if(PXCUPipeline_QueryLabelMap(mSession, mLabelMap,0))
			mLabelTex.loadData(mLabelMap,mlw,mlh,GL_LUMINANCE);
		PXCUPipeline_ReleaseFrame(mSession);
	}
}

//--------------------------------------------------------------
void testApp::draw()
{
	mRgbTex.draw(0,0,mcw,mch);
	mLabelTex.draw(mcw,0,mlw*2,mlh*2);
}

//--------------------------------------------------------------
