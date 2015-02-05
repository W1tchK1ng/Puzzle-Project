//---------------------------------------------------------------------------------------------------------------------------
#ifndef __FICHA_H__
#define __FICHA_H__
//---------------------------------------------------------------------------------------------------------------------------
#include "_constantes.h"
//---------------------------------------------------------------------------------------------------------------------------
class FICHA
{
public:
				FICHA();
				~FICHA();

	void		set(int n,int f,int c);			// ficha set
	void		clear();						// ficha clear
	
	int			ofs;							// offset en el tablero
	int			x,y;							// posicion en el tablero
	float		posx,posy;						// posicion en pantalla en la que deberia estar

	int			numero;							// numero de la ficha
	int			forma;							// forma de la ficha
	int			color;							// color de la ficha

	bool		flagBreak;						// si el jugador rompio la ficha haciendo combinacion
	bool		flagMark;						// Si esta marcado por un touch
	bool		flagActive;						// Si esta siendo usado

	bool		flagActionFall;					// accion caer
	bool		flagActionEscape;				// accion Escapar
};
//---------------------------------------------------------------------------------------------------------------------------
#endif
//---------------------------------------------------------------------------------------------------------------------------
