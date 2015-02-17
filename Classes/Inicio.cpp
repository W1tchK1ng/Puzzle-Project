#include "Inicio.h"
#include "SceneGame.h"
#include "cocos-ext.h"


//#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
//#include "platform/android/jni/JniHelper.h"
//#endif

USING_NS_CC;
using namespace cocos2d::extension;
using namespace cocos2d::gui;
using namespace CocosDenshion;

Inicio::~Inicio()
{
	CCArmatureDataManager::purge();
	SceneReader::purge();
	ActionManager::purge();
	GUIReader::purge();	
}

Inicio::Inicio()
{
	
}

CCScene* Inicio::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();    
    // 'layer' is an autorelease object
    Inicio *layer = Inicio::create();
    // add layer as a child to scene
    scene->addChild(layer);
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool Inicio::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() )    { return false; }

	setKeypadEnabled(true);

	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();

	// Crea una UILayer y la pone como child de la Scene actual
	UILayer *myView = UILayer::create();
	this->addChild(myView, 0, 1000);	
	UIWidget* widget;	
			
	widget = GUIReader::shareReader()->widgetFromJsonFile("puzzle.json");		
	myView->addWidget(widget);

	imageLogo = dynamic_cast <UIImageView*>(myView->getWidgetByName("Image_Fondo_Logo"));
	imageLogo->setEnabled(true);
	imageLogo->setVisible(true);
	imageLogo->setTouchEnabled(true);

	imageMenu = dynamic_cast <UIImageView*>(myView->getWidgetByName("Image_Fondo_Menu"));
	imageMenu->setEnabled(false);
	imageMenu->setVisible(false);
	imageMenu->setTouchEnabled(false);			
	UIButton* btn1 = dynamic_cast <UIButton*>(myView->getWidgetByName("Button_Jugar"));
	btn1->setEnabled(false);
	btn1->setVisible(false);
	UIButton* btn2 = dynamic_cast <UIButton*>(myView->getWidgetByName("Button_Facebook"));
	btn2->setEnabled(false);
	btn2->setVisible(false);
	UIButton* btn3 = dynamic_cast <UIButton*>(myView->getWidgetByName("Button_Tienda"));
	btn3->setEnabled(false);
	btn3->setVisible(false);	
	UIButton* btn4 = dynamic_cast <UIButton*>(myView->getWidgetByName("Button_Salir"));
	btn4->setEnabled(false);
	btn4->setVisible(false);	
	btn1->addTouchEventListener(this, toucheventselector(Inicio::ButtonUpdate));
	btn2->addTouchEventListener(this, toucheventselector(Inicio::ButtonUpdate));  
	btn3->addTouchEventListener(this, toucheventselector(Inicio::ButtonUpdate));  	
	btn4->addTouchEventListener(this, toucheventselector(Inicio::ButtonUpdate));  	

	CCActionInterval *seq1 = (CCActionInterval*)CCSequence::create(CCDelayTime::create(2.0f), CCCallFunc::create(this, callfunc_selector(Inicio::ActiveMenu)), NULL); 		
	this->runAction(seq1);	

	SimpleAudioEngine::sharedEngine()->preloadBackgroundMusic("intro.mp3");	
	
    return true;
}

