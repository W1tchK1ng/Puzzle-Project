#include "Inicio.h"
#include "SceneGame.h"
#include "cocos-ext.h"
#include "TileMap.h"


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
	btn1->setEnabled(false);btn1->setVisible(false);
	UIButton* btn2 = dynamic_cast <UIButton*>(myView->getWidgetByName("Button_Facebook"));
	btn2->setEnabled(false);btn2->setVisible(false);
	UIButton* btn3 = dynamic_cast <UIButton*>(myView->getWidgetByName("Button_Tienda"));
	btn3->setEnabled(false);btn3->setVisible(false);	
	UIButton* btn4 = dynamic_cast <UIButton*>(myView->getWidgetByName("Button_Salir"));
	btn4->setEnabled(false);btn4->setVisible(false);	
	UIButton* btn5 = dynamic_cast <UIButton*>(myView->getWidgetByName("Button_Rankings"));
	btn5->setEnabled(false);btn4->setVisible(false);	
	UIButton* btn6 = dynamic_cast <UIButton*>(myView->getWidgetByName("Button_Facebook"));
	btn6->setEnabled(false);btn6->setVisible(false);
	UIButton* btn7 = dynamic_cast <UIButton*>(myView->getWidgetByName("Button_Tienda"));	
	btn7->setEnabled(false);btn7->setVisible(false);
	UIButton* btn8 = dynamic_cast <UIButton*>(myView->getWidgetByName("Button_Setting"));
	btn8->setEnabled(false);btn8->setVisible(false);
	UIButton* btn9 = dynamic_cast <UIButton*>(myView->getWidgetByName("Button_Gift"));
	btn9->setEnabled(false);btn9->setVisible(false);
	UIButton* btn10 = dynamic_cast <UIButton*>(myView->getWidgetByName("Button_Sound"));
	btn10->setEnabled(false);btn10->setVisible(false);
	UIImageView *imageArco = dynamic_cast <UIImageView*>(myView->getWidgetByName("Image_Arco"));
	imageArco->setEnabled(false); imageArco->setVisible(false);

	btn1->addTouchEventListener(this, toucheventselector(Inicio::ButtonUpdate));
	btn2->addTouchEventListener(this, toucheventselector(Inicio::ButtonUpdate));  
	btn3->addTouchEventListener(this, toucheventselector(Inicio::ButtonUpdate));  	
	btn4->addTouchEventListener(this, toucheventselector(Inicio::ButtonUpdate));	
	btn5->addTouchEventListener(this, toucheventselector(Inicio::ButtonUpdate));	
	btn6->addTouchEventListener(this, toucheventselector(Inicio::ButtonUpdate));
	btn7->addTouchEventListener(this, toucheventselector(Inicio::ButtonUpdate));  
	btn8->addTouchEventListener(this, toucheventselector(Inicio::ButtonUpdate));  	
	btn9->addTouchEventListener(this, toucheventselector(Inicio::ButtonUpdate));  	
	btn10->addTouchEventListener(this, toucheventselector(Inicio::ButtonUpdate));  	
	
	CCActionInterval *seq1 = (CCActionInterval*)CCSequence::create(CCDelayTime::create(0.5f), CCCallFunc::create(this, callfunc_selector(Inicio::ActiveMenu)), NULL); 		
	this->runAction(seq1);	

	CCLOG("preload music");
	SimpleAudioEngine::sharedEngine()->preloadBackgroundMusic("intro.mp3");	
	UIImageView* imageNoSound = dynamic_cast <UIImageView*>(myView->getWidgetByName("Image_NoSound"));
	imageNoSound->setEnabled(false);
	imageNoSound->setVisible(false);
	
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
					FadeOutBotonera();
					FadeOutAjustes();
					CCActionInterval *seq2 = (CCActionInterval*)CCSequence::create(CCDelayTime::create(0.5f), CCCallFunc::create(this, callfunc_selector(Inicio::GotoSceneGame)), NULL); 		
					this->runAction(seq2);					
					}

				if (std::strcmp(btn->getName(), "Button_Facebook")==0) 
					{
					FadeOutBotonera();
					FadeOutAjustes();
					CCActionInterval *seq2 = (CCActionInterval*)CCSequence::create(CCDelayTime::create(0.5f), CCCallFunc::create(this, callfunc_selector(Inicio::GotoSceneTileMap)), NULL); 		
					this->runAction(seq2);					
					}		

				if (std::strcmp(btn->getName(), "Button_Sound")==0) 
					{
					UILayer* myView = (UILayer*) this->getChildByTag(1000);
					UIImageView* imageNoSound = dynamic_cast <UIImageView*>(myView->getWidgetByName("Image_NoSound"));
					
					if(flag_music == true) 
						{imageNoSound->setEnabled(true);
						 SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
						 flag_music = false;
						 CCLOG("pause music");
						}
					else{
						imageNoSound->setEnabled(false);
						SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
						if (!SimpleAudioEngine::sharedEngine()->isBackgroundMusicPlaying()) 
								SimpleAudioEngine::sharedEngine()->playBackgroundMusic("intro.mp3",true);
						CCLOG("resume music");
						flag_music = true;
						}


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
					#endif
				}				

				break;
            
			case TOUCH_EVENT_CANCELED:				
				break;
            
			default:
				break;
		}
	
}

