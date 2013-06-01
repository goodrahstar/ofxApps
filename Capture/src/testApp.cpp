#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup()
{
	ofSetLogLevel(OF_LOG_NOTICE);
	ofSetWindowShape(640,240);
	mSession.EnableImage(PXCImage::COLOR_FORMAT_RGB24);
	mSession.EnableImage(PXCImage::COLOR_FORMAT_DEPTH);
	mSession.EnableGesture();
	if(!mSession.Init())
	{
		ofLogNotice() << "Unable Starting Session" << endl;
		return;
	}
	
	if(mSession.QueryImageSize(PXCImage::IMAGE_TYPE_COLOR, mRGBW, mRGBH))
		mRGBTexture.allocate(mRGBW,mRGBH,GL_RGB);
	else
		ofLogNotice() << "Unable to Query RGB Map Size" << endl;
	if(mSession.QueryImageSize(PXCImage::IMAGE_TYPE_DEPTH, mLW, mLH))
		mLabelTexture.allocate(mLW,mLH,GL_LUMINANCE);
	else
		ofLogNotice() << "Unable to Query Depth Map Size" << endl;
}

//--------------------------------------------------------------
void testApp::update()
{
	if(mSession.AcquireFrame(false))
	{
		mImage = mSession.QueryImage(PXCImage::IMAGE_TYPE_COLOR);
		if(mImage)
		{
			if(mImage->AcquireAccess(PXCImage::ACCESS_READ, &mImageData)>=PXC_STATUS_NO_ERROR)
			{
				mRGBTexture.loadData(mImageData.planes[0], mRGBW, mRGBH,GL_RGB);
				mImage->ReleaseAccess(&mImageData);
			}
			else
				ofLogNotice()
		}
		// Get Label (Blob) Map

		if(mSession.QueryGesture()->QueryBlobImage(PXCGesture::Blob::LABEL_SCENE, 0, &mImage)>=PXC_STATUS_NO_ERROR)
		{
			if(mImage->AcquireAccess(PXCImage::ACCESS_READ, &mImageData)>=PXC_STATUS_NO_ERROR)
			{
				mLabelTexture.loadData(mImageData.planes[0], mLW, mLH, GL_LUMINANCE);
				mImage->ReleaseAccess(&mImageData);
			}			
		}
		mSession.ReleaseFrame();
	}
}

//--------------------------------------------------------------
void testApp::draw()
{
	//ofSetColor(ofColor::white);
	//mRGBTexture.draw(0,0,320,240);
	mLabelTexture.draw(320,0,320,240);
}

void testApp::exit()
{
	mSession.Close();
}