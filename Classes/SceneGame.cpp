//---------------------------------------------------------------------------------------------------------------------------
#include "SceneGame.h"
//---------------------------------------------------------------------------------------------------------------------------
using namespace cocos2d;
//---------------------------------------------------------------------------------------------------------------------------
//
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
//
//---------------------------------------------------------------------------------------------------------------------------
bool SceneGame::init()
{
	int	o;

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
	pTex[IDX_NUMERO_8]				= CCTextureCache::sharedTextureCache()->addImage( "8.png" );
	pTex[IDX_NUMERO_9]				= CCTextureCache::sharedTextureCache()->addImage( "9.png" );
	pTex[IDX_FORMA_BOX]				= CCTextureCache::sharedTextureCache()->addImage( "box.png" );
	pTex[IDX_FORMA_CIRCLE]			= CCTextureCache::sharedTextureCache()->addImage( "circle.png" );
	pTex[IDX_FORMA_STAR]			= CCTextureCache::sharedTextureCache()->addImage( "star.png" );
	pTex[IDX_FORMA_DONUT]			= CCTextureCache::sharedTextureCache()->addImage( "donut.png" );
	pTex[IDX_FORMA_HEXAGON]			= CCTextureCache::sharedTextureCache()->addImage( "hexagon.png" );
	pTex[IDX_FORMA_SPIRAL]			= CCTextureCache::sharedTextureCache()->addImage( "spiral.png" );
	pTex[IDX_TABLEROMARK]			= CCTextureCache::sharedTextureCache()->addImage( "boxmark.png" );

	pTex[IDX_BG_001]				= CCTextureCache::sharedTextureCache()->addImage( "bg001.png" );
	pTex[IDX_BG_GAME]				= CCTextureCache::sharedTextureCache()->addImage( "gamebg.png" );

	// inicializa los sprites
	initTablero();
	createTablero();
	createTableroSpr();
	resetTableroMark();

	// Create a "close" menu item with close icon, it's an auto release object.
	CCMenuItemImage *pCloseItem		= CCMenuItemImage::create( "CloseNormal.png","CloseSelected.png", this, menu_selector(SceneGame::menuCloseCallback)); 
	pCloseItem->setPosition(ccp( _LX - 20, 20));
	CCMenuItemImage *pNewMapItem	= CCMenuItemImage::create( "CloseNormal.png","CloseSelected.png", this, menu_selector(SceneGame::menuNewMapCallback)); 
	pNewMapItem->setPosition(ccp( _LX - 20, 60));
	CCMenu* pMenu = CCMenu::create(pCloseItem,pNewMapItem,NULL);
	pMenu->setPosition(CCPointZero);
	addChild(pMenu, 1);

	// Update
	schedule( schedule_selector( SceneGame::update ) , GAME_REFRESH );

	return true;
}
//---------------------------------------------------------------------------------------------------------------------------
// create tablero fichas
//---------------------------------------------------------------------------------------------------------------------------
void SceneGame::createTablero()
{
	int o;
	for(o=0;o<TABLERO_LEN;o++)
	{
		// datos basicos de la ficha
		ficha[o].set( 
			azar( IDX_NUMERO_1 , IDX_NUMERO_9+1 ) , 
			azar( IDX_FORMA_BOX,IDX_FORMA_SPIRAL+1)  , 
			azar( IDX_COLOR_ROJO,IDX_COLOR_NEGRO+1)
			);
		// ficha ofs en tablero
		ficha[o].ofs	= o;
	}
}
//---------------------------------------------------------------------------------------------------------------------------
//
//---------------------------------------------------------------------------------------------------------------------------
void SceneGame::createFichaSpr(int idx)
{
	int xx,yy;

	// filtros
	if(idx < 0)					{ CCLog("ERROR : SceneGame::createFichaSpr(%i) ofs menor que cero"); return; }
	if(idx >= TABLERO_LEN)		{ CCLog("ERROR : SceneGame::createFichaSpr(%i) ofs mayor que TABLERO_LEN"); return; }
	if(pSprNumero[idx] != NULL) { CCLog("ERROR : SceneGame::createFichaSpr(%i) pSprNumero no null"); return; }
	if(pSprForma[idx] != NULL)	{ CCLog("ERROR : SceneGame::createFichaSpr(%i) pSprForma no null"); return; }
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
	else if(ficha[idx].forma == IDX_FORMA_DONUT)	pSprForma[idx]->initWithTexture( pTex[IDX_FORMA_DONUT ] );
	else if(ficha[idx].forma == IDX_FORMA_HEXAGON)	pSprForma[idx]->initWithTexture( pTex[IDX_FORMA_HEXAGON ] );
	else if(ficha[idx].forma == IDX_FORMA_SPIRAL)	pSprForma[idx]->initWithTexture( pTex[IDX_FORMA_SPIRAL ] );
	// color
	if(ficha[idx].color == IDX_COLOR_ROJO)			pSprForma[idx]->setColor( ccc3(255,50,50) );
	else if(ficha[idx].color == IDX_COLOR_VERDE)	pSprForma[idx]->setColor( ccc3(50,255,50) );
	else if(ficha[idx].color == IDX_COLOR_AZUL)		pSprForma[idx]->setColor( ccc3(50,50,255) );
	else if(ficha[idx].color == IDX_COLOR_AMARILLO)	pSprForma[idx]->setColor( ccc3(255,255,50) );
	else if(ficha[idx].color == IDX_COLOR_MAGENTA)	pSprForma[idx]->setColor( ccc3(255,50,255) );
	else if(ficha[idx].color == IDX_COLOR_CYAN)		pSprForma[idx]->setColor( ccc3(50,255,255) );
	else if(ficha[idx].color == IDX_COLOR_BLANCO)	pSprForma[idx]->setColor( ccc3(255,255,255) );
	else if(ficha[idx].color == IDX_COLOR_NEGRO)	pSprForma[idx]->setColor( ccc3(90,90,90) );
	// sprite
	xx	= getTableroX( idx );
	yy	= getTableroY( idx );
	if(pSprForma[idx] != NULL)
	{
		pSprForma[idx]->setPosition(ccp(128+xx*128,128+yy*128));
		pSprForma[idx]->setVisible(true);
		addChild( pSprForma[idx] , Z_ORDER_FORMA );
	}
	if(pSprNumero[idx] != NULL)
	{
		pSprNumero[idx]->setPosition(ccp(128+xx*128,128+yy*128));
		pSprNumero[idx]->setVisible(true);
		addChild( pSprNumero[idx] , Z_ORDER_NUMERO );
	}
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
		pSprBg->setAnchorPoint(ccp(0.0f,0.0f));
		pSprBg->setVisible(true);
		pSprBg->setPosition(ccp(128-64,128-64));
		addChild(pSprBg,Z_ORDER_BG);
	}
	if(pSprBgGame == NULL)
	{
		pSprBgGame	= new CCSprite;
		pSprBgGame->initWithTexture( pTex[IDX_BG_GAME] );
		pSprBgGame->setVisible(true);
		pSprBgGame->setPosition(ccp(_HLX,_HLY));
		addChild(pSprBgGame,Z_ORDER_BG_GAME);
	}

	// create
	for(xx=0;xx<TABLERO_LX;xx++)
	for(yy=0;yy<TABLERO_LY;yy++)
	{
		// index
		idx		= xx + (yy * TABLERO_LX);
		createFichaSpr( idx );
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
    CCDirector::sharedDirector()->end();
}
//---------------------------------------------------------------------------------------------------------------------------
// menu new map callback
//---------------------------------------------------------------------------------------------------------------------------
void SceneGame::menuNewMapCallback(CCObject* pSender)
{
	// Fichas en tablero
	createTablero();
	// Sprites de fichas
	createTableroSpr();
}
//-------------------------------------------------------------------------------------------------------------------------
// azar
//-------------------------------------------------------------------------------------------------------------------------
int SceneGame::azar( int low , int high )
{
	return low + (rand() % (high - low));
}
//-------------------------------------------------------------------------------------------------------------------------
//
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
	int				o,i;
	float			flo,moved;
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

	for(idx=0;idx<TABLERO_LEN;idx++)
	{
		// marca de ficha elegida
		ficha[idx].flagMark		= false;
		// sprite asociado
		pSprTableroMark[idx]->setVisible(false);
		pSprTableroMark[idx]->setPosition(ccp(0,0));
	}
}
//-------------------------------------------------------------------------------------------------------------------------
// reset box marks
//-------------------------------------------------------------------------------------------------------------------------
void SceneGame::setTableroMark(int xx,int yy)
{
	int idx;

	idx	= getTableroOfs(xx,yy);

	if(ficha[idx].flagMark == true)
		return;

	pSprTableroMark[idx]->setVisible(true);
	pSprTableroMark[idx]->setPosition(ccp(128+xx*128,128+yy*128));
	ficha[idx].flagMark		= true;
	CCLog("BoxMark[%i]",idx);
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
	int xx,yy,ofs;
	int	sumaRes,sumaAct;

	// suma resultado 10 , suma actual 0
	sumaRes	= 10;
	sumaAct	= 0;

	// create
	for(xx=0;xx<TABLERO_LX;xx++)
	for(yy=0;yy<TABLERO_LY;yy++)
	{
		// offset
		ofs		= getTableroOfs(xx,yy);
		// check suma
		if(ficha[ofs].flagMark == true)
		{
			sumaAct	+= (ficha[ofs].numero+1);
		}
	}

	// check suma
	if(sumaAct == sumaRes)
	{
		CCLog("Bingo!");
		for(xx=0;xx<TABLERO_LX;xx++)
		for(yy=0;yy<TABLERO_LY;yy++)
		{
			ofs		= getTableroOfs(xx,yy);
			// rompe ficha
			if(ficha[ofs].flagMark == true)
				ficha[ofs].flagBreak = true;
		}
		// reset marks
		resetTableroMark();
	}
}
//-------------------------------------------------------------------------------------------------------------------------
//
//-------------------------------------------------------------------------------------------------------------------------
void SceneGame::copiarFicha(int ofs0,int ofs1)
{
	FICHA f0,f1;
	// guarda valores
	memcpy( &f0 , &ficha[ofs0] , sizeof(FICHA) );
	memcpy( &f1 , &ficha[ofs1] , sizeof(FICHA) );
	// libera sprites asociados , para luego crearlos de nuevo
	if(pSprForma[ofs0] != NULL)
	{
		pSprForma[ofs0]->release();
		pSprForma[ofs0]	= NULL;
	}
	if(pSprForma[ofs1] != NULL)
	{
		pSprForma[ofs1]->release();
		pSprForma[ofs1]	= NULL;
	}
	// copia ficha data
	memcpy( &ficha[ofs1] , &f0 , sizeof(FICHA) );
	memcpy( &ficha[ofs0] , &f1 , sizeof(FICHA) );
	// crea sprites
	createFichaSpr( ofs0 );
	createFichaSpr( ofs1 );
	// desactiva el destino
	ficha[ofs0].flagActive	= false;


	CCLog("Copiar Ficha %i a %i",ofs0,ofs1);
}
//-------------------------------------------------------------------------------------------------------------------------
// update
//-------------------------------------------------------------------------------------------------------------------------
void SceneGame::update(float dt)
{
	int		xx,yy,ofs,ofs2;
	FICHA	tmpFicha;

	for(xx=0;xx<TABLERO_LX;xx++)
	for(yy=0;yy<TABLERO_LY;yy++)
	{
		ofs		= getTableroOfs(xx,yy);

		// Hay ficha rota ?
		if(ficha[ofs].flagBreak == true)
		{
			// si es fila de bien arriba , solo la rompe
			if(yy == (TABLERO_LY-1)) 
			{
				ficha[ofs].flagActive	= false;
				ficha[ofs].flagBreak	= false;
				pSprNumero[ofs]->setVisible(false);
				pSprForma[ofs]->setVisible(false);
			}
			else
			{
				// si hay una ficha arriba
				ofs2	= getTableroOfs(xx,yy+1);
				// si la ficha de arriba esta ok , la hace caer
				if(ficha[ofs2].flagActive == true)
				{
					// la ficha de arriba cae , y la de abajo copia sus datos
					memcpy( &ficha[ofs] , &ficha[ofs2] , sizeof(FICHA) );
					ficha[ofs].flagActive	= true;
					ficha[ofs].flagBreak	= false;
					pSprNumero[ofs2]->setPosition(ccp(128+(128*xx),128+(128*yy)));
					pSprForma[ofs2]->setPosition(ccp(128+(128*xx),128+(128*yy)));
					// la ficha de arriba se rompe
					pSprNumero[ofs2]->setVisible(false);
					pSprForma[ofs2]->setVisible(false);
					ficha[ofs2].flagActive	= false;
					ficha[ofs2].flagBreak	= true;
				}
			}
		}
	}
}
