//---------------------------------------------------------------------------------------------------------------------------
#ifndef __FICHA_H__
#define __FICHA_H__
//---------------------------------------------------------------------------------------------------------------------------
#define IDX_NUMERO_1		0
#define IDX_NUMERO_2		1
#define IDX_NUMERO_3		2
#define IDX_NUMERO_4		3
#define IDX_NUMERO_5		4
#define IDX_NUMERO_6		5
#define IDX_NUMERO_7		6
#define IDX_NUMERO_8		7
#define IDX_NUMERO_9		8
#define IDX_FORMA_BOX		9
#define IDX_FORMA_CIRCLE	10
#define IDX_FORMA_STAR		11
#define IDX_COLOR_ROJO		12
#define IDX_COLOR_VERDE		13
#define IDX_COLOR_AZUL		14

#define TABLERO_LX			7
#define TABLERO_LY			7
#define TABLERO_LEN			TABLERO_LX*TABLERO_LY

#define Z_ORDER_FORMA		50
#define Z_ORDER_NUMERO		100
//---------------------------------------------------------------------------------------------------------------------------
class FICHA
{
public:
				FICHA();
				~FICHA();
	void		set(int n,int f,int c,int x,int y,int e);
	int			numero;
	int			forma;
	int			color;
	int			x,y;
	int			estado;
};
//---------------------------------------------------------------------------------------------------------------------------
#endif
//---------------------------------------------------------------------------------------------------------------------------
