//---------------------------------------------------------------------------------------------------------------------------
#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__
//---------------------------------------------------------------------------------------------------------------------------
#include "cocos2d.h"
#include "Box2D/Box2D.h"
#include "SimpleAudioEngine.h"
//---------------------------------------------------------------------------------------------------------------------------
#include "_constantes.h"
#include "Ficha.h"
//---------------------------------------------------------------------------------------------------------------------------
using namespace cocos2d;
//---------------------------------------------------------------------------------------------------------------------------
//
//---------------------------------------------------------------------------------------------------------------------------
class SceneGame : public cocos2d::CCLayer
{
public:

	//-Sizes------------------------------------------------//
	float						_HLX,_HLY;
	float						_LX,_LY;
	float						_OX,_OY;

	//-Fichas----------------------------------------------//
	FICHA			ficha[MAX_FICHA];
	int				fichaBoxMark[MAX_FICHA];

	//-BoxMark---------------------------------------------//
	CCSprite*		pSprMark[TABLERO_LEN];
	void			resetBoxMarks();
	void			setBoxMark(float x,float y);

	//-Sprites---------------------------------------------//
	CCTexture2D*	pTex[MAX_TEXTURE];
	CCSprite*		pSprNumero[TABLERO_LEN];
	CCSprite*		pSprForma[TABLERO_LEN];

	//-Game-----------------------------------------------//
	void			createTableroFichas();
	void			createTableroSpr();
	void			update(float dt);
	
	//-Tools-----------------------------------------------//
	int				azar( int low , int high );

	//-Touch-----------------------------------------------//
	void			initTouches();
	void			ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent);
	void			ccTouchesMoved(CCSet *pTouches, CCEvent *pEvent);
	void			ccTouchesEnded(CCSet *pTouches, CCEvent *pEvent);
	int				touchId;
	bool			flagTouchMoved;
	bool			flagTouchCalc;
	bool			flagScaling;
	CCPoint			touchMoved;				// movimiento acumulado , se usa con flagTouchCalc
	CCPoint			touchTMoved;
	CCPoint			touchMov;				// movimiento no acumulado
	CCPoint			touchPos0;
	CCPoint			touchPosL;
	CCPoint			touchPosF;

	//-Cocos2dx--------------------------------------------//
    virtual bool				init();
    static cocos2d::CCScene*	scene();
    void						menuCloseCallback(CCObject* pSender);
    void						menuNewMapCallback(CCObject* pSender);
    CREATE_FUNC(SceneGame);
};
//---------------------------------------------------------------------------------------------------------------------------
#endif
//---------------------------------------------------------------------------------------------------------------------------
