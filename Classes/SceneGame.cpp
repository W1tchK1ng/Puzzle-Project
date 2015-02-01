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
	pTex[IDX_BOXMARK]				= CCTextureCache::sharedTextureCache()->addImage( "boxmark.png" );

	// inicializa los sprites
	for(o=0;o<TABLERO_LEN;o++)
	{
		pSprNumero[o]	= NULL;
		pSprForma[o]	= NULL;
		pSprMark[o]		= NULL;
		ficha[o].estado	= false;
	}

	// Create a "close" menu item with close icon, it's an auto release object.
	CCMenuItemImage *pCloseItem		= CCMenuItemImage::create( "CloseNormal.png","CloseSelected.png", this, menu_selector(SceneGame::menuCloseCallback)); 
	pCloseItem->setPosition(ccp( _LX - 20, 20));
	CCMenuItemImage *pNewMapItem	= CCMenuItemImage::create( "CloseNormal.png","CloseSelected.png", this, menu_selector(SceneGame::menuNewMapCallback)); 
	pNewMapItem->setPosition(ccp( _LX - 20, 60));
	CCMenu* pMenu = CCMenu::create(pCloseItem,pNewMapItem,NULL);
	pMenu->setPosition(CCPointZero);
	addChild(pMenu, 1);

	return true;
}
//---------------------------------------------------------------------------------------------------------------------------
// create tablero fichas
//---------------------------------------------------------------------------------------------------------------------------
void SceneGame::createTableroFichas()
{
	int o;
	for(o=0;o<TABLERO_LEN;o++)
	{
		ficha[o].set( 
			azar( IDX_NUMERO_1 , IDX_NUMERO_9+1 ) , 
			azar( IDX_FORMA_BOX,IDX_FORMA_STAR+1)  , 
			azar( IDX_COLOR_ROJO,IDX_COLOR_AZUL+1) , 
			0 , 0 , true );
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
	// create
	for(xx=0;xx<TABLERO_LX;xx++)
	for(yy=0;yy<TABLERO_LY;yy++)
	{
		// index
		idx		= xx + (yy * TABLERO_LX);
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
		// color
		if(ficha[idx].color == IDX_COLOR_ROJO)			pSprForma[idx]->setColor( ccc3(255,0,0) );
		else if(ficha[idx].color == IDX_COLOR_VERDE)	pSprForma[idx]->setColor( ccc3(0,255,0) );
		else if(ficha[idx].color == IDX_COLOR_AZUL)		pSprForma[idx]->setColor( ccc3(0,0,255) );
		// position
		ficha[idx].x			= xx;
		ficha[idx].y			= yy;
		// sprite
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
	// create marks
	for(o=0;o<TABLERO_LEN;o++)
	{
		if(pSprMark[o] == NULL)
		{
			pSprMark[o]		= new CCSprite;
			pSprMark[o]->initWithTexture( pTex[IDX_BOXMARK] );
			pSprMark[o]->setPosition(ccp(0,0));
			pSprMark[o]->setVisible(false);
			addChild( pSprMark[o] , Z_ORDER_BOXMARK );
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
	createTableroFichas();
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
			resetBoxMarks();
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

			// calcula en que ficha del tablero termino el touch
			for(xx=0;xx<TABLERO_LX;xx++)
			for(yy=0;yy<TABLERO_LY;yy++)
			{
				// index
				idx		= xx + (yy * TABLERO_LX);
				if(pSprForma[idx] != NULL)
				if(pSprForma[idx]->boundingBox().containsPoint( p ) )
				{
					// boxmark
					setBoxMark( pSprForma[idx]->getPositionX() , pSprForma[idx]->getPositionY() );
					fichaBoxMark[ idx ] = true;
					break;
				}
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
			// calcula en que ficha del tablero termino el touch
			for(xx=0;xx<TABLERO_LX;xx++)
			for(yy=0;yy<TABLERO_LY;yy++)
			{
				// index
				idx		= xx + (yy * TABLERO_LX);
				if(pSprForma[idx] != NULL)
				if(pSprForma[idx]->boundingBox().containsPoint( p ) )
				{
					// boxmark
					setBoxMark( pSprForma[idx]->getPositionX() , pSprForma[idx]->getPositionY() );
					fichaBoxMark[ idx ] = true;
					break;
				}
			}
		}

	}
}
//-------------------------------------------------------------------------------------------------------------------------
// update
//-------------------------------------------------------------------------------------------------------------------------
void SceneGame::update(float dt)
{
	
}
//-------------------------------------------------------------------------------------------------------------------------
// reset box marks
//-------------------------------------------------------------------------------------------------------------------------
void SceneGame::resetBoxMarks()
{
	int idx;

	for(idx=0;idx<TABLERO_LEN;idx++)
	{
		// marca de ficha elegida
		fichaBoxMark[idx]	= false;
		// sprite asociado
		pSprMark[idx]->setVisible(false);
		pSprMark[idx]->setPosition(ccp(0,0));
	}
}
//-------------------------------------------------------------------------------------------------------------------------
// reset box marks
//-------------------------------------------------------------------------------------------------------------------------
void SceneGame::setBoxMark(float xx,float yy)
{
	int idx;
	for(idx=0;idx<TABLERO_LEN;idx++)
	{
		if( pSprMark[idx]->isVisible() == false)
		{
			// marca de ficha elegida
			fichaBoxMark[idx]	= true;
			// sprite asociado
			pSprMark[idx]->setPosition( ccp(xx,yy) );
			pSprMark[idx]->setVisible(true);
			return;
		}
	}
}