#include "testApp.h"

const int HANDS = 2;
const int FINGERS = 5;
const PXCGesture::GeoNode::Label gHands[] = {PXCGesture::GeoNode::LABEL_BODY_HAND_PRIMARY,PXCGesture::GeoNode::LABEL_BODY_HAND_SECONDARY};
const PXCGesture::GeoNode::Label gFingers[] = {PXCGesture::GeoNode::LABEL_FINGER_THUMB,
												PXCGesture::GeoNode::LABEL_FINGER_INDEX,
												PXCGesture::GeoNode::LABEL_FINGER_MIDDLE,
												PXCGesture::GeoNode::LABEL_FINGER_RING,
												PXCGesture::GeoNode::LABEL_FINGER_PINKY};

//--------------------------------------------------------------
void testApp::setup()
{
	ofSetWindowShape(640,480);
	ofSetLogLevel(OF_LOG_NOTICE);

	mSession = PXCUPipeline_Create();
	if(!PXCUPipeline_Init(mSession, (PXCUPipeline)PXCU_PIPELINE_GESTURE))
		ofLogNotice() << "Unable to initialize session" << endl;
	if(PXCUPipeline_QueryLabelMapSize(mSession, &mLW, &mLH))
	{
		mLabelMap = new unsigned char[mLW*mLH];
		mLabelTexture.allocate(mLW, mLH, GL_LUMINANCE);
	}
}

//--------------------------------------------------------------
void testApp::update()
{
	if(PXCUPipeline_AcquireFrame(mSession, false))
	{
		mPositions.clear();
		if(PXCUPipeline_QueryLabelMap(mSession, mLabelMap, 0))
			mLabelTexture.loadData(mLabelMap, mLW, mLH, GL_LUMINANCE);
		for(int i=0;i<HANDS;++i)
		{
			for(int j=0;j<FINGERS;++j)
			{
				if(PXCUPipeline_QueryGeoNode(mSession, gHands[i]|gFingers[j], &mNode))
					mPositions.push_back(ofPoint(mNode.positionImage.x*2, mNode.positionImage.y*2));
			}
			if(PXCUPipeline_QueryGeoNode(mSession, gHands[i], &mNode))
				mPositions.push_back(ofPoint(mNode.positionImage.x*2, mNode.positionImage.y*2));
		}
		PXCUPipeline_ReleaseFrame(mSession);
	}
}

//--------------------------------------------------------------
void testApp::draw()
{
	ofSetColor(ofColor::white);
	mLabelTexture.draw(0,0,640,480);

	ofPushStyle();
	ofSetColor(ofColor::green);
	ofFill();
	for(vector<ofPoint>::iterator vit=mPositions.begin();vit!=mPositions.end();++vit)
		ofCircle(*vit, 10);

	ofPopStyle();
}

//--------------------------------------------------------------
void testApp::exit()
{

}