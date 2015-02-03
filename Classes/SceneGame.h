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

	//-Textures--------------------------------------------//
	CCTexture2D*	pTex[MAX_TEXTURE];

	//-Tablero---------------------------------------------//
	int				getTableroOfs(int x,int y);
	int				getTableroX(int len);
	int				getTableroY(int len);
	void			initTablero();
	void			createTablero();
	void			createFichaSpr(int ofs);

	void			createTableroSpr();
	
	void			romperFicha(int ofs);
	void			desactivarFicha(int ofs);
	void			copiarFicha(int ofs0,int ofsD);

	bool			flagAcomodarTablero;

	FICHA			ficha[TABLERO_LEN];
	CCSprite*		pSprNumero[TABLERO_LEN];
	CCSprite*		pSprForma[TABLERO_LEN];
	CCSprite*		pSprBg;
	CCSprite*		pSprBgGame;

	//-Mark------------------------------------------------//
	//int				tableroMark[TABLERO_LEN];
	//int				tableroBreak[TABLERO_LEN];
	CCSprite*		pSprTableroMark[TABLERO_LEN];
	void			resetTableroMark();
	void			setTableroMark(int x,int y);

	//-Game-----------------------------------------------//
	void			update(float dt);
	void			checkMarked();
	void			tableroLock();
	void			tableroUnlock();
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
