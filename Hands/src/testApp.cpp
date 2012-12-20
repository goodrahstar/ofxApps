#include "testApp.h"

PXCGesture::GeoNode::Label gHands[] = {PXCGesture::GeoNode::LABEL_BODY_HAND_PRIMARY,PXCGesture::GeoNode::LABEL_BODY_HAND_SECONDARY};

//--------------------------------------------------------------
void testApp::setup()
{
	mSession = PXCUPipeline_Init((PXCUPipeline)PXCU_PIPELINE_GESTURE);
	if(!mSession)
		ofExit();
	if(PXCUPipeline_QueryLabelMapSize(mSession, &mlw, &mlh))
	{
		mLabelMap = new unsigned char[mlw*mlh];
		mLabelTex = ofTexture();
		mLabelTex.allocate(mlw,mlh,GL_LUMINANCE);
		for(int i=0;i<2;++i)
		{
			mDraw[i] = false;
			mHands[i].set(0,0,0);
		}
	}
	ofSetWindowShape(mlw*2,mlh*2);
}

//--------------------------------------------------------------
void testApp::update()
{
	if(PXCUPipeline_AcquireFrame(mSession, true))
	{
		if(PXCUPipeline_QueryLabelMap(mSession, mLabelMap, 0))
		{
			mLabelTex.loadData(mLabelMap,mlw,mlh,GL_LUMINANCE);
			for(int i=0;i<2;++i)
			{
				mDraw[i] = PXCUPipeline_QueryGeoNode(mSession, gHands[i],&mNode);
				if(mDraw[i])
				{
					mHands[i].set(mNode.positionImage.x*2,mNode.positionImage.y*2,mNode.openness);
				}
			}
		}
		PXCUPipeline_ReleaseFrame(mSession);
	}
}

//--------------------------------------------------------------
void testApp::draw()
{
	mLabelTex.draw(0,0,mlw*2,mlh*2);
	ofPushStyle();
	ofSetColor(0,255,0);
	ofNoFill();
	ofSetLineWidth(3);
	for(int i=0;i<2;i++)
	{
		if(mDraw[i])
		{
			if(mHands[i].z>0)
			{
				ofCircle(mHands[i].x,mHands[i].y,mHands[i].z*0.5);
			}
		}
	}
	ofPopStyle();
}