#include "Inicio.h"
#include "SceneGame.h"
#include "cocos-ext.h"
#include "TileMap.h"

//#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
//#include "platform/android/jni/JniHelper.h"
//#endif

#define MAXBUTTONS 8
#define TIME_LIMIT 1

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
	for (int i=0; i<MAXBUTTONS; i++) delete Btn[i];	

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
	imageLogo->setEnabled(true);imageLogo->setVisible(true);	
	
	// Main Menu
	imageMenu = dynamic_cast <UIImageView*>(myView->getWidgetByName("Image_Fondo_Menu"));
	imageMenu->setEnabled(false);
	imageMenu->setVisible(false);
	imageMenu->setTouchEnabled(false);	

	UIButton *btns[MAXBUTTONS];
	UILabelBMFont *lbls[MAXBUTTONS];
	UIImageView *imgs[MAXBUTTONS];

	UIPanel* Panel_MainMenu = dynamic_cast <UIPanel*>(myView->getWidgetByName("Panel_Botonera"));

	// Main Menu Buttons//	
	btns[0] = dynamic_cast <UIButton*>(myView->getWidgetByName("Button_Jugar"));	
	btns[1] = dynamic_cast <UIButton*>(myView->getWidgetByName("Button_Facebook"));	
	btns[2] = dynamic_cast <UIButton*>(myView->getWidgetByName("Button_Tienda"));	
	btns[3] = dynamic_cast <UIButton*>(myView->getWidgetByName("Button_Salir"));	
	btns[4] = dynamic_cast <UIButton*>(myView->getWidgetByName("Button_Rankings"));	
	lbls[0] = dynamic_cast <UILabelBMFont*>(myView->getWidgetByName("Label_Jugar")); 
	lbls[1] = dynamic_cast <UILabelBMFont*>(myView->getWidgetByName("Label_Facebook"));
	lbls[2] = dynamic_cast <UILabelBMFont*>(myView->getWidgetByName("Label_Tienda"));
	lbls[3] = NULL;
	lbls[4] = dynamic_cast <UILabelBMFont*>(myView->getWidgetByName("Label_Rankings"));
	imgs[0] = NULL;
	imgs[1] = dynamic_cast <UIImageView*>(myView->getWidgetByName("Image_10"));
	imgs[2] = NULL;
	imgs[3] = NULL;
	imgs[4] = NULL;	

	for (int i=0; i<5; i++)
	{
	btns[i]->addTouchEventListener(this, toucheventselector(Inicio::ButtonUpdate_MainMenu));
	btns[i]->setEnabled(false);
	btns[i]->setVisible(false);
	}	
	
	// Load Settings Widget //
	UIWidget* widget_settings;			
	widget_settings = GUIReader::shareReader()->widgetFromJsonFile("puzzle_settings.json");		
	myView->addWidget(widget_settings);
	// Settings Buttons & Images //	
	UIPanel* Panel_Settings = dynamic_cast <UIPanel*>(myView->getWidgetByName("Panel_Settings"));
	Panel_Settings->setZOrder(10);
	Panel_Settings->setTouchEnabled(false);
	
	btns[5] = dynamic_cast <UIButton*>(myView->getWidgetByName("Button_Setting"));	
	btns[6] = dynamic_cast <UIButton*>(myView->getWidgetByName("Button_Music"));	
	btns[7] = dynamic_cast <UIButton*>(myView->getWidgetByName("Button_Sound"));
	lbls[5] = dynamic_cast <UILabelBMFont*>(myView->getWidgetByName("Label_Settings")); 
	lbls[6] = dynamic_cast <UILabelBMFont*>(myView->getWidgetByName("Label_Music"));
	lbls[7] = dynamic_cast <UILabelBMFont*>(myView->getWidgetByName("Label_Sound"));
	imgs[5] = dynamic_cast <UIImageView*>(myView->getWidgetByName("Image_Arco"));
	imgs[5]->setScale(0);
	imgs[6] = dynamic_cast <UIImageView*>(myView->getWidgetByName("Image_NoMusic"));
	imgs[7] = dynamic_cast <UIImageView*>(myView->getWidgetByName("Image_NoSound"));
	
	for (int i=5; i<8; i++)
	{
	btns[i]->addTouchEventListener(this, toucheventselector(Inicio::ButtonUpdate_Settings));
	btns[i]->setEnabled(false);
	btns[i]->setVisible(false);	
	}	
	
	// Load Music
	LoadBackgroundMusic();
	LoadSounds();
	
	// Primero se muestra el Logo y luego se Activa el Menu
	CCActionInterval *seq1 = (CCActionInterval*)CCSequence::create(CCDelayTime::create(0.5f), CCCallFunc::create(this, callfunc_selector(Inicio::ActiveMainMenu)), NULL); 		
	this->runAction(seq1);	

	for (int i=0; i < MAXBUTTONS; i++)
	{
	Btn[i] = new AnimatedButtons;
	float panel_sx, panel_sy;
	if (i < 5) {panel_sx = Panel_MainMenu->getScaleX(); panel_sy = Panel_MainMenu->getScaleY();}
	else {panel_sx = Panel_Settings->getScaleX(); panel_sy = Panel_Settings->getScaleY();}
	Btn[i]->Init(btns[i], lbls[i], imgs[i], panel_sx, panel_sy);
	}	
	
	schedule( schedule_selector( SceneGame::update ) , GAME_REFRESH );
    return true;
}

