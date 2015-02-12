//---------------------------------------------------------------------------------------------------------------------------
#ifndef ___CONSTANTES_H__
#define ___CONSTANTES_H__
//---------------------------------------------------------------------------------------------------------------------------
#define	OFF					-1
#define IMPOSIBLE			-2
#define	MAX_TEXTURE			64
#define MAX_FICHA			256
#define GAME_REFRESH		1.0f/30.0f
#define MAX_FX_EXPLO		64
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

#define IDX_FORMA_BOX		20
#define IDX_FORMA_CIRCLE	21
#define IDX_FORMA_STAR		22
#define IDX_FORMA_HEXAGON	23
#define IDX_FORMA_SPIRAL	24
#define IDX_FORMA_DONUT		25

#define IDX_BG_GAME			30
#define IDX_BG_001			31

#define IDX_COLOR_ROJO		130
#define IDX_COLOR_VERDE		131
#define IDX_COLOR_AZUL		132
#define IDX_COLOR_AMARILLO	133
#define IDX_COLOR_MAGENTA	134
#define IDX_COLOR_CYAN		135
#define IDX_COLOR_BLANCO	136
#define IDX_COLOR_NEGRO		137

#define IDX_TABLEROMARK		40
//---------------------------------------------------------------------------------------------------------------------------
#define TABLERO_OX			128
#define TABLERO_OY			128
#define TABLERO_LX			5
#define TABLERO_LY			10
#define TABLERO_LEN			TABLERO_LX*TABLERO_LY
#define FICHA_LX			128
#define FICHA_LY			128
//---------------------------------------------------------------------------------------------------------------------------
#define Z_ORDER_FX_EXPLO	70
#define Z_ORDER_NUMERO		60
#define Z_ORDER_FORMA		50
#define Z_ORDER_TABLEROMARK	40
#define Z_ORDER_BG			0
#define Z_ORDER_BG_GAME		-10
//---------------------------------------------------------------------------------------------------------------------------
#define CREATE_MODE_NORMAL	0
#define CREATE_MODE_FALL	1
#define CREATE_MODE_ESCAPE	2
//---------------------------------------------------------------------------------------------------------------------------
#endif
//---------------------------------------------------------------------------------------------------------------------------
