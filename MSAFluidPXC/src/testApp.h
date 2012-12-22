#pragma once

#include "ofMain.h"
#include "MSAFluid.h"
#include "MSAFluidSolver.h"
#include "MSAFluidDrawerGl-OF.h"
#include "pxcupipeline.h"

class testApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();
		void addDensity(msa::fluid::Solver *pSolver, msa::Vec2f pPos, msa::Color pColor, int pSize);
		void addVelocity(msa::fluid::Solver *pSolver, msa::Vec2f pPos, msa::Vec2f pForce, int pSize);
		void addToSolver(msa::fluid::Solver *pSolver, msa::Vec2f pPos, msa::Color pColor, msa::Vec2f pForce, int pSize);

		int mcw,mch;
		unsigned char *mRgbMap;
		ofTexture mRgbTex;
		PXCUPipeline_Instance mSession;
		PXCGesture::GeoNode mNode;

		ofPoint mPHand0, mPHand1;
		ofPoint mSHand0, mSHand1;
		msa::fluid::Solver mSolver;
		msa::fluid::DrawerGl mDrawer;

};
