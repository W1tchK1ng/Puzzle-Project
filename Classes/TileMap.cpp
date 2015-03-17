#include "TileMap.h"
#include "SceneGame.h"
#include "cocos-ext.h"
#include "Inicio.h"

#define FIRSTOBJECTGID 100

USING_NS_CC;
using namespace cocos2d::extension;
using namespace cocos2d::gui;
using namespace CocosDenshion;

TileMap::~TileMap()
{
	CCArmatureDataManager::purge();
	SceneReader::purge();
	ActionManager::purge();
	GUIReader::purge();	
}

TileMap::TileMap()
{
	
}

CCScene* TileMap::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();    
    // 'layer' is an autorelease object
    TileMap *layer = TileMap::create();
    // add layer as a child to scene
    scene->addChild(layer);
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool TileMap::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() )    { return false; }

	setKeypadEnabled(true);
	setTouchEnabled(true);

	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();

	// Crea una UILayer y la pone como child de la Scene actual

	UILayer *myView = UILayer::create();
	this->addChild(myView, 1, 1000);	
	UIWidget* widget;			
	widget = GUIReader::shareReader()->widgetFromJsonFile("ScrollViewMap.json");		
	myView->addWidget(widget);	

	UIScrollView* sv = dynamic_cast <UIScrollView*>(myView->getWidgetByName("ScrollView"));		
	//sv->setBounceEnabled(true);
	sv->setInertiaScrollEnabled(true);

	//CCTMXTiledMap* map = CCTMXTiledMap::create("orthogonal-test2.tmx");
	CCTMXTiledMap* map = CCTMXTiledMap::create("road.tmx");
	this->addChild(map, 0, 100);	
	
	//CCTMXMapInfo *mapInfo = CCTMXMapInfo::formatWithTMXFile("road.tmx");
	//CCTMXTilesetInfo *info = (CCTMXTilesetInfo*) mapInfo->getTilesets()->objectAtIndex(1);

	CCSize tile_size = map->getTileSize();
	CCSize map_size = map->getMapSize();
	//float tiles_x = 16;
	//float tiles_y = 64;
	float zoom1 = 1;
	float zoom2 = 1;

	sv->setInnerContainerSize(CCSize(tile_size.width*map_size.width*zoom2, tile_size.height*map_size.height*zoom2));
	sv->scrollToBottom(1, true);
	
	//sv->getInnerContainer()->setPosition(ccp(0, 0)); 
	//sv->getInnerContainer()->updateTransform();

	CCArray* pChildrenArray = map->getChildren();
    CCSpriteBatchNode* child = NULL;
    CCObject* pObject = NULL;
    CCARRAY_FOREACH(pChildrenArray, pObject)
    {
        child = (CCSpriteBatchNode*)pObject;

        if(!child)
            break;

        child->getTexture()->setAntiAliasTexParameters();
    }
	map->setAnchorPoint(ccp(0, 0));	
	map->setScale(zoom1);	

	CCArray *ObjectGroups = map->getObjectGroups();		
	CCTMXObjectGroup *objects = (CCTMXObjectGroup *) ObjectGroups->objectAtIndex(0);			
	CCArray *Todos = objects->getObjects();		
	CCDictionary* spawnPointTodos = NULL;
    CCObject* pObj = NULL;
	int i = 50;
	CCARRAY_FOREACH(Todos, pObj)
	{
	spawnPointTodos = (CCDictionary*)pObj;
	int x = ((CCString)*spawnPointTodos->valueForKey("x")).intValue();
	int y = ((CCString)*spawnPointTodos->valueForKey("y")).intValue(); 
	int gid = ((CCString)*spawnPointTodos->valueForKey("gid")).intValue(); 	
	if (gid > FIRSTOBJECTGID-1) 
		{std::string filename;
		 getSpriteNameGID(gid, &filename);
		 CCSprite *player = CCSprite::create(filename.c_str());
		 player->setPosition(ccp(x,y)); 
		 player->setAnchorPoint(ccp(0,0));
		 int zorder = 0;
		 if (i == 50) zorder = 1;
		 map->addChild(player,zorder, i);			 
		 i++;
		 }	
	}
	

	schedule( schedule_selector( TileMap::update ) , 1.0f / 60 );

	UIButton* btn1 = dynamic_cast <UIButton*>(myView->getWidgetByName("Button_Salir"));
	btn1->addTouchEventListener(this, toucheventselector(TileMap::ButtonUpdate));
	
	llego = false;
	next_level = 1;
	MovePlayerToLevel(next_level);

    return true;
}

