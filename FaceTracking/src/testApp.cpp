#include "testApp.h"


PXCFaceAnalysis::Landmark::Label gLabels[] = {PXCFaceAnalysis::Landmark::LABEL_LEFT_EYE_INNER_CORNER,
												PXCFaceAnalysis::Landmark::LABEL_LEFT_EYE_OUTER_CORNER,
												PXCFaceAnalysis::Landmark::LABEL_RIGHT_EYE_INNER_CORNER,
												PXCFaceAnalysis::Landmark::LABEL_RIGHT_EYE_OUTER_CORNER,
												PXCFaceAnalysis::Landmark::LABEL_MOUTH_LEFT_CORNER,
												PXCFaceAnalysis::Landmark::LABEL_MOUTH_RIGHT_CORNER};
//--------------------------------------------------------------
void testApp::setup()
{
	mSession = PXCUPipeline_Init((PXCUPipeline)(PXCU_PIPELINE_FACE_LANDMARK|PXCU_PIPELINE_COLOR_VGA));
	//mSession = PXCUPipeline_Init((PXCUPipeline)(PXCU_PIPELINE_FACE_LANDMARK|PXCU_PIPELINE_COLOR_WXGA));
	if(!mSession)
		ofExit();
	if(PXCUPipeline_QueryRGBSize(mSession,&mcw,&mch))
	{
		mRgbMap = new unsigned char[mcw*mch*4];
		mRgbTex = ofTexture();
		mRgbTex.allocate(mcw,mch,GL_RGBA);
	}
	ofSetWindowShape(mcw,mch);
}

//--------------------------------------------------------------
void testApp::update()
{
	if(PXCUPipeline_AcquireFrame(mSession, true))
	{
		if(PXCUPipeline_QueryRGB(mSession, mRgbMap))
		{
			mRgbTex.loadData(mRgbMap,mcw,mch,GL_RGBA);
			pxcUID face;
			pxcU64 timeStamp;
			if(PXCUPipeline_QueryFaceID(mSession,0,&face,&timeStamp))
			{
				if(PXCUPipeline_QueryFaceLocationData(mSession, face, &mFaceLoc))
				{
					for(int i=0;i<6;i++)
					{
						mDraw[i] = PXCUPipeline_QueryFaceLandmarkData(mSession,face,gLabels[i],0,&mFaceLM);
						if(mDraw[i])
						{
							mLandmarks[i].set(mFaceLM.position.x,mFaceLM.position.y);
						}
					}
				}
			}
		}
		PXCUPipeline_ReleaseFrame(mSession);
	}
}

//--------------------------------------------------------------
void testApp::draw()
{
	mRgbTex.draw(0,0,mcw,mch);
	ofPushStyle();
	ofSetColor(0,255,0);
	for(int i=0;i<6;++i)
	{
		if(mDraw[i])
		{
			ofCircle(mLandmarks[i],2);
		}
	}

	ofNoFill();
	ofRect(mFaceLoc.rectangle.x,mFaceLoc.rectangle.y,mFaceLoc.rectangle.w,mFaceLoc.rectangle.h);
	ofPopStyle();
}