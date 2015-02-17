//---------------------------------------------------------------------------------------------------------------------------
#include "cocos2d.h"
#include "CCEGLView.h"
#include "AppDelegate.h"
#include "Inicio.h"
#include "SimpleAudioEngine.h"
#include "AppMacros.h"

#include <vector>
#include <string>

//---------------------------------------------------------------------------------------------------------------------------
using namespace CocosDenshion;
using namespace cocos2d;
using namespace std;

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
    CCDirector *pDirector		= CCDirector::sharedDirector();
	CCEGLView* pEGLView			= CCEGLView::sharedOpenGLView();
    pDirector->setOpenGLView(CCEGLView::sharedOpenGLView());
	// Set the design resolution
    pEGLView->setDesignResolutionSize(designResolutionSize.width, designResolutionSize.height, kResolutionShowAll);
	// Obtiene el FrameSize del Dispositivo
	CCSize frameSize = pEGLView->getFrameSize();
	
	vector<string> searchPath;

	// In this demo, we select resource according to the frame's height.
    // If the resource size is different from design resolution size, you need to set contentScaleFactor.
    // We use the ratio of resource's height to the height of design resolution,
    // this can make sure that the resource's height could fit for the height of design resolution.

    // if the frame's height is larger than the height of medium resource size, select large resource.
	if (frameSize.height > mediumResource.size.height)
	{
 		searchPath.push_back(mediumResource.directory);        
        pDirector->setContentScaleFactor(MIN(mediumResource.size.height/designResolutionSize.height, mediumResource.size.width/designResolutionSize.width));
		//  searchPath.push_back(largeResource.directory);
		//  pDirector->setContentScaleFactor(MIN(largeResource.size.height/designResolutionSize.height, largeResource.size.width/designResolutionSize.width));
	}
    // if the frame's height is larger than the height of small resource size, select medium resource.
    else if (frameSize.height > smallResource.size.height)
    {
        searchPath.push_back(mediumResource.directory);        
        pDirector->setContentScaleFactor(MIN(mediumResource.size.height/designResolutionSize.height, mediumResource.size.width/designResolutionSize.width));
    }
    // if the frame's height is smaller than the height of medium resource size, select small resource.
	else
    {
		searchPath.push_back(mediumResource.directory);        
        pDirector->setContentScaleFactor(MIN(mediumResource.size.height/designResolutionSize.height, mediumResource.size.width/designResolutionSize.width));

        //searchPath.push_back(smallResource.directory);
		//pDirector->setContentScaleFactor(MIN(smallResource.size.height/designResolutionSize.height, smallResource.size.width/designResolutionSize.width));
    }
	
    // set searching path
    CCFileUtils::sharedFileUtils()->setSearchPaths(searchPath);

	// Calcule las pulgadas del Device
	int dpi = CCDevice::getDPI();	
	CCSize frameSize2	= pEGLView->getFrameSize();
	CCSize inches;	
	inches.width		= frameSize2.width/dpi;
	inches.height		= frameSize2.height/dpi;
	float hipotenusa = sqrt(inches.width*inches.width + inches.height*inches.height);	
	//AppData::device_inches = hipotenusa;

    // turn on display FPS
    pDirector->setDisplayStats(false);
    // set FPS. the default value is 1.0/60 if you don't call this
    pDirector->setAnimationInterval(1.0 / 60.0f);
    // create a scene. it's an autorelease object
    CCScene *pScene = Inicio::scene();
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