bool Inicio::IsTouchOutsideButton(AnimatedButtons *btn, cocos2d::gui::UIPanel* panelBotonera)
{
	return btn->isPressedOutside(panelBotonera->getScaleX(), panelBotonera->getScaleY());
}

void Inicio::ButtonUpdate_MainMenu(CCObject* pSender, cocos2d::gui::TouchEventType type)
{

UIButton* btn = dynamic_cast <UIButton*>(pSender);
UILayer* myView = (UILayer*) this->getChildByTag(1000);
UIPanel* panelBotonera = dynamic_cast <UIPanel*>(myView->getWidgetByName("Panel_Botonera"));

int button = 0;
if (std::strcmp(btn->getName(), "Button_Jugar")==0) button = 0;
if (std::strcmp(btn->getName(), "Button_Facebook")==0) button = 1;
if (std::strcmp(btn->getName(), "Button_Tienda")==0) button = 2;
if (std::strcmp(btn->getName(), "Button_Salir")==0) button = 3;
if (std::strcmp(btn->getName(), "Button_Rankings")==0) button = 4;

	switch (type)
		{
			case TOUCH_EVENT_BEGAN:
				CCLOG("Button BEGAN");
				PlaySoundTouch();				
				Btn[button]->Began();				
				break;
            
			case TOUCH_EVENT_MOVED:
				CCLOG("Button MOVED");							
				Btn[button]->Moved();			
				break;
            
			case TOUCH_EVENT_ENDED:		

				CCLOG("Button ENDED");
				Btn[button]->Ended();
				
				if (std::strcmp(btn->getName(), "Button_Jugar")==0)
					{
					CCActionInterval *seq1 = (CCActionInterval*)CCSequence::create(CCDelayTime::create(0.5f), CCCallFunc::create(this, callfunc_selector(Inicio::FadeOutMainMenu)), NULL); 		
					this->runAction(seq1);										
					CCActionInterval *seq2 = (CCActionInterval*)CCSequence::create(CCDelayTime::create(0.5f), CCCallFunc::create(this, callfunc_selector(Inicio::FadeOutSettings)), NULL); 		
					this->runAction(seq2);															
					CCActionInterval *seq3 = (CCActionInterval*)CCSequence::create(CCDelayTime::create(1.0f), CCCallFunc::create(this, callfunc_selector(Inicio::GotoSceneGame)), NULL); 		
					this->runAction(seq3);					
					}

				if (std::strcmp(btn->getName(), "Button_Facebook")==0) 
					{
					CCActionInterval *seq1 = (CCActionInterval*)CCSequence::create(CCDelayTime::create(0.5f), CCCallFunc::create(this, callfunc_selector(Inicio::FadeOutMainMenu)), NULL); 		
					this->runAction(seq1);										
					CCActionInterval *seq2 = (CCActionInterval*)CCSequence::create(CCDelayTime::create(0.5f), CCCallFunc::create(this, callfunc_selector(Inicio::FadeOutSettings)), NULL); 		
					this->runAction(seq2);	
					CCActionInterval *seq3 = (CCActionInterval*)CCSequence::create(CCDelayTime::create(1.0f), CCCallFunc::create(this, callfunc_selector(Inicio::GotoSceneTileMap)), NULL); 		
					this->runAction(seq3);					
					}			

				if (std::strcmp(btn->getName(), "Button_Salir")==0) 
					{					
					CCActionInterval *seq1 = (CCActionInterval*)CCSequence::create(CCDelayTime::create(0.5f), CCCallFunc::create(this, callfunc_selector(Inicio::Salir)), NULL); 		
					this->runAction(seq1);									
					}				

				break;
            
			case TOUCH_EVENT_CANCELED:
				CCLOG("Button CANCELED");								
				Btn[button]->Canceled();
				break;
            
			default:
				break;
		}
	
}

