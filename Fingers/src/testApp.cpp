#include "testApp.h"

PXCGesture::GeoNode::Label gFingers[] = {PXCGesture::GeoNode::LABEL_BODY_HAND_PRIMARY|PXCGesture::GeoNode::LABEL_FINGER_THUMB,
											PXCGesture::GeoNode::LABEL_BODY_HAND_PRIMARY|PXCGesture::GeoNode::LABEL_FINGER_INDEX,
											PXCGesture::GeoNode::LABEL_BODY_HAND_PRIMARY|PXCGesture::GeoNode::LABEL_FINGER_MIDDLE,
											PXCGesture::GeoNode::LABEL_BODY_HAND_PRIMARY|PXCGesture::GeoNode::LABEL_FINGER_RING,
											PXCGesture::GeoNode::LABEL_BODY_HAND_PRIMARY|PXCGesture::GeoNode::LABEL_FINGER_PINKY,
											PXCGesture::GeoNode::LABEL_BODY_HAND_SECONDARY|PXCGesture::GeoNode::LABEL_FINGER_THUMB,
											PXCGesture::GeoNode::LABEL_BODY_HAND_SECONDARY|PXCGesture::GeoNode::LABEL_FINGER_INDEX,
											PXCGesture::GeoNode::LABEL_BODY_HAND_SECONDARY|PXCGesture::GeoNode::LABEL_FINGER_MIDDLE,
											PXCGesture::GeoNode::LABEL_BODY_HAND_SECONDARY|PXCGesture::GeoNode::LABEL_FINGER_RING,
											PXCGesture::GeoNode::LABEL_BODY_HAND_SECONDARY|PXCGesture::GeoNode::LABEL_FINGER_PINKY};

//--------------------------------------------------------------
void testApp::setup()
{
	mSession = PXCUPipeline_Init((PXCUPipeline)PXCU_PIPELINE_GESTURE);
	if(!mSession)
		return;
	if(PXCUPipeline_QueryLabelMapSize(mSession, &mlw, &mlh))
	{
		mLabelMap = new unsigned char[mlw*mlh];
		mLabelTex = ofTexture();
		mLabelTex.allocate(mlw,mlh,GL_LUMINANCE);
	}
	for(int i=0;i<10;++i)
	{
		mDraw[i] = false;
		mFingers[i].set(0,0);
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
			for(int i=0;i<10;++i)
			{
				mDraw[i] = PXCUPipeline_QueryGeoNode(mSession, gFingers[i], &mNode);
				if(mDraw[i])
				{
					mFingers[i].set(mNode.positionImage.x*2,mNode.positionImage.y*2);
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
	for(int i=0;i<10;i++)
	{
		if(mDraw[i])
		{
			ofSetColor(0,255,0);
			ofFill();
			ofCircle(mFingers[i], 10);
		}
	}
	ofPopStyle();
}