void Inicio::GotoSceneGame()
{	
	CCLOG("stop music");
	flag_music = false;
	SimpleAudioEngine::sharedEngine()->stopBackgroundMusic();
	CCScene *pScene = SceneGame::scene();	
	CCDirector::sharedDirector()->replaceScene(pScene);		

}

void Inicio::GotoSceneTileMap()
{	
	CCLOG("stop music");
	flag_music = false;
	SimpleAudioEngine::sharedEngine()->stopBackgroundMusic();
	CCScene *pScene = TileMap::scene();	
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
	imageMenu->setEnabled(true);
	imageMenu->setVisible(true);
	imageMenu->setTouchEnabled(true);	

	setLogo(false);	
	setBotonera(true);
	setAjustes(true);
	
	CCLOG("dont start music");
	flag_music = false;
	//SimpleAudioEngine::sharedEngine()->playBackgroundMusic("intro.mp3",true);
	UILayer* myView = (UILayer*) this->getChildByTag(1000);
	UIImageView* imageNoSound = dynamic_cast <UIImageView*>(myView->getWidgetByName("Image_NoSound"));
	imageNoSound->setEnabled(true);					
	
}

void Inicio::setLogo (bool value)
{	
	imageLogo->setEnabled(value);
	imageLogo->setVisible(value);
	imageLogo->setTouchEnabled(value);
}

void Inicio::setBotonera(bool value)
{
	UILayer* myView = (UILayer*) this->getChildByTag(1000);
	UIButton* btn1 = dynamic_cast <UIButton*>(myView->getWidgetByName("Button_Jugar"));
	btn1->setEnabled(value);btn1->setVisible(value);
	UIButton* btn2 = dynamic_cast <UIButton*>(myView->getWidgetByName("Button_Facebook"));
	btn2->setEnabled(value);btn2->setVisible(value);
	UIButton* btn3 = dynamic_cast <UIButton*>(myView->getWidgetByName("Button_Tienda"));
	btn3->setEnabled(value);btn3->setVisible(value);	
	UIButton* btn4 = dynamic_cast <UIButton*>(myView->getWidgetByName("Button_Rankings"));
	btn4->setEnabled(value);btn4->setVisible(value);	
	UIButton* btn5 = dynamic_cast <UIButton*>(myView->getWidgetByName("Button_Salir"));
	btn5->setEnabled(value);	btn5->setVisible(value);		
	
}

void Inicio::setAjustes(bool value)
{
	UILayer* myView = (UILayer*) this->getChildByTag(1000);
	UIButton* btn1 = dynamic_cast <UIButton*>(myView->getWidgetByName("Button_Setting"));
	btn1->setEnabled(value);btn1->setVisible(value);
	btn1->setTouchEnabled(value);
	UIButton* btn2 = dynamic_cast <UIButton*>(myView->getWidgetByName("Button_Gift"));
	btn2->setEnabled(value);btn2->setVisible(value);
	btn2->setTouchEnabled(value);
	UIButton* btn3 = dynamic_cast <UIButton*>(myView->getWidgetByName("Button_Sound"));
	btn3->setEnabled(value);btn3->setVisible(value);	
	btn3->setTouchEnabled(value);
	UIImageView* imageNoGift = dynamic_cast <UIImageView*>(myView->getWidgetByName("Image_NoGift"));
	imageNoGift->setEnabled(value);
	imageNoGift->setVisible(value);	
	UIImageView* imageNoSound = dynamic_cast <UIImageView*>(myView->getWidgetByName("Image_NoSound"));
	imageNoSound->setEnabled(value);	
	imageNoSound->setVisible(value);
	UIImageView *imageArco = dynamic_cast <UIImageView*>(myView->getWidgetByName("Image_Arco"));
	imageArco->setEnabled(value); imageArco->setVisible(value);
	
}

