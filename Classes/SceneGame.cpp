//---------------------------------------------------------------------------------------------------------------------------
#include "SceneGame.h"
#include "AdmobHelper.h"
#include "Inicio.h"

//---------------------------------------------------------------------------------------------------------------------------
using namespace cocos2d;
//---------------------------------------------------------------------------------------------------------------------------
// scene
//---------------------------------------------------------------------------------------------------------------------------
CCScene* SceneGame::scene()
{
    CCScene * scene = NULL;
    do 
    {
        // 'scene' is an autorelease object
        scene	= CCScene::create();
        CC_BREAK_IF(! scene);
        // 'layer' is an autorelease object
        SceneGame *layer = SceneGame::create();
        CC_BREAK_IF(! layer);
        // add layer as a child to scene
        scene->addChild(layer);
    } while (0);

    // return the scene
    return scene;
}
//---------------------------------------------------------------------------------------------------------------------------
// init
//---------------------------------------------------------------------------------------------------------------------------
bool SceneGame::init()
{
	// super init first
	CCLayer::init();

	// Accelerometer & Touch
	setAccelerometerEnabled(false);
	initTouches();

	// Calcula valores del centro y desplazamiento general
	CCSize	size		= CCDirector::sharedDirector()->getVisibleSize();
	CCPoint origin		= CCDirector::sharedDirector()->getVisibleOrigin();
	CCSize	winsize		= CCDirector::sharedDirector()->getWinSize();
	_OX					= origin.x;
	_OY					= origin.y;
	_LX					= size.width;
	_LY					= size.height;
	_HLX				= (size.width/2.0f);
	_HLY				= (size.height/2.0f);
	CCLog("Oxy(%.0f,%.0f) Lxy(%.0f,%.0f) HLxy(%.0f,%.0f)",_OX,_OY,_HLX,_HLY,_LX,_LY);

	// Textures
	pTex[IDX_NUMERO_1]				= CCTextureCache::sharedTextureCache()->addImage( "1.png" );
	pTex[IDX_NUMERO_2]				= CCTextureCache::sharedTextureCache()->addImage( "2.png" );
	pTex[IDX_NUMERO_3]				= CCTextureCache::sharedTextureCache()->addImage( "3.png" );
	pTex[IDX_NUMERO_4]				= CCTextureCache::sharedTextureCache()->addImage( "4.png" );
	pTex[IDX_NUMERO_5]				= CCTextureCache::sharedTextureCache()->addImage( "5.png" );
	pTex[IDX_NUMERO_6]				= CCTextureCache::sharedTextureCache()->addImage( "6.png" );
	pTex[IDX_NUMERO_7]				= CCTextureCache::sharedTextureCache()->addImage( "7.png" );
	//pTex[IDX_NUMERO_7]				= CCTextureCache::sharedTextureCache()->addImage( "cock.png" );
	pTex[IDX_NUMERO_8]				= CCTextureCache::sharedTextureCache()->addImage( "8.png" );
	//pTex[IDX_NUMERO_8]				= CCTextureCache::sharedTextureCache()->addImage( "swan.png" );
	pTex[IDX_NUMERO_9]				= CCTextureCache::sharedTextureCache()->addImage( "9.png" );
	//pTex[IDX_NUMERO_9]				= CCTextureCache::sharedTextureCache()->addImage( "bird.png" );

	pTex[IDX_FORMA_BOX]				= CCTextureCache::sharedTextureCache()->addImage( "box.png" );
	pTex[IDX_FORMA_CIRCLE]			= CCTextureCache::sharedTextureCache()->addImage( "circle.png" );
	pTex[IDX_FORMA_STAR]			= CCTextureCache::sharedTextureCache()->addImage( "star.png" );
	pTex[IDX_FORMA_DONUT]			= CCTextureCache::sharedTextureCache()->addImage( "donut.png" );
	pTex[IDX_FORMA_HEXAGON]			= CCTextureCache::sharedTextureCache()->addImage( "hexagon.png" );
	pTex[IDX_FORMA_SPIRAL]			= CCTextureCache::sharedTextureCache()->addImage( "spiral.png" );
	pTex[IDX_TABLEROMARK]			= CCTextureCache::sharedTextureCache()->addImage( "boxmark.png" );
	pTex[IDX_BG_001]				= CCTextureCache::sharedTextureCache()->addImage( "bg001.png" );
	pTex[IDX_BG_GAME]				= CCTextureCache::sharedTextureCache()->addImage( "gamebg.png" );
	//pTex[IDX_BG_GAME]				= CCTextureCache::sharedTextureCache()->addImage( "inca.png" );

	// inicializa los sprites
	initTablero();
	createTablero();
	createTableroSpr();
	resetTableroMark();
	
	initFxExplo();

	// Create a "close" menu item with close icon, it's an auto release object.
	CCMenuItemImage *pCloseItem		= CCMenuItemImage::create( "CloseNormal.png","CloseSelected.png", this, menu_selector(SceneGame::menuCloseCallback)); 
	pCloseItem->setPosition(ccp( _LX - pCloseItem->getContentSize().width/2, pCloseItem->getContentSize().height/2));
	CCMenuItemImage *pNewMapItem	= CCMenuItemImage::create( "CloseNormal.png","CloseSelected.png", this, menu_selector(SceneGame::menuNewMapCallback)); 
	pNewMapItem->setPosition(ccp( pCloseItem->getContentSize().width/2, pCloseItem->getContentSize().height/2));
	CCMenu* pMenu = CCMenu::create(pCloseItem,pNewMapItem,NULL);
	pMenu->setPosition(CCPointZero);
	addChild(pMenu, 1, 10);

	// Update
	schedule( schedule_selector( SceneGame::update ) , GAME_REFRESH );
	
	#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID) 
	if (!AdmobHelper::isAdShowing) AdmobHelper::showAd();
	#endif

	return true;
}
//---------------------------------------------------------------------------------------------------------------------------
// create tablero fichas
//---------------------------------------------------------------------------------------------------------------------------
void SceneGame::createTablero()
{
	int	o,valor,total;
	total	= 0;
	for(o=0;o<TABLERO_LEN;o++)
	{
		// numero
		if(o==(TABLERO_LEN-1))
		{
			// valor es lo que falta para que la suma de todas las fichas sea multiplo de 10
			valor	= 10 - total%10;
			// si justo da multiplo de 10 faltando crear la ultima ficha 
			// entonces crea un nivel nuevo de cero
			if(valor == 0)
			{
				o		= 0;
				total	= 0;
				valor	= azar( 1 , 10 );
				CCLog("ATENCION!! : Se creo el nivel otra vez por ser todas las fichas-1 multiplo de 10");
			}
		}
		else
			valor	= azar( 1 , 10 );

		total	+= valor;
		// datos basicos de la ficha
		ficha[o].set( valor-1 , azar( IDX_FORMA_BOX,IDX_FORMA_DONUT+0) , azar( IDX_COLOR_ROJO,IDX_COLOR_NEGRO+1) );
		// set data
		ficha[o].x		= o % TABLERO_LX;
		ficha[o].y		= o / TABLERO_LX;
		ficha[o].ofs	= o;
		ficha[o].posx	= float(TABLERO_OX+(ficha[o].x*FICHA_LX));
		ficha[o].posy	= float(TABLERO_OY+(ficha[o].y*FICHA_LY));
	}

	// log
	CCLog("Todas las fichas del nivel suman : %i",total);
}
//---------------------------------------------------------------------------------------------------------------------------
// create ficha spr
//---------------------------------------------------------------------------------------------------------------------------
void SceneGame::createFichaSpr(int idx,int _modo,CCPoint* p0,CCPoint* p1)
{
	CCPoint				pos;
	CCActionInterval*	action1;
	CCActionInterval*	action2;
	CCActionInterval*	action3;
	CCActionInterval*	action4;

	// init
	action1				= NULL;
	action2				= NULL;
	action3				= NULL;
	action4				= NULL;

	// filtros
	if(idx < 0)					{ CCLog("ERROR : SceneGame::createFichaSpr(%i) ofs menor que cero"); return; }
	if(idx >= TABLERO_LEN)		{ CCLog("ERROR : SceneGame::createFichaSpr(%i) ofs mayor que TABLERO_LEN"); return; }
	if(pSprNumero[idx] != NULL) { CCLog("ERROR : SceneGame::createFichaSpr(%i) pSprNumero no null"); return; }
	if(pSprForma[idx] != NULL)	{ CCLog("ERROR : SceneGame::createFichaSpr(%i) pSprForma no null"); return; }
	if(_modo < 0)				{ CCLog("ERROR : SceneGame::createFichaSpr(%i) modo erroneo"); return; }

	// alloc
	pSprNumero[idx]		= new CCSprite;
	pSprForma[idx]		= new CCSprite;

	// spr numero
	if(ficha[idx].numero == IDX_NUMERO_1)			pSprNumero[idx]->initWithTexture( pTex[IDX_NUMERO_1 ] );
	else if(ficha[idx].numero == IDX_NUMERO_2)		pSprNumero[idx]->initWithTexture( pTex[IDX_NUMERO_2 ] );
	else if(ficha[idx].numero == IDX_NUMERO_3)		pSprNumero[idx]->initWithTexture( pTex[IDX_NUMERO_3 ] );
	else if(ficha[idx].numero == IDX_NUMERO_4)		pSprNumero[idx]->initWithTexture( pTex[IDX_NUMERO_4 ] );
	else if(ficha[idx].numero == IDX_NUMERO_5)		pSprNumero[idx]->initWithTexture( pTex[IDX_NUMERO_5 ] );
	else if(ficha[idx].numero == IDX_NUMERO_6)		pSprNumero[idx]->initWithTexture( pTex[IDX_NUMERO_6 ] );
	else if(ficha[idx].numero == IDX_NUMERO_7)		pSprNumero[idx]->initWithTexture( pTex[IDX_NUMERO_7 ] );
	else if(ficha[idx].numero == IDX_NUMERO_8)		pSprNumero[idx]->initWithTexture( pTex[IDX_NUMERO_8 ] );
	else if(ficha[idx].numero == IDX_NUMERO_9)		pSprNumero[idx]->initWithTexture( pTex[IDX_NUMERO_9 ] );
	// spr forma
	if(ficha[idx].forma == IDX_FORMA_STAR)			pSprForma[idx]->initWithTexture( pTex[IDX_FORMA_STAR ] );
	else if(ficha[idx].forma == IDX_FORMA_CIRCLE)	pSprForma[idx]->initWithTexture( pTex[IDX_FORMA_CIRCLE ] );
	else if(ficha[idx].forma == IDX_FORMA_BOX)		pSprForma[idx]->initWithTexture( pTex[IDX_FORMA_BOX ] );
	else if(ficha[idx].forma == IDX_FORMA_HEXAGON)	pSprForma[idx]->initWithTexture( pTex[IDX_FORMA_HEXAGON ] );
	else if(ficha[idx].forma == IDX_FORMA_SPIRAL)	pSprForma[idx]->initWithTexture( pTex[IDX_FORMA_SPIRAL ] );
	else if(ficha[idx].forma == IDX_FORMA_DONUT)	pSprForma[idx]->initWithTexture( pTex[IDX_FORMA_DONUT ] );
	// color
	if(ficha[idx].color == IDX_COLOR_ROJO)			pSprForma[idx]->setColor( ccc3(255,50,50) );
	else if(ficha[idx].color == IDX_COLOR_VERDE)	pSprForma[idx]->setColor( ccc3(50,255,50) );
	else if(ficha[idx].color == IDX_COLOR_AZUL)		pSprForma[idx]->setColor( ccc3(50,50,255) );
	else if(ficha[idx].color == IDX_COLOR_AMARILLO)	pSprForma[idx]->setColor( ccc3(255,255,50) );
	else if(ficha[idx].color == IDX_COLOR_MAGENTA)	pSprForma[idx]->setColor( ccc3(255,50,255) );
	else if(ficha[idx].color == IDX_COLOR_CYAN)		pSprForma[idx]->setColor( ccc3(50,255,255) );
	else if(ficha[idx].color == IDX_COLOR_BLANCO)	pSprForma[idx]->setColor( ccc3(255,255,255) );
	else if(ficha[idx].color == IDX_COLOR_NEGRO)	pSprForma[idx]->setColor( ccc3(90,90,90) );
	
	// posicion segun modo
	if(_modo == CREATE_MODE_FALL)
	{
		pos		= *p0;
		action1	= CCMoveTo::create( 0.5f , *p1 );
		action2	= CCMoveTo::create( 0.5f , *p1 );

		action3	= CCEaseIn::create( action1 , 2.0f );
		action4	= CCEaseIn::create( action2 , 2.0f );
		
		//action1	= CCJumpTo::create( 0.2f , *p1 , -25.0f , 1 );
		//action2	= CCJumpTo::create( 0.2f , *p1 , -25.0f , 1 );
	}
	// posicion basica
	else
	{
		pos		= ccp( ficha[idx].posx , ficha[idx].posy );
	}

	// ubica sprite , agrega a scene
	if(pSprForma[idx] != NULL)
	{
		pSprForma[idx]->setPosition(pos);
		pSprForma[idx]->setVisible(true);
		addChild( pSprForma[idx] , Z_ORDER_FORMA );
	}
	if(pSprNumero[idx] != NULL)
	{
		pSprNumero[idx]->setPosition(pos);
		pSprNumero[idx]->setVisible(true);
		addChild( pSprNumero[idx] , Z_ORDER_NUMERO );
	}
	// action
	if(action1 != NULL)
	{
		pSprForma[idx]->runAction( action3 );
	}
	if(action2 != NULL)
	{
		pSprNumero[idx]->runAction( action4 );
	}

	//CCLog("createFichaSpr(%i,%i,ccp,ccp)",idx,_modo);

}
//---------------------------------------------------------------------------------------------------------------------------
// create tablero spr
//---------------------------------------------------------------------------------------------------------------------------
void SceneGame::createTableroSpr()
{
	int			xx,yy,idx;
	int			o;

	// release
	for(o=0;o<TABLERO_LEN;o++)
	{
		if(pSprNumero[o] != NULL)
		{
			removeChild( pSprNumero[o] , true );
			pSprNumero[o]->release();
			pSprNumero[o]	= NULL;
		}
		if(pSprForma[o] != NULL)
		{
			removeChild( pSprForma[o] , true );
			pSprForma[o]->release();
			pSprForma[o]	= NULL;
		}
	}
	// bg
	if(pSprBg == NULL)
	{
		pSprBg	= new CCSprite;
		pSprBg->initWithTexture( pTex[IDX_BG_001] );
		//pSprBg->setAnchorPoint(ccp(0.0f,0.0f));
		pSprBg->setVisible(true);
		pSprBg->setPosition(ccp(_HLX,_HLY+64));
		addChild(pSprBg,Z_ORDER_BG);
	}
	if(pSprBgGame == NULL)
	{
		pSprBgGame	= new CCSprite;
		pSprBgGame->initWithTexture( pTex[IDX_BG_GAME] );
		pSprBgGame->setVisible(true);
		pSprBgGame->setPosition(ccp(_HLX,_HLY));
		addChild(pSprBgGame,Z_ORDER_BG_GAME);
		pSprBgGame->setColor(ccc3(255,255,255));
	}

	// create
	for(xx=0;xx<TABLERO_LX;xx++)
	for(yy=0;yy<TABLERO_LY;yy++)
	{
		// index
		idx		= xx + (yy * TABLERO_LX);
		createFichaSpr( idx , 0 , 0 , 0);
	}
	// create marks
	for(o=0;o<TABLERO_LEN;o++)
	{
		if(pSprTableroMark[o] == NULL)
		{
			pSprTableroMark[o]		= new CCSprite;
			pSprTableroMark[o]->initWithTexture( pTex[IDX_TABLEROMARK] );
			pSprTableroMark[o]->setPosition(ccp(0,0));
			pSprTableroMark[o]->setVisible(false);
			addChild( pSprTableroMark[o] , Z_ORDER_TABLEROMARK );
		}
	}

}
//---------------------------------------------------------------------------------------------------------------------------
// menu close callback
//---------------------------------------------------------------------------------------------------------------------------
void SceneGame::menuCloseCallback(CCObject* pSender)
{
	CCScene *pScene = Inicio::scene();	
	CCDirector::sharedDirector()->replaceScene(pScene);	    
}
//---------------------------------------------------------------------------------------------------------------------------
// menu new map callback
//---------------------------------------------------------------------------------------------------------------------------
void SceneGame::menuNewMapCallback(CCObject* pSender)
{
	CCMenu* pMenu = (CCMenu*) getChildByTag(10);
	pMenu->setTouchEnabled(false);
	pMenu->setEnabled(false);
	pMenu->setVisible(false);

	// Fichas en tablero
	createTablero();
	// Sprites de fichas
	createTableroSpr();
	//pMenu->setTouchEnabled(true);
	
	
	pMenu->setTouchEnabled(true);
	pMenu->setEnabled(true);
	pMenu->setVisible(true);
}
//-------------------------------------------------------------------------------------------------------------------------
// azar
//-------------------------------------------------------------------------------------------------------------------------
int SceneGame::azar( int low , int high )
{
	return low + (rand() % (high - low));
}
//-------------------------------------------------------------------------------------------------------------------------
// init touches
//-------------------------------------------------------------------------------------------------------------------------
void SceneGame::initTouches()
{
	// cocos2d touches
	setTouchEnabled(true);
	// vars
	touchId			= OFF;
	flagTouchMoved	= false;
	flagTouchCalc	= true;
	touchMoved		= ccp(0,0);
	touchMov		= ccp(0,0);
	touchTMoved		= ccp(0,0);
}
//-------------------------------------------------------------------------------------------------------------------------
// Touches Began
//-------------------------------------------------------------------------------------------------------------------------
void SceneGame::ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent)
{
	CCPoint			p;
	CCSetIterator	it;
	CCTouch*		touch;
	int				id;
    for (it=pTouches->begin(); it!=pTouches->end(); it++)
    {
		// get touch info
        touch			= (CCTouch*)(*it);
		p				= convertTouchToNodeSpace(touch);
		id				= touch->getID();
		// basic touch data
		if(touchId == OFF)
		{
			touchPos0		= p;
			touchPosF		= p;
			touchPosL		= p;
			touchId			= id;
			touchMoved		= ccp(0,0);
			touchMov		= ccp(0,0);
			flagTouchMoved	= false;
			CCLog("ccTouchesBegan : touchId=%i x=%.1f y=%.1f",touchId,touchPos0.x,touchPos0.y);
			// boxmarks
			resetTableroMark();
		}
	}
}
//-------------------------------------------------------------------------------------------------------------------------
// Touches Moved
//-------------------------------------------------------------------------------------------------------------------------
void SceneGame::ccTouchesMoved(CCSet *pTouches, CCEvent *pEvent)
{
	int xx,yy,idx;

	CCPoint			p;
	CCSetIterator	it;
	CCTouch*		touch;
	int				id;
    for (it=pTouches->begin(); it!=pTouches->end(); it++)
    {
		// get touch info
        touch			= (CCTouch*)(*it);
		p				= convertTouchToNodeSpace(touch);
		id				= touch->getID();
		// basic touch data
		if(touchId == id)
		{
			touchPosL		= touchPosF;
			touchPosF		= p;
			// movimiento en este frame del touch
			touchMov.x		= touchPosL.x - touchPosF.x;		
			touchMov.y		= touchPosL.y - touchPosF.y;
			// acumulacion de movimiento desde el inicio del touch
			touchMoved.x	+= touchMov.x;
			touchMoved.y	+= touchMov.y;
			flagTouchMoved	= true;
			flagTouchCalc	= false;

			// marca ficha con touch
			for(xx=0;xx<TABLERO_LX;xx++)
			for(yy=0;yy<TABLERO_LY;yy++)
			{
				idx		= getTableroOfs(xx,yy);
				if(pSprForma[idx] != NULL)
				if(pSprForma[idx]->boundingBox().containsPoint( p ) )
					setTableroMark( xx , yy );
			}
		}
	}
}
//-------------------------------------------------------------------------------------------------------------------------
// Touches Ended
//-------------------------------------------------------------------------------------------------------------------------
void SceneGame::ccTouchesEnded(CCSet *pTouches, CCEvent *pEvent)
{
	float			moved;
	int				xx,yy,idx;

	CCPoint			p;
	CCSetIterator	it;
	CCTouch*		touch;
	int				id;
    for (it=pTouches->begin(); it!=pTouches->end(); it++)
    {
		// get touch info
        touch			= (CCTouch*)(*it);
		p				= convertTouchToNodeSpace(touch);
		id				= touch->getID();

		// pixel movidos suma de componentes x e y (no es distancia real)
		// si el movimiento es grande , no hace fin de touch para seleccionar
		moved			= fabs(touchTMoved.x) + fabs(touchTMoved.y);
		touchTMoved		= ccp(0,0);

		// Finaliza los datos del touch ,dejandolo listo para el proximo
		if(id == touchId)
		{
			touchPosL		= touchPosF;
			touchPosF		= p;
			touchMov.x		= touchPosL.x - touchPosF.x;
			touchMov.y		= touchPosL.y - touchPosF.y;
			touchMoved.x	+= touchMov.x;
			touchMoved.y	+= touchMov.y;
			CCLog("ccTouchesEnded : touchId=%i x=%.1f y=%.1f",touchId,touchPosF.x,touchPosF.y);
			flagTouchMoved	= true;
			flagTouchCalc	= false;
			touchId			= OFF;

			// marca ficha con touch
			for(xx=0;xx<TABLERO_LX;xx++)
			for(yy=0;yy<TABLERO_LY;yy++)
			{
				idx		= getTableroOfs(xx,yy);
				if(pSprForma[idx] != NULL)
				if(pSprForma[idx]->boundingBox().containsPoint( p ) )
					setTableroMark( xx , yy );
			}

			// check marked
			checkMarked();
		}
	}
}
//-------------------------------------------------------------------------------------------------------------------------
// init tablero
//-------------------------------------------------------------------------------------------------------------------------
void SceneGame::initTablero()
{
	int o;
	// Tablero
	for(o=0;o<TABLERO_LEN;o++)
	{
		pSprNumero[o]			= NULL;
		pSprForma[o]			= NULL;
		pSprTableroMark[o]		= NULL;
	}
	// Bg
	pSprBgGame				= NULL;
	pSprBg					= NULL;
	//flags
	flagAcomodarTablero		= false;
}
//-------------------------------------------------------------------------------------------------------------------------
// reset box marks
//-------------------------------------------------------------------------------------------------------------------------
void SceneGame::resetTableroMark()
{
	int idx;
	markCount	= 0;
	for(idx=0;idx<TABLERO_LEN;idx++)
	{
		// marca de ficha elegida
		ficha[idx].flagMark		= false;
		// sprite asociado
		pSprTableroMark[idx]->setVisible(false);
		pSprTableroMark[idx]->setPosition(ccp(0,0));
	}
	CCLog("resetTableroMark()");
}
//-------------------------------------------------------------------------------------------------------------------------
// reset box marks
//-------------------------------------------------------------------------------------------------------------------------
void SceneGame::setTableroMark(int xx,int yy)
{
	int					idx;
	int					i;
	CCActionInterval*	action[8];
	CCActionInterval*	seq[8];
	// init
	for(i=0;i<8;i++)
	{
		action[i]	= NULL;
		seq[i]		= NULL;
	}

	idx					= getTableroOfs(xx,yy);
	// si ya esta activa retorna
	if(ficha[idx].flagMark == true)
		return;
	// agrega mark
	markCount++;
	pSprTableroMark[idx]->setVisible(true);
	pSprTableroMark[idx]->setPosition(ccp(TABLERO_OX+xx*FICHA_LX,TABLERO_OY+yy*FICHA_LY));
	pSprTableroMark[idx]->stopAllActions();
	pSprTableroMark[idx]->setScale(0.20f);
	pSprTableroMark[idx]->setRotation(0.0f);
	// acciones
	action[0]	= CCScaleTo::create( 0.35f , 1.75f );
	action[1]	= CCScaleTo::create( 0.25f , 1.00f );
	seq[0]		= (CCActionInterval*)(CCSequence::create(action[0],action[1],NULL) );
	pSprTableroMark[idx]->runAction(seq[0]);
	//
	action[2]	= CCRotateBy::create( 1.00f , 720.0f );
	pSprTableroMark[idx]->runAction(action[2]);
	// Ficha hace accion
	pSprForma[idx]->stopAllActions();
	pSprForma[idx]->setScale(1.0f);
	action[3]	= CCScaleTo::create( 0.20f , 1.50f );
	action[4]	= CCScaleTo::create( 0.20f , 1.00f );
	seq[1]		= (CCActionInterval*)(CCSequence::create(action[3],action[4],NULL) );
	pSprForma[idx]->runAction(seq[1]);
	// Ficha hace accion
	pSprNumero[idx]->stopAllActions();
	pSprNumero[idx]->setScale(1.0f);
	action[5]	= CCScaleTo::create( 0.20f , 1.50f );
	action[6]	= CCScaleTo::create( 0.20f , 1.00f );
	seq[2]		= (CCActionInterval*)(CCSequence::create(action[5],action[6],NULL) );
	pSprNumero[idx]->runAction(seq[2]);

	/*
	CCActionInterval*	rot			= CCRotateBy::create(0.75f,360.0f);
	CCRepeatForever*	repeat		= CCRepeatForever::create( rot );
	//
	CCActionInterval* scale1		= CCScaleBy::create(0.5f,1.40f);
	CCActionInterval* scale2		= scale1->reverse();
	CCActionInterval* seq			= (CCActionInterval*)(CCSequence::create(scale1,scale2,NULL) );
	CCRepeatForever* action			= CCRepeatForever::create(seq);
	spr->runAction(action);
	*/

	ficha[idx].flagMark		= true;
	CCLog("setTableroMark(%i,%i) [ofs=%i]",xx,yy,idx);
}
//-------------------------------------------------------------------------------------------------------------------------
// get tablero ofs
//-------------------------------------------------------------------------------------------------------------------------
int SceneGame::getTableroOfs(int xx,int yy)
{
	return xx + (yy * TABLERO_LX);
}
//-------------------------------------------------------------------------------------------------------------------------
// get tablero x
//-------------------------------------------------------------------------------------------------------------------------
int SceneGame::getTableroX(int ofs)
{
	return (ofs % TABLERO_LX);
}
//-------------------------------------------------------------------------------------------------------------------------
// get tablero y
//-------------------------------------------------------------------------------------------------------------------------
int SceneGame::getTableroY(int ofs)
{
	return (ofs / TABLERO_LX);
}
//-------------------------------------------------------------------------------------------------------------------------
// check Marked
//-------------------------------------------------------------------------------------------------------------------------
void SceneGame::checkMarked()
{
	int		xx,yy,ofs;
	int		sumaRes,sumaAct;
	int		chkForma;
	int		chkColor;
	bool	flagBreaked;

	// suma resultado 10 , suma actual 0
	sumaRes		= 10;
	sumaAct		= 0;
	// forma empieza en OFF
	chkForma	= OFF;
	chkColor	= OFF;
	// flag si las fichas rompieron
	flagBreaked	= false;

	// create
	for(xx=0;xx<TABLERO_LX;xx++)
	for(yy=0;yy<TABLERO_LY;yy++)
	{
		// offset
		ofs		= getTableroOfs(xx,yy);
		// check suma
		if(ficha[ofs].flagMark == true)
		{
			// suma
			sumaAct	+= (ficha[ofs].numero+1);
			// forma
			if(chkForma != IMPOSIBLE)
			{
				if(chkForma == OFF)
					chkForma	= ficha[ofs].forma;
				else if(chkForma != ficha[ofs].forma)
					chkForma	= IMPOSIBLE;
			}
			// color
			if(chkColor != IMPOSIBLE)
			{
				if(chkColor == OFF)
					chkColor	= ficha[ofs].color;
				else if(chkColor != ficha[ofs].color)
					chkColor	= IMPOSIBLE;
			}
		}
	}

	//
	// revision #1 : suma los valores de las fichas
	//
	if((sumaAct % 10) == 0)
	{
		CCLog("Bingo #1");
		for(xx=0;xx<TABLERO_LX;xx++)
		for(yy=0;yy<TABLERO_LY;yy++)
		{
			// offset de la ficha
			ofs		= getTableroOfs(xx,yy);
			// rompe ficha
			if(ficha[ofs].flagMark == true)
			if(ficha[ofs].flagActive == true)
			{
				// flag
				flagBreaked		= true;
				// rompe ficha
				romperFicha( ofs );
				// fx explo
				fxExplo( pSprForma[ofs]->getPositionX()    , pSprForma[ofs]->getPositionY() );
			}
		}
		// reset marks
		resetTableroMark();
	}
	/*
	//
	// revision #2 : las fichas tienen la misma forma ?
	//
	if(flagBreaked == false)
	{
		if((chkForma != IMPOSIBLE)&&(chkForma != OFF))
		if(markCount >= 3)
		{
			CCLog("Bingo #2");
			for(xx=0;xx<TABLERO_LX;xx++)
			for(yy=0;yy<TABLERO_LY;yy++)
			{
				// offset de la ficha
				ofs		= getTableroOfs(xx,yy);
				// rompe ficha
				if(ficha[ofs].flagMark == true)
				if(ficha[ofs].flagActive == true)
				{
					// flag
					flagBreaked		= true;
					// rompe ficha
					romperFicha( ofs );
					// fx explo
					fxExplo( pSprForma[ofs]->getPositionX()    , pSprForma[ofs]->getPositionY() );
				}

			}
			// reset marks
			resetTableroMark();
		}
	}

	//
	// revision #3 : las fichas tienen el mismo color ?
	//
	if(flagBreaked == false)
	{
		if((chkColor != IMPOSIBLE)&&(chkColor != OFF))
		if(markCount >= 3)
		{
			CCLog("Bingo #3");
			for(xx=0;xx<TABLERO_LX;xx++)
			for(yy=0;yy<TABLERO_LY;yy++)
			{
				// offset de la ficha
				ofs		= getTableroOfs(xx,yy);
				// rompe ficha
				if(ficha[ofs].flagMark == true)
				if(ficha[ofs].flagActive == true)
				{
					// flag
					flagBreaked		= true;
					// rompe ficha
					romperFicha( ofs );
					// fx explo
					fxExplo( pSprForma[ofs]->getPositionX()    , pSprForma[ofs]->getPositionY() );
				}

			}
			// reset marks
			resetTableroMark();
		}
	}
		*/
}
//-------------------------------------------------------------------------------------------------------------------------
// copiar ficha
//-------------------------------------------------------------------------------------------------------------------------
void SceneGame::copiarFicha(int ofs0,int ofs1)
{
	FICHA f0,f1;
	// guarda valores
	memcpy( &f0 , &ficha[ofs0] , sizeof(FICHA) );
	memcpy( &f1 , &ficha[ofs1] , sizeof(FICHA) );
	// libera sprites asociados , para luego crearlos de nuevo
	removeChild( pSprForma[ofs0] , true );
	pSprForma[ofs0]->release();
	pSprForma[ofs0]	= NULL;
	removeChild( pSprForma[ofs1] , true );
	pSprForma[ofs1]->release();
	pSprForma[ofs1]	= NULL;
	removeChild( pSprNumero[ofs0] , true );
	pSprNumero[ofs0]->release();
	pSprNumero[ofs0]	= NULL;
	removeChild( pSprNumero[ofs1] , true );
	pSprNumero[ofs1]->release();
	pSprNumero[ofs1]	= NULL;
	// copia ficha data
	memcpy( &ficha[ofs1] , &f0 , sizeof(FICHA) );
	memcpy( &ficha[ofs0] , &f1 , sizeof(FICHA) );
	// crea sprites
	createFichaSpr( ofs0 , 0 , 0 , 0 );
	createFichaSpr( ofs1 , 0 , 0 , 0 );
	// Log
	CCLog("copiar Ficha %i a %i",ofs0,ofs1);
}
//-------------------------------------------------------------------------------------------------------------------------
// mover ficha
//-------------------------------------------------------------------------------------------------------------------------
void SceneGame::moverFicha(int ofs0,int ofs1)
{
	FICHA	f0,f1;
	CCPoint	p0,p1;

	// guarda valores
	memcpy( &f0 , &ficha[ofs0] , sizeof(FICHA) );
	memcpy( &f1 , &ficha[ofs1] , sizeof(FICHA) );

	// libera sprites asociados , para luego crearlos de nuevo
	if(pSprForma[ofs0] != NULL)
	{
		removeChild( pSprForma[ofs0] , true );
		pSprForma[ofs0]->release();
		pSprForma[ofs0]	= NULL;
	}
	if(pSprForma[ofs1] != NULL)
	{
		removeChild( pSprForma[ofs1] , true );
		pSprForma[ofs1]->release();
		pSprForma[ofs1]	= NULL;
	}
	if(pSprNumero[ofs0] != NULL)
	{
		removeChild( pSprNumero[ofs0] , true );
		pSprNumero[ofs0]->release();
		pSprNumero[ofs0]	= NULL;
	}
	if(pSprNumero[ofs1] != NULL)
	{
		removeChild( pSprNumero[ofs1] , true );
		pSprNumero[ofs1]->release();
		pSprNumero[ofs1]	= NULL;
	}

	// mueve
	ficha[ofs1].clear();
	memcpy( &ficha[ofs0] , &f1 , sizeof(FICHA) );
	ficha[ofs0].x		= f0.x;
	ficha[ofs0].y		= f0.y;
	ficha[ofs0].ofs		= f0.ofs;
	ficha[ofs0].posx	= f0.posx;
	ficha[ofs0].posy	= f0.posy;
	ficha[ofs1].x		= f1.x;
	ficha[ofs1].y		= f1.y;
	ficha[ofs1].ofs		= f1.ofs;
	ficha[ofs1].posx	= f1.posx;
	ficha[ofs1].posy	= f1.posy;


	// crea sprites
	if(ficha[ofs0].flagActive == true)
	{
		// a la ficha la hace caer
		CCPoint p1;
		CCPoint p2;
		p1 = ccp(f1.posx,f1.posy);
		p2 = ccp(f0.posx,f0.posy);
		createFichaSpr( ofs0 , CREATE_MODE_FALL , &p1 , &p2 );
		//createFichaSpr( ofs0 , 0 , 0 , 0 );
	}

	// Log
	CCLog("mover Ficha %i a %i",ofs0,ofs1);
}
//-------------------------------------------------------------------------------------------------------------------------
//
//-------------------------------------------------------------------------------------------------------------------------
void SceneGame::desactivarFicha(int ofs)
{
	ficha[ofs].flagActive	= false;
}
//-------------------------------------------------------------------------------------------------------------------------
// romper ficha
//-------------------------------------------------------------------------------------------------------------------------
void SceneGame::romperFicha(int ofs)
{
	ficha[ofs].flagBreak	= true;
}
//-------------------------------------------------------------------------------------------------------------------------
// init explo
//-------------------------------------------------------------------------------------------------------------------------
void SceneGame::initFxExplo()
{
	int i;
	pTexFxExplo		= NULL;
	pTexFxExplo		= CCTextureCache::sharedTextureCache()->addImage( "flame.png" );	
	for(i=0;i<MAX_FX_EXPLO;i++)
	{
		pFxExplo[i] = CCParticleSun::create();
		pFxExplo[i]->setVisible(false);
		addChild( pFxExplo[i],  Z_ORDER_FX_EXPLO );
	}
	cont_fx_explo	= 0;
}
//-------------------------------------------------------------------------------------------------------------------------
// explo
//-------------------------------------------------------------------------------------------------------------------------
void SceneGame::fxExplo(float xx,float yy)
{
	pFxExplo[cont_fx_explo]->resetSystem();
	pFxExplo[cont_fx_explo]->setDuration(0.25f);
	pFxExplo[cont_fx_explo]->setTexture(pTexFxExplo);
	pFxExplo[cont_fx_explo]->setPosition(xx,yy);
	pFxExplo[cont_fx_explo]->setLife(0.25f);
	pFxExplo[cont_fx_explo]->setStartSize(150.0f);
	pFxExplo[cont_fx_explo]->setVisible(true);
	pFxExplo[cont_fx_explo]->setPosVar(ccp(75,75));
	pFxExplo[cont_fx_explo]->setEmissionRate(95);
	cont_fx_explo++;
	if(cont_fx_explo >= MAX_FX_EXPLO)
		cont_fx_explo = 0;
}
//-------------------------------------------------------------------------------------------------------------------------
// update Fx Llama
//-------------------------------------------------------------------------------------------------------------------------
void SceneGame::updateFxExplo(float dt)
{
	/*
	CCPoint	p;
	int		o;
	for(o=0;o<MAX_FX_EXPLO;o++)
	{
		if(pFxExplo[o]->isVisible() == true)
		{
			pFxExplo[o]->setPositionType( kCCPositionTypeGrouped );
			p		= pFxExplo[o]->getPosition();
			p.x		-=	movBgX;
			p.y		-=	movBgY;
			pFxExplo[o]->setPosition( p );
		}
	}
	*/
}
//-------------------------------------------------------------------------------------------------------------------------
// update
//-------------------------------------------------------------------------------------------------------------------------
void SceneGame::update(float dt)
{
	int		xx,yy,yy2,ofs,ofs2;
	FICHA	tmpFicha;

	for(xx=0;xx<TABLERO_LX;xx++)
	for(yy=0;yy<TABLERO_LY;yy++)
	{
		ofs		= getTableroOfs(xx,yy);
		//ofs		= ficha[ofs].ofs;
		// Hay ficha rota ?
		if(ficha[ofs].flagBreak == true)
		if(pSprNumero[ofs]->numberOfRunningActions() == 0)
		{
			// clear ficha
			ficha[ofs].clear();
			// copia toda la columna hacia abajo
			for(yy2=yy;yy2<TABLERO_LY-1;yy2++)
			{
				// offset de la ficha de arriba
				ofs		= getTableroOfs(xx,yy2);
				ofs2	= getTableroOfs(xx,yy2+1);
				// copia ficha de arriba con la de abajo
				moverFicha( ofs , ofs2 );
			}
		}
	}
}