void Inicio::ButtonUpdate_Settings(CCObject* pSender, cocos2d::gui::TouchEventType type)
{

UIButton* btn = dynamic_cast <UIButton*>(pSender);
UILayer* myView = (UILayer*) this->getChildByTag(1000);
UIPanel* panelSettings = dynamic_cast <UIPanel*>(myView->getWidgetByName("Panel_Settings"));
UIImageView *imageArc = dynamic_cast <UIImageView*>(myView->getWidgetByName("Image_Arco"));	
UIButton* btn_s2 = dynamic_cast <UIButton*>(myView->getWidgetByName("Button_Music"));
UIButton* btn_s3 = dynamic_cast <UIButton*>(myView->getWidgetByName("Button_Sound"));
UIImageView* imageNoSound = dynamic_cast <UIImageView*>(myView->getWidgetByName("Image_NoSound"));
UIImageView* imageNoMusic = dynamic_cast <UIImageView*>(myView->getWidgetByName("Image_NoMusic"));
UILabelBMFont *labelSound = dynamic_cast <UILabelBMFont*>(myView->getWidgetByName("Label_Sound"));
UILabelBMFont *labelMusic = dynamic_cast <UILabelBMFont*>(myView->getWidgetByName("Label_Music"));

CCLOG("Button Name: %s", btn->getName());

int button = 0;
if (std::strcmp(btn->getName(), "Button_Setting")==0) button = 5;
if (std::strcmp(btn->getName(), "Button_Music")==0) button = 6;
if (std::strcmp(btn->getName(), "Button_Sound")==0) button = 7;

	switch (type)
		{
			case TOUCH_EVENT_BEGAN:
				CCLOG("Button BEGAN");
				PlaySoundTouch();				
				Btn[button]->Began();
				
				if (std::strcmp(btn->getName(), "Button_Setting")==0) 
					{	
						if (imageArc->getScaleX() == 0)
						{
						ShowSettings(true, true);
						CCScaleTo *scale1 = CCScaleTo::create(5/30.f,2,2);						
						imageArc->runAction(CCSequence::create(scale1, NULL));					
						}

						if (imageArc->getScaleX() == 2)						
						{
						ShowSettings(true, false);
						CCScaleTo *scale1 = CCScaleTo::create(5/30.f,0,0);						
						imageArc->runAction(CCSequence::create(scale1, NULL));					
					
						}
				
					}

				if (std::strcmp(btn->getName(), "Button_Music")==0) 
					{
					UILayer* myView = (UILayer*) this->getChildByTag(1000);
					UIImageView* imageNoMusic = dynamic_cast <UIImageView*>(myView->getWidgetByName("Image_NoMusic"));
					
					if(flag_music == true) 
						{imageNoMusic->setEnabled(true);
						 imageNoMusic->setVisible(true);
						 PauseBackgroundMusic();						 
						}
					else{
						imageNoMusic->setEnabled(false);
						imageNoMusic->setVisible(false);
						PlayBackgroundMusic();						
						}
					}

				if (std::strcmp(btn->getName(), "Button_Sound")==0) 
					{
					UILayer* myView = (UILayer*) this->getChildByTag(1000);
					UIImageView* imageNoMusic = dynamic_cast <UIImageView*>(myView->getWidgetByName("Image_NoSound"));
					
					if(flag_sounds == true) 
						{
						imageNoSound->setEnabled(true);
						imageNoSound->setVisible(true);
						PauseSounds();						 
						}
					else{
						imageNoSound->setEnabled(false);
						imageNoSound->setVisible(false);
						ResumeSounds();	
						PlaySoundTouch();				
						}
					}
				break;
            
			case TOUCH_EVENT_MOVED:
				CCLOG("Button MOVED");							
				Btn[button]->Moved();			
				break;
            
			case TOUCH_EVENT_ENDED:	
				CCLOG("Button ENDED");				
				Btn[button]->Ended();
				break;
            
			case TOUCH_EVENT_CANCELED:					
				Btn[button]->Canceled();
				break;
            
			default:
				break;
		}
	
}


void Inicio::GotoSceneGame()
{	
	StopBackgroundMusic();
	CCLOG("Goto SceneGame");
	CCScene *pScene = SceneGame::scene();	
	CCDirector::sharedDirector()->replaceScene(pScene);
}

void Inicio::GotoSceneTileMap()
{		
	StopBackgroundMusic();
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
	ShowSettings(true, false);	
	
	CCLOG("dont start music");
	flag_music = false;	
	flag_sounds = true;
}