void Inicio::FadeOutAjustes()
{
	UILayer* myView = (UILayer*) this->getChildByTag(1000);
	UIButton* btn7 = dynamic_cast <UIButton*>(myView->getWidgetByName("Button_Tienda"));	
	UIButton* btn8 = dynamic_cast <UIButton*>(myView->getWidgetByName("Button_Setting"));
	UIButton* btn9 = dynamic_cast <UIButton*>(myView->getWidgetByName("Button_Gift"));
	UIButton* btn10 = dynamic_cast <UIButton*>(myView->getWidgetByName("Button_Sound"));
	UIImageView *imageArco = dynamic_cast <UIImageView*>(myView->getWidgetByName("Image_Arco"));

	CCActionInterval *seqb7 = (CCActionInterval*)CCSequence::create(CCFadeOut::create(0.3f), NULL); 
	CCActionInterval *seqb8 = (CCActionInterval*)CCSequence::create(CCFadeOut::create(0.3f), NULL); 
	CCActionInterval *seqb9 = (CCActionInterval*)CCSequence::create(CCFadeOut::create(0.3f), NULL); 		
	CCActionInterval *seqb10 = (CCActionInterval*)CCSequence::create(CCFadeOut::create(0.3f), NULL); 	
	CCActionInterval *seqi1 = (CCActionInterval*)CCSequence::create(CCFadeOut::create(0.3f), NULL); 	

	btn7->runAction(seqb7);
	btn8->runAction(seqb8);
	btn9->runAction(seqb9);
	btn10->runAction(seqb10);
	imageArco->runAction(seqi1);
}

void Inicio::FadeOutBotonera()
{
	CCActionInterval *seqa1 = (CCActionInterval*)CCSequence::create(CCFadeOut::create(0.5f), NULL); 		
	imageMenu->runAction(seqa1);
	UILayer* myView = (UILayer*) this->getChildByTag(1000);
	UIButton* btn1 = dynamic_cast <UIButton*>(myView->getWidgetByName("Button_Jugar"));
	UIButton* btn2 = dynamic_cast <UIButton*>(myView->getWidgetByName("Button_Facebook"));
	UIButton* btn3 = dynamic_cast <UIButton*>(myView->getWidgetByName("Button_Tienda"));
	UIButton* btn4 = dynamic_cast <UIButton*>(myView->getWidgetByName("Button_Salir"));
	UIButton* btn5 = dynamic_cast <UIButton*>(myView->getWidgetByName("Button_Rankings"));
	//UIPanel *panel1 = dynamic_cast <UIPanel*>(myView->getWidgetByName("Panel_Botonera"));
	CCActionInterval *seqb1 = (CCActionInterval*)CCSequence::create(CCFadeOut::create(0.3f), NULL); 
	CCActionInterval *seqb2 = (CCActionInterval*)CCSequence::create(CCFadeOut::create(0.3f), NULL); 
	CCActionInterval *seqb3 = (CCActionInterval*)CCSequence::create(CCFadeOut::create(0.3f), NULL); 		
	CCActionInterval *seqb4 = (CCActionInterval*)CCSequence::create(CCFadeOut::create(0.3f), NULL); 
	CCActionInterval *seqb5 = (CCActionInterval*)CCSequence::create(CCFadeOut::create(0.3f), NULL); 								
	//CCActionInterval *seqp1 = (CCActionInterval*)CCSequence::create(CCFadeOut::create(0.5f), NULL); 								
	btn1->runAction(seqb1);
	btn2->runAction(seqb2);
	btn3->runAction(seqb3);
	btn4->runAction(seqb4);
	btn5->runAction(seqb5);	
	//panel1->runAction(seqp1);
	//panel1->setVisible(false);
	UILabelBMFont *label_jugar = dynamic_cast <UILabelBMFont*>(myView->getWidgetByName("Label_Jugar")); 
	UILabelBMFont *label_facebook = dynamic_cast <UILabelBMFont*>(myView->getWidgetByName("Label_Facebook"));
	UILabelBMFont *label_tienda = dynamic_cast <UILabelBMFont*>(myView->getWidgetByName("Label_Tienda"));
	UILabelBMFont *label_rankings = dynamic_cast <UILabelBMFont*>(myView->getWidgetByName("Label_Rankings"));
	UIImageView* image_facebook = dynamic_cast <UIImageView*>(myView->getWidgetByName("Image_10"));
	CCActionInterval *seqc1 = (CCActionInterval*)CCSequence::create(CCFadeOut::create(0.3f), NULL); 					
	CCActionInterval *seqc2 = (CCActionInterval*)CCSequence::create(CCFadeOut::create(0.3f), NULL); 					
	CCActionInterval *seqc3 = (CCActionInterval*)CCSequence::create(CCFadeOut::create(0.3f), NULL); 	
	CCActionInterval *seqc4 = (CCActionInterval*)CCSequence::create(CCFadeOut::create(0.3f), NULL); 	
	CCActionInterval *seqc5 = (CCActionInterval*)CCSequence::create(CCFadeOut::create(0.3f), NULL); 	
	label_jugar->runAction(seqc1);
	label_facebook->runAction(seqc2);
	label_tienda->runAction(seqc3);	
	label_rankings->runAction(seqc4);	
	image_facebook->runAction(seqc5);		
}
