//---------------------------------------------------------------------------------------------------------------------------
#include "cocos2d.h"
#include "CCEGLView.h"
#include "AppDelegate.h"
#include "SceneGame.h"
#include "SimpleAudioEngine.h"
#include "AppMacros.h"
//---------------------------------------------------------------------------------------------------------------------------
using namespace CocosDenshion;
using namespace cocos2d;
//---------------------------------------------------------------------------------------------------------------------------
//
//---------------------------------------------------------------------------------------------------------------------------
AppDelegate::AppDelegate()
{

}
//---------------------------------------------------------------------------------------------------------------------------
//
//---------------------------------------------------------------------------------------------------------------------------
AppDelegate::~AppDelegate()
{
    SimpleAudioEngine::end();
}
//---------------------------------------------------------------------------------------------------------------------------
//
//---------------------------------------------------------------------------------------------------------------------------
bool AppDelegate::applicationDidFinishLaunching()
{
    // initialize director
    CCDirector *pDirector = CCDirector::sharedDirector();
	CCEGLView* pEGLView = CCEGLView::sharedOpenGLView();
    pDirector->setOpenGLView(CCEGLView::sharedOpenGLView());
	// Set the design resolution
    pEGLView->setDesignResolutionSize(designResolutionSize.width, designResolutionSize.height, kResolutionShowAll);
	// Obtiene el FrameSize del Dispositivo
	CCSize frameSize = pEGLView->getFrameSize();
	
    // if the frame's height is larger than the height of medium resource size, select large resource.
	if (frameSize.height > mediumResource.size.height)
	{ 
		//CCFileUtils::sharedFileUtils()->setSearchPaths->setResourceDirectory(largeResource.directory);
		pDirector->setContentScaleFactor(smallResource2.size.height/designResolutionSize.height);		
        //pDirector->setContentScaleFactor(largeResource.size.height/designResolutionSize.height);		
	}
    // if the frame's height is larger than the height of small resource size, select medium resource.
    else if (frameSize.height > smallResource2.size.height)
    { 
        //CCFileUtils::sharedFileUtils()->setResourceDirectory(mediumResource.directory);
        pDirector->setContentScaleFactor(smallResource2.size.height/designResolutionSize.height);		
    }
	// if the frame's height is larger than the height of small resource size, select medium resource.
    else if (frameSize.height > smallResource.size.height)
    { 
        //CCFileUtils::sharedFileUtils()->setResourceDirectory(mediumResource.directory);
        pDirector->setContentScaleFactor(smallResource2.size.height/designResolutionSize.height);		
    }
    // if the frame's height is smaller than the height of medium resource size, select small resource.
	else
    { 
		//CCFileUtils::sharedFileUtils()->setResourceDirectory(smallResource.directory);
        pDirector->setContentScaleFactor(smallResource.size.height/designResolutionSize.height);
	}

	// Calcule las pulgadas del Device
	int dpi = CCDevice::getDPI();	
	CCSize frameSize2 = pEGLView->getFrameSize();
	CCSize inches;	
	inches.width = frameSize2.width/dpi;
	inches.height = frameSize2.height/dpi;
	float hipotenusa = sqrt(inches.width*inches.width + inches.height*inches.height);	
	//AppData::device_inches = hipotenusa;

    // turn on display FPS
    pDirector->setDisplayStats(false);
    // set FPS. the default value is 1.0/60 if you don't call this
    pDirector->setAnimationInterval(1.0 / 30.0f);
    // create a scene. it's an autorelease object
    CCScene *pScene = SceneGame::scene();
    // run
    pDirector->runWithScene(pScene);
    return true;
}
//---------------------------------------------------------------------------------------------------------------------------
// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
//---------------------------------------------------------------------------------------------------------------------------
void AppDelegate::applicationDidEnterBackground()
{
    CCDirector::sharedDirector()->stopAnimation();
    SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
}
//---------------------------------------------------------------------------------------------------------------------------
// this function will be called when the app is active again
//---------------------------------------------------------------------------------------------------------------------------
void AppDelegate::applicationWillEnterForeground()
{
    CCDirector::sharedDirector()->startAnimation();
    SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
}
