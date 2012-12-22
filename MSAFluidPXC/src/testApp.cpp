#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup()
{
	//Setup PXC
	mSession = PXCUPipeline_Init((PXCUPipeline)(PXCU_PIPELINE_COLOR_VGA|PXCU_PIPELINE_GESTURE));
	if(!mSession)
		ofExit();
	if(!PXCUPipeline_QueryRGBSize(mSession,&mcw,&mch))
		ofExit();
	mRgbMap = new unsigned char[mcw*mch*4];
	mRgbTex = ofTexture();
	mRgbTex.allocate(mcw,mch,GL_RGBA);
	
	//Setup fluid	
	mSolver.setup(160,120);
	mSolver.enableRGB(true).setColorDiffusion(0).setDeltaT(0.5).setFadeSpeed(0.01).setVisc(0.0002);
	mDrawer.setup(&mSolver);
	mDrawer.enableAlpha(true);
	mDrawer.useAdditiveBlending = true;

	//Setup ofx
	ofSetWindowShape(mcw,mch);
	ofEnableAlphaBlending();	
}

//--------------------------------------------------------------
void testApp::update()
{
	if(PXCUPipeline_AcquireFrame(mSession, true))
	{
		if(PXCUPipeline_QueryRGB(mSession, mRgbMap))
		{
			mRgbTex.loadData(mRgbMap,mcw,mch,GL_RGBA);
			if(PXCUPipeline_QueryGeoNode(mSession, PXCGesture::GeoNode::LABEL_BODY_HAND_PRIMARY, &mNode))
			{
				mPHand1 = mPHand0;
				mPHand0.set(ofLerp(mPHand0.x,mNode.positionImage.x,0.5f),
							ofLerp(mPHand0.y,mNode.positionImage.y,0.5f));
				
				addToSolver(&mSolver,
							msa::Vec2f(mPHand1.x,mPHand1.y),
							msa::Color(255,0,0),
							msa::Vec2f(mPHand0.x-mPHand1.x,mPHand0.y-mPHand1.y),
							mNode.openness);
			}
			if(PXCUPipeline_QueryGeoNode(mSession, PXCGesture::GeoNode::LABEL_BODY_HAND_SECONDARY, &mNode))
			{
				mSHand1 = mSHand0;
				mSHand0.set(ofLerp(mSHand0.x,mNode.positionImage.x,0.5f),
							ofLerp(mSHand0.y,mNode.positionImage.y,0.5f));

				addToSolver(&mSolver,
							msa::Vec2f(mSHand1.x,mSHand1.y),
							msa::Color(0,0,255),
							msa::Vec2f(mSHand0.x-mSHand1.x,mSHand0.y-mSHand1.y),
							mNode.openness);
			}
		}
		mSolver.update();
		PXCUPipeline_ReleaseFrame(mSession);
	}
}

//--------------------------------------------------------------
void testApp::draw()
{
	ofClear(0);
	mRgbTex.draw(0,0,mcw,mch);
	mDrawer.draw(0,0,mcw,mch);
}

void testApp::addDensity(msa::fluid::Solver *pSolver, msa::Vec2f pPos, msa::Color pColor, int pSize)
{
	msa::Vec2f newPos;
	for(int i=0;i<pSize;i++)
	{
		float rx = ofRandom(-pSize,pSize);
		float ry = ofRandom(-pSize,pSize);
		newPos = msa::Vec2f((pPos.x+rx)/320.f,(pPos.y+ry)/240.f);
		pSolver->addColorAtPos(newPos, pColor);
	}
}

void testApp::addVelocity(msa::fluid::Solver *pSolver, msa::Vec2f pPos, msa::Vec2f pForce, int pSize)
{
	msa::Vec2f newPos;
	for(int i=0;i<pSize;i++)
	{
		float rx = ofRandom(-pSize,pSize);
		float ry = ofRandom(-pSize,pSize);
		newPos = msa::Vec2f((pPos.x+rx)/320.f,(pPos.y+ry)/240.f);
		pSolver->addForceAtPos(newPos, pForce);
	}
}

void testApp::addToSolver(msa::fluid::Solver *pSolver, msa::Vec2f pPos, msa::Color pColor, msa::Vec2f pForce, int pSize)
{
	if(pSize<10)
	{
		addVelocity(pSolver, pPos, pForce, 100);
	}
	else
	{
		int fSize = (int)ofMap(pSize,10,100,5,10);
		addDensity(pSolver, pPos, pColor, fSize);
		addVelocity(pSolver, pPos, pForce, fSize);
	}
}