void Inicio::ButtonUpdate(CCObject* pSender, cocos2d::gui::TouchEventType type)
{

UIButton* btn = dynamic_cast <UIButton*>(pSender);

CCLOG("Button Name: %s", btn->getName());

	switch (type)
		{
			case TOUCH_EVENT_BEGAN:
				CCLOG("Button BEGAN");
				break;
            
			case TOUCH_EVENT_MOVED:
				CCLOG("Button MOVED");
				break;
            
			case TOUCH_EVENT_ENDED:		

				CCLOG("Button ENDED");

				if (std::strcmp(btn->getName(), "Button_Jugar")==0)
					{
					CCActionInterval *seq1a = (CCActionInterval*)CCSequence::create(CCFadeOut::create(0.5f), NULL); 		
					CCActionInterval *seq1b = (CCActionInterval*)CCSequence::create(CCFadeOut::create(0.5f), NULL); 
					CCActionInterval *seq1c = (CCActionInterval*)CCSequence::create(CCFadeOut::create(0.5f), NULL); 
					CCActionInterval *seq1d = (CCActionInterval*)CCSequence::create(CCFadeOut::create(0.5f), NULL); 		
					CCActionInterval *seq1e = (CCActionInterval*)CCSequence::create(CCFadeOut::create(0.5f), NULL); 
					CCActionInterval *seq1f = (CCActionInterval*)CCSequence::create(CCFadeOut::create(0.5f), NULL); 					
					CCActionInterval *seq1g = (CCActionInterval*)CCSequence::create(CCFadeOut::create(0.5f), NULL); 					
					CCActionInterval *seq1h = (CCActionInterval*)CCSequence::create(CCFadeOut::create(0.5f), NULL); 					
					CCActionInterval *seq1i = (CCActionInterval*)CCSequence::create(CCFadeOut::create(0.5f), NULL); 	
					imageMenu->runAction(seq1a);
					UILayer* myView = (UILayer*) this->getChildByTag(1000);
					UIButton* btn1 = dynamic_cast <UIButton*>(myView->getWidgetByName("Button_Jugar"));
					UIButton* btn2 = dynamic_cast <UIButton*>(myView->getWidgetByName("Button_Facebook"));
					UIButton* btn3 = dynamic_cast <UIButton*>(myView->getWidgetByName("Button_Tienda"));
					UIButton* btn4 = dynamic_cast <UIButton*>(myView->getWidgetByName("Button_Salir"));
					btn1->runAction(seq1b);
					btn2->runAction(seq1c);
					btn3->runAction(seq1g);
					btn4->runAction(seq1h);
					UILabelBMFont *label_jugar = dynamic_cast <UILabelBMFont*>(myView->getWidgetByName("Label_Jugar")); 
					UILabelBMFont *label_facebook = dynamic_cast <UILabelBMFont*>(myView->getWidgetByName("Label_Facebook"));
					UILabelBMFont *label_tienda = dynamic_cast <UILabelBMFont*>(myView->getWidgetByName("Label_Tienda"));
					label_jugar->runAction(seq1d);
					label_facebook->runAction(seq1e);
					label_tienda->runAction(seq1i);
					UIImageView* image_facebook = dynamic_cast <UIImageView*>(myView->getWidgetByName("Image_10"));
					image_facebook->runAction(seq1f);
					CCActionInterval *seq2 = (CCActionInterval*)CCSequence::create(CCDelayTime::create(0.5f), CCCallFunc::create(this, callfunc_selector(Inicio::GotoSceneGame)), NULL); 		
					this->runAction(seq2);					
					}

				if (std::strcmp(btn->getName(), "Button_Facebook")==0) 
					{

					}		
				if (std::strcmp(btn->getName(), "Button_Salir")==0) 
					{					
					#if (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT) || (CC_TARGET_PLATFORM == CC_PLATFORM_WP8)
					CCMessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
					#else
					CCDirector::sharedDirector()->end();
					#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
					exit(0);
					#endif
					}
				#endif

				break;
            
			case TOUCH_EVENT_CANCELED:				
				break;
            
			default:
				break;
		}
	
}

void Inicio::GotoSceneGame()
{	
	SimpleAudioEngine::sharedEngine()->stopBackgroundMusic();
	CCScene *pScene = SceneGame::scene();	
	CCDirector::sharedDirector()->replaceScene(pScene);		

}

void Inicio::Salir()
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT) || (CC_TARGET_PLATFORM == CC_PLATFORM_WP8)
	CCMessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
#else
    CCDirector::sharedDirector()->end();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
#endif
}

void Inicio::ActiveMenu()  
{
	UILayer* myView = (UILayer*) this->getChildByTag(1000);
	UIButton* btn1 = dynamic_cast <UIButton*>(myView->getWidgetByName("Button_Jugar"));
	btn1->setEnabled(true);
	btn1->setVisible(true);
	UIButton* btn2 = dynamic_cast <UIButton*>(myView->getWidgetByName("Button_Facebook"));
	btn2->setEnabled(true);
	btn2->setVisible(true);	
	UIButton* btn3 = dynamic_cast <UIButton*>(myView->getWidgetByName("Button_Tienda"));
	btn3->setEnabled(true);
	btn3->setVisible(true);			
	UIButton* btn4 = dynamic_cast <UIButton*>(myView->getWidgetByName("Button_Salir"));
	btn4->setEnabled(true);
	btn4->setVisible(true);		
	imageLogo->setEnabled(false);
	imageLogo->setVisible(false);
	imageLogo->setTouchEnabled(false);	
	imageMenu->setEnabled(true);
	imageMenu->setVisible(true);
	imageMenu->setTouchEnabled(true);	

	SimpleAudioEngine::sharedEngine()->playBackgroundMusic("intro.mp3",true);
	
}
