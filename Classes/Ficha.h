//---------------------------------------------------------------------------------------------------------------------------
#ifndef __FICHA_H__
#define __FICHA_H__
//---------------------------------------------------------------------------------------------------------------------------
#include "_constantes.h"
#include "cocos2d.h"
//---------------------------------------------------------------------------------------------------------------------------
using namespace cocos2d;
//---------------------------------------------------------------------------------------------------------------------------
class FICHA
{
public:
					FICHA();
					~FICHA();
	void			init();							// init
	void			release();						// release

	CCNode*			pScene;							// guarda scene que crea el sprite para luego poder liberarlo
	//CCSprite*		pSprNumero;						// 
	CCSprite*		pSprForma;						// 
	char			text[64];
	CCLabelBMFont*	pText;					

	int				numero;							// numero de la ficha
	int				forma;							// forma de la ficha
	int				color;							// color de la ficha
	int				mapX,mapY;						// posicion en el tablero
	float			scrX,scrY;						// posicion en pantalla en la que deberia estar
	bool			flagRompiendo;					// esta rompiendose
	bool			flagCayendo;					// esta cayendo
	bool			flagEscapando;					// esta escapando
	bool			flagMarcada;					// Si esta marcado por un touch
	bool			flagActive;						// Si esta siendo usado
	bool			flagRota;						// esta rota

	void			activar();
	void			desactivar();
	void			setMapPos(int _x,int _y);
	void			setScrPos(float _x,float _y);
	void			setForma(int _n);
	void			setNumero(int _n);
	void			setColor(int _n);
	void			setText(char* txt);
	void			accionRomper();
	void			accionCaer();
	void			accionEscapar();
};
//---------------------------------------------------------------------------------------------------------------------------
#endif
//---------------------------------------------------------------------------------------------------------------------------
