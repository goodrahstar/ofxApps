#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup()
{
	mSession = PXCUPipeline_Init((PXCUPipeline)(PXCU_PIPELINE_DEPTH_QVGA));
	if(!mSession)
		return;
	if(PXCUPipeline_QueryDepthMapSize(mSession, &mdw, &mdh))
	{
		mDepthBuffer = new short[mdw*mdh];
		mDepthMap = new unsigned char[mdw*mdh];
		mDepthTex = ofTexture();
		mDepthTex.allocate(mdw,mdh,GL_LUMINANCE);
	}
	if(PXCUPipeline_QueryIRMapSize(mSession, &mirw, &mirh))
	{
		mIrBuffer = new short[mirw*mirh];
		mIrMap = new unsigned char[mirw*mirh];
		mIrTex = ofTexture();
		mIrTex.allocate(mirw,mirh,GL_LUMINANCE);
	}
	ofSetWindowShape(640,240);
}

//--------------------------------------------------------------
void testApp::update()
{
	if(PXCUPipeline_AcquireFrame(mSession, true))
	{
		if(PXCUPipeline_QueryDepthMap(mSession, mDepthBuffer))
		{
			convertImage((unsigned short *)mDepthBuffer, mDepthMap, mdw, mdh);
			mDepthTex.loadData(mDepthMap, mdw, mdh, GL_LUMINANCE);
		}
		if(PXCUPipeline_QueryIRMap(mSession, mIrBuffer))
		{
			convertImage((unsigned short *)mIrBuffer, mIrMap, mirw, mirh);
			mIrTex.loadData(mIrMap, mirw, mirh, GL_LUMINANCE);
		}

		PXCUPipeline_ReleaseFrame(mSession);
	}
}

//--------------------------------------------------------------
void testApp::draw()
{
	mDepthTex.draw(0,0,mdw,mdh);
	mIrTex.draw(mdw,0,mirw,mirh);
}

void testApp::convertImage(unsigned short *src, unsigned char* dst, int w, int h)
{
    float minC = 0xffff;
    float maxC = -0xffff;
    for(int k=0;k<w*h;k++) {
        float vC = (float)src[k]/0xffff;
        if (minC>vC) minC = vC;
        if (maxC<vC) maxC = vC;
    }

    for(int i=0;i<w*h;i++)
	{
        float val = (float)src[i]/0xffff;
        val = 255.f*sqrt((val-minC)/(maxC-minC));
        dst[i]=(unsigned char)val;
    }
}
