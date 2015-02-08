//---------------------------------------------------------------------------------------------------------------------------
#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__
//---------------------------------------------------------------------------------------------------------------------------
#include "cocos2d.h"
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
	void			createFichaSpr(int ofs,int _modo,CCPoint* p0,CCPoint* p1);

	void			createTableroSpr();
	
	
	void			romperFicha(int ofs);
	void			desactivarFicha(int ofs);
	void			copiarFicha(int ofs0,int ofsD);
	void			moverFicha(int ofs0,int ofsD);

	bool			flagAcomodarTablero;

	int				markCount;
	FICHA			ficha[TABLERO_LEN];
	CCSprite*		pSprNumero[TABLERO_LEN];
	CCSprite*		pSprForma[TABLERO_LEN];
	CCSprite*		pSprBg;
	CCSprite*		pSprBgGame;

	//-Mark------------------------------------------------//
	CCSprite*		pSprTableroMark[TABLERO_LEN];
	void			resetTableroMark();
	void			setTableroMark(int x,int y);

	//-FX explo-------------------------------------------//
	CCTexture2D*	pTexFxExplo;
	CCParticleSun*	pFxExplo[MAX_FX_EXPLO];
	int				cont_fx_explo;
	void			initFxExplo();
	void			fxExplo(float xx,float yy);
	void			updateFxExplo(float dt);

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
