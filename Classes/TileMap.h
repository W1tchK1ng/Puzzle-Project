#ifndef __TileMap_SCENE_H__
#define __TileMap_SCENE_H__

#include "cocos2d.h"
#include "cocos-ext.h"

class TileMap : public cocos2d::CCLayer
{
public:
	TileMap();
	~TileMap();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  

    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::CCScene* scene();
//	void ccTouchesMoved(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent);
    
    // a selector callback	
	void GotoSceneGame();
	void MovePlayerToLevel(int level);
	void PresentNextLevel();
	void update(float delta);
	double GetFloatPrecision(double value, double precision);
	void ButtonUpdate(CCObject* pSender, cocos2d::gui::TouchEventType type);		
	cocos2d::CCPoint old_position;
	cocos2d::CCPoint new_position;

	bool llego;
	int next_level;
	
    // implement the "static node()" method manually
    CREATE_FUNC(TileMap);

	};

#endif // __TileMap_SCENE_H__
