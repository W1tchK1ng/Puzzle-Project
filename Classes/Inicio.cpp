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
	
	// Load Main Menu/Logo Widget //
	UIWidget* widget_mainmenu;			
	widget_mainmenu = GUIReader::shareReader()->widgetFromJsonFile("puzzle.json");		
	myView->addWidget(widget_mainmenu);	
	
	// Logo //
	imageLogo = dynamic_cast <UIImageView*>(myView->getWidgetByName("Image_Fondo_Logo"));
	imageLogo->setEnabled(true);
	imageLogo->setVisible(true);
	imageLogo->setTouchEnabled(true);
	
	// Main Menu
	imageMenu = dynamic_cast <UIImageView*>(myView->getWidgetByName("Image_Fondo_Menu"));
	imageMenu->setEnabled(false);
	imageMenu->setVisible(false);
	imageMenu->setTouchEnabled(false);	

	// Main Menu Buttons//	
	UIButton* btn_mm1 = dynamic_cast <UIButton*>(myView->getWidgetByName("Button_Jugar"));
	btn_mm1->setEnabled(false);btn_mm1->setVisible(false);
	UIButton* btn_mm2 = dynamic_cast <UIButton*>(myView->getWidgetByName("Button_Facebook"));
	btn_mm2->setEnabled(false);btn_mm2->setVisible(false);
	UIButton* btn_mm3 = dynamic_cast <UIButton*>(myView->getWidgetByName("Button_Tienda"));
	btn_mm3->setEnabled(false);btn_mm3->setVisible(false);	
	UIButton* btn_mm4 = dynamic_cast <UIButton*>(myView->getWidgetByName("Button_Salir"));
	btn_mm4->setEnabled(false);btn_mm4->setVisible(false);	
	UIButton* btn_mm5 = dynamic_cast <UIButton*>(myView->getWidgetByName("Button_Rankings"));
	btn_mm5->setEnabled(false);btn_mm5->setVisible(false);
	btn_mm1->addTouchEventListener(this, toucheventselector(Inicio::ButtonUpdate_MainMenu));
	btn_mm2->addTouchEventListener(this, toucheventselector(Inicio::ButtonUpdate_MainMenu));  
	btn_mm3->addTouchEventListener(this, toucheventselector(Inicio::ButtonUpdate_MainMenu));  	
	btn_mm4->addTouchEventListener(this, toucheventselector(Inicio::ButtonUpdate_MainMenu));	
	btn_mm5->addTouchEventListener(this, toucheventselector(Inicio::ButtonUpdate_MainMenu));	
	
	// Load Settings Widget //
	UIWidget* widget_settings;			
	widget_settings = GUIReader::shareReader()->widgetFromJsonFile("puzzle-settings.json");		
	myView->addWidget(widget_settings);
	// Settings Buttons & Images //	
	UIButton* btn_s1 = dynamic_cast <UIButton*>(myView->getWidgetByName("Button_Setting"));
	btn_s1->setEnabled(false);btn_s1->setVisible(false);
	UIButton* btn_s2 = dynamic_cast <UIButton*>(myView->getWidgetByName("Button_Gift"));
	btn_s2->setEnabled(false);btn_s2->setVisible(false);
	UIButton* btn_s3 = dynamic_cast <UIButton*>(myView->getWidgetByName("Button_Sound"));
	btn_s3->setEnabled(false);btn_s3->setVisible(false);
	UIImageView *imageArc = dynamic_cast <UIImageView*>(myView->getWidgetByName("Image_Arco"));
	imageArc->setEnabled(false); imageArc->setVisible(false);
	btn_s1->addTouchEventListener(this, toucheventselector(Inicio::ButtonUpdate_Settings));
	btn_s2->addTouchEventListener(this, toucheventselector(Inicio::ButtonUpdate_Settings));  
	btn_s3->addTouchEventListener(this, toucheventselector(Inicio::ButtonUpdate_Settings));	

	// Load Music
	CCLOG("preload music");
	SimpleAudioEngine::sharedEngine()->preloadBackgroundMusic("intro.mp3");	
	UIImageView* imageNoSound = dynamic_cast <UIImageView*>(myView->getWidgetByName("Image_NoSound"));
	imageNoSound->setEnabled(false);
	imageNoSound->setVisible(false);

	// Primero se muestra el Logo y luego se Activa el Menu
	CCActionInterval *seq1 = (CCActionInterval*)CCSequence::create(CCDelayTime::create(0.5f), CCCallFunc::create(this, callfunc_selector(Inicio::ActiveMainMenu)), NULL); 		
	this->runAction(seq1);	

	
    return true;
}

void Inicio::ButtonUpdate_MainMenu(CCObject* pSender, cocos2d::gui::TouchEventType type)
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
					FadeOutMainMenu();
					FadeOutSettings();
					CCActionInterval *seq2 = (CCActionInterval*)CCSequence::create(CCDelayTime::create(0.5f), CCCallFunc::create(this, callfunc_selector(Inicio::GotoSceneGame)), NULL); 		
					this->runAction(seq2);					
					}

				if (std::strcmp(btn->getName(), "Button_Facebook")==0) 
					{
					FadeOutMainMenu();
					FadeOutSettings();
					CCActionInterval *seq2 = (CCActionInterval*)CCSequence::create(CCDelayTime::create(0.5f), CCCallFunc::create(this, callfunc_selector(Inicio::GotoSceneTileMap)), NULL); 		
					this->runAction(seq2);					
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

void Inicio::ButtonUpdate_Settings(CCObject* pSender, cocos2d::gui::TouchEventType type)
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
	CCLOG("Goto SceneGame");
	CCScene *pScene = SceneGame::scene();	
	CCDirector::sharedDirector()->replaceScene(pScene);		

}

void Inicio::GotoSceneTileMap()
{		
	CCLOG("stop music");
	flag_music = false;
	SimpleAudioEngine::sharedEngine()->stopBackgroundMusic();
	CCLOG("Goto TileMap Scene");
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

void Inicio::ActiveMainMenu()  
{	
	imageMenu->setEnabled(true);
	imageMenu->setVisible(true);
	imageMenu->setTouchEnabled(true);	

	ShowLogo(false);	
	ShowMainMenu(true);
	ShowSettings(true);
	
	CCLOG("dont start music");
	flag_music = false;
	//SimpleAudioEngine::sharedEngine()->playBackgroundMusic("intro.mp3",true);
	UILayer* myView = (UILayer*) this->getChildByTag(1000);
	UIImageView* imageNoSound = dynamic_cast <UIImageView*>(myView->getWidgetByName("Image_NoSound"));
	imageNoSound->setEnabled(true);					
	
}

void Inicio::ShowLogo (bool value)
{	
	imageLogo->setEnabled(value);
	imageLogo->setVisible(value);
	imageLogo->setTouchEnabled(value);
}

void Inicio::ShowMainMenu(bool value)
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

void Inicio::ShowSettings(bool value)
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

void Inicio::FadeOutSettings()
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

void Inicio::FadeOutMainMenu()
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