void TileMap::GotoSceneGame()
{		
	CCScene *pScene = SceneGame::scene();	
	CCDirector::sharedDirector()->replaceScene(pScene);		

}

void TileMap::update(float delta)
{
	CCTMXTiledMap* map = (cocos2d::CCTMXTiledMap*) this->getChildByTag(100);	
	UILayer* myView = (UILayer*) this->getChildByTag(1000);	
	UIScrollView* sv = dynamic_cast <UIScrollView*>(myView->getWidgetByName("ScrollView"));	
		
	new_position = sv->getInnerContainer()->getPosition();
	//if (new_position.y != 0) new_position.y = 0;
	new_position.x = GetFloatPrecision(new_position.x, 0);
	new_position.y = GetFloatPrecision(new_position.y, 0);
	
	if (new_position.x != old_position.x || new_position.y != old_position.y)
		{
		map->setPosition(new_position);		
		old_position = new_position;
		}

	if (llego == true) {MovePlayerToLevel(next_level); llego = false;}
			
	//CCLOG("x: %f y: %f", new_position.x, new_position.y);
}

double TileMap::GetFloatPrecision(double value, double precision)
{
    return (floor((value * pow(10, precision) + 0.5)) / pow(10, precision)); 
}

void TileMap::ButtonUpdate(CCObject* pSender, cocos2d::gui::TouchEventType type)
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

				if (std::strcmp(btn->getName(), "Button_Salir")==0) 
					{	
					CCScene *pScene = Inicio::scene();	
					CCDirector::sharedDirector()->replaceScene(pScene);						
					}
			break;
            
			case TOUCH_EVENT_CANCELED:				
				break;
            
			default:
				break;

		}
}

void TileMap::MovePlayerToLevel(int level)
	{
		CCTMXTiledMap* map = (CCTMXTiledMap*) this->getChildByTag(100); 
		CCSprite *player = (CCSprite *) map->getChildByTag(50);
		CCArray *ObjectGroups = map->getObjectGroups();	
		CCTMXObjectGroup *objects = (CCTMXObjectGroup *) ObjectGroups->objectAtIndex(0);
		
		std::string level_number;
		level_number.append("Nivel ");
		const char *codigo = CCString::createWithFormat("%01d", level)->getCString();
		level_number.append(codigo);		
		CCDictionary *spawnPoint = objects->objectNamed(level_number.c_str()); 
		int x = ((CCString)*spawnPoint->valueForKey("x")).intValue();
		int y = ((CCString)*spawnPoint->valueForKey("y")).intValue();	
		CCPoint delta;
		delta.x = x - player->getPositionX();
		delta.y = y - player->getPositionY();
		if (delta.x < 0) player->setFlipX(true); else player->setFlipX(false);
		CCActionInterval *seq = (CCActionInterval*)CCSequence::create(CCDelayTime::create(0.25f), CCMoveBy::create(0.25f, delta), CCCallFunc::create(this, callfunc_selector(TileMap::PresentNextLevel)), NULL); 		
		player->runAction(seq);

	}

void TileMap::PresentNextLevel()
{
	llego = true;
	next_level++;
	if (next_level > 55) next_level = 1;

}

void TileMap::getSpriteNameGID(int gid, std::string *file_string)
	{		
		int first_gid = FIRSTOBJECTGID;
		file_string->append("gid");
		const char *codigo = CCString::createWithFormat("%03d", gid-first_gid)->getCString();	
		file_string->append(codigo);
		file_string->append(".png");				
	}
