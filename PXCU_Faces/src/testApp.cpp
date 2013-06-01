#include "testApp.h"
const int LABELS = 6;
PXCFaceAnalysis::Landmark::Label gLandmarks[] = {PXCFaceAnalysis::Landmark::LABEL_LEFT_EYE_INNER_CORNER,
													PXCFaceAnalysis::Landmark::LABEL_LEFT_EYE_OUTER_CORNER,
													PXCFaceAnalysis::Landmark::LABEL_RIGHT_EYE_INNER_CORNER,
													PXCFaceAnalysis::Landmark::LABEL_RIGHT_EYE_OUTER_CORNER,
													PXCFaceAnalysis::Landmark::LABEL_MOUTH_LEFT_CORNER,
													PXCFaceAnalysis::Landmark::LABEL_MOUTH_RIGHT_CORNER};

//--------------------------------------------------------------
void testApp::setup()
{
	ofSetWindowShape(640,480);
	ofSetLogLevel(OF_LOG_NOTICE);
	mSession = PXCUPipeline_Create();

	if(!PXCUPipeline_Init(mSession, (PXCUPipeline)(PXCU_PIPELINE_COLOR_VGA|PXCU_PIPELINE_FACE_LANDMARK)))
	{
		ofLogNotice() << "Unable to initialize session" << endl;
		return;
	}

	if(PXCUPipeline_QueryRGBSize(mSession, &mCW, &mCH))
	{
		mRGBMap = new unsigned char[mCW*mCH*4];
		mRGBTexture.allocate(mCW,mCH,GL_RGBA);
	}

}

//--------------------------------------------------------------
void testApp::update()
{
	if(PXCUPipeline_AcquireFrame(mSession, false))
	{
		mFaceLocs.clear();
		mFaceLMs.clear();
		if(PXCUPipeline_QueryRGB(mSession, mRGBMap))
			mRGBTexture.loadData(mRGBMap, mCW, mCH, GL_RGBA);
		for(int fid=0;;++fid)
		{
			if(PXCUPipeline_QueryFaceID(mSession, fid, &mFaceId, &mTimestamp))
			{
				if(PXCUPipeline_QueryFaceLocationData(mSession, mFaceId, &mFaceData))
					mFaceLocs.push_back(ofRectangle(mFaceData.rectangle.x,mFaceData.rectangle.y,mFaceData.rectangle.w,mFaceData.rectangle.h));
				for(int lm=0;lm<LABELS;++lm)
				{
					if(PXCUPipeline_QueryFaceLandmarkData(mSession, mFaceId, gLandmarks[lm], 0, &mLMData))
						mFaceLMs.push_back(ofPoint(mLMData.position.x, mLMData.position.y));
				}
			}
			else
				break;
		}
		PXCUPipeline_ReleaseFrame(mSession);
	}
}

//--------------------------------------------------------------
void testApp::draw()
{
	ofSetColor(ofColor::white);
	mRGBTexture.draw(0,0,640,480);

	ofPushStyle();
	ofSetColor(0,255,0);
	ofNoFill();
	for(vector<ofRectangle>::iterator vit=mFaceLocs.begin();vit!=mFaceLocs.end();++vit)
		ofRectRounded(vit->x,vit->y,vit->width,vit->height,10);
	ofPopStyle();
	
	ofPushStyle();
	ofSetColor(255,255,0);
	ofFill();
	for(vector<ofPoint>::iterator vit=mFaceLMs.begin();vit!=mFaceLMs.end();++vit)
		ofCircle(*vit, 2.5f);
	ofPopStyle();
}

//--------------------------------------------------------------
void testApp::exit()
{
	PXCUPipeline_Close(mSession);
}