void Inicio::ShowLogo (bool value)
{	
	imageLogo->setEnabled(value);
	imageLogo->setVisible(value);
	imageLogo->setTouchEnabled(value);
}

void Inicio::ShowMainMenu(bool value)
{
	if (value == true)
	{
	Btn[0]->Show();
	Btn[1]->Show();
	Btn[2]->Show();	
	Btn[3]->Show();
	Btn[4]->Show();	
	}
	else 
	{
	Btn[0]->Hide();
	Btn[1]->Hide();
	Btn[2]->Hide();	
	Btn[3]->Hide();
	Btn[4]->Hide();	
	}
}

void Inicio::ShowSettings(bool value1, bool value2)
{
	if (value1 == true)
	{
	Btn[5]->Show();
	Btn[6]->Show();	
	Btn[6]->UIImg->setVisible(!flag_music);
	Btn[7]->Show();
	Btn[7]->UIImg->setVisible(!flag_sounds);
	if (value2 == false)
		{		
		Btn[6]->Hide();
		Btn[7]->Hide();
		}
	}
	else 
	{
	Btn[5]->Hide();
	Btn[6]->Hide();
	Btn[7]->Hide();	
	}
	
}

void Inicio::FadeOutSettings()
{
	Btn[5]->FadeOut(0.3f);
	Btn[6]->FadeOut(0.3f);
	Btn[7]->FadeOut(0.3f);	
}

void Inicio::FadeOutMainMenu()
{
	CCActionInterval *seqa1 = (CCActionInterval*)CCSequence::create(CCFadeOut::create(0.5f), NULL); 		
	imageMenu->runAction(seqa1);
	Btn[0]->FadeOut(0.3f);
	Btn[1]->FadeOut(0.3f);
	Btn[2]->FadeOut(0.3f);
	Btn[3]->FadeOut(0.3f);
	Btn[4]->FadeOut(0.3f);	
	}


void Inicio::update(float dt)
{
	Btn[0]->Update(dt);
	Btn[1]->Update(dt);
	Btn[2]->Update(dt);
	Btn[3]->Update(dt);
	Btn[4]->Update(dt);
	Btn[5]->Update(dt);
	Btn[6]->Update(dt);
	Btn[7]->Update(dt);

	int contar = 0;
	for (int i=0; i < MAXBUTTONS; i++)
		{
			if (Btn[i]->isPressed() == false) contar++;
		}
	if (contar == 8) {SetTouchEnabledSettings(true); SetTouchEnabledMainMenu(true);}
	else {SetTouchEnabledSettings(false); SetTouchEnabledMainMenu(false);}

}

void Inicio::SetTouchEnabledSettings(bool value)
{
	Btn[0]->SetTouchable(value);
	Btn[1]->SetTouchable(value);
	Btn[2]->SetTouchable(value);
	Btn[3]->SetTouchable(value);
	Btn[4]->SetTouchable(value);	

}
void Inicio::SetTouchEnabledMainMenu(bool value)
{
	Btn[5]->SetTouchable(value);
	Btn[6]->SetTouchable(value);
	Btn[7]->SetTouchable(value);		
}
void Inicio::LoadBackgroundMusic()
{	CCLOG("preload background music");
	SimpleAudioEngine::sharedEngine()->preloadBackgroundMusic("intro.mp3");		
}

void Inicio::PlayBackgroundMusic()
{
	if (SimpleAudioEngine::sharedEngine()->isBackgroundMusicPlaying()) 
	{
	SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();	
	CCLOG("resume music");	
	}
	
	if (!SimpleAudioEngine::sharedEngine()->isBackgroundMusicPlaying()) 
		{
		SimpleAudioEngine::sharedEngine()->playBackgroundMusic("intro.mp3",true);
		CCLOG("play music");
		}
						
	flag_music = true;
}

void Inicio::PauseBackgroundMusic()
{
	CCLOG("pause music");	
	flag_music = false;
	SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();	
}

void Inicio::StopBackgroundMusic()
{
	CCLOG("stop music");	
	flag_music = false;
	SimpleAudioEngine::sharedEngine()->stopBackgroundMusic();	
}

void Inicio::LoadSounds()
{
	CCLOG("preload sounds");
	SimpleAudioEngine::sharedEngine()->preloadEffect("button-settings.wav"); 	
}
void Inicio::PlaySoundTouch()
{
	if (flag_sounds == true)
	SimpleAudioEngine::sharedEngine()->playEffect("button-settings.wav");								
}
void Inicio::PauseSounds()
{
	flag_sounds = false;
}
void Inicio::ResumeSounds()
{
	flag_sounds = true;	
}