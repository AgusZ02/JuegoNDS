/*---------------------------------------------------------------------------------
Código desarrollado basado en el ejemplo "Simple sprite demo" de dovoto y en otro de Jaeden Amero.
---------------------------------------------------------------------------------*/

#include <nds.h> 		
#include <stdio.h>		
#include <stdlib.h>		
#include <unistd.h>		

#include "sprites.h"
#include "definiciones.h"

u16* gfxrombo;
u16* gfxromboGrande;

u16* gfxArriba;
u16* gfxDerecha;
u16* gfxIzquierda;
u16* gfxAbajo;
u16* gfxProyHorizontal;
u16* gfxProyVertical;
u16* gfxVida;
/* Reservar memoria para cada sprite que se quiera mostrar en pantalla */
void memoriaReserva()
{
	/* Por cada sprite que se quiera incluir en la pantalla principal hay que hacer algo equivalente a lo que sigue */
	gfxrombo= oamAllocateGfx(&oamMain, SpriteSize_16x16, SpriteColorFormat_256Color);
	gfxromboGrande=oamAllocateGfx(&oamMain, SpriteSize_32x32, SpriteColorFormat_256Color);
	gfxArriba= oamAllocateGfx(&oamMain, SpriteSize_16x16, SpriteColorFormat_256Color);
	gfxDerecha= oamAllocateGfx(&oamMain, SpriteSize_16x16, SpriteColorFormat_256Color);
	gfxIzquierda= oamAllocateGfx(&oamMain, SpriteSize_16x16, SpriteColorFormat_256Color);
	gfxAbajo= oamAllocateGfx(&oamMain, SpriteSize_16x16, SpriteColorFormat_256Color);
	gfxProyHorizontal = oamAllocateGfx(&oamMain, SpriteSize_16x16, SpriteColorFormat_256Color);
	gfxProyVertical = oamAllocateGfx(&oamMain, SpriteSize_16x16, SpriteColorFormat_256Color);
	

}

/* A cada uno de los 256 valores que puede tomar un pixel en la PALETA PRINCIPAL
   se le puede asignar un color. El valor 0 es transparente. Los valores sin definir son negros. 
   MODIFICAR SEGÚN LOS COLORES QUE QUERAIS UTILIZAR EN VUESTROS SPRITES */
void EstablecerPaletaPrincipal() {

	SPRITE_PALETTE[1] = RGB15(31,0,0); // los píxeles con valor 1 serán de color rojo.
	SPRITE_PALETTE[2] = RGB15(0,31,0); // los píxeles con valor 2 serán verdes.
	SPRITE_PALETTE[3] = RGB15(255,255,255);
	SPRITE_PALETTE[4] = RGB15(0,0,31); // los píxeles con valor 4 serán azules.
}

/* definición de un sprite de 16x16 píxeles para dibujar un rombo */
/* Por la forma que tienen de trabajar los bancos de memoria, la imagen del sprite se divide en bloques de 8x8 píxeles. Los primeros 64 (8x8) píxeles que indicamos
aparecerán en el cuadrante superior izquierdo de la imagen del sprite, los siguientes 64 en el cuadrante superior derecho, los siguientes en el cuadrante inferior izquierdo y los
últimos en el cuadrante inferior derecho */

u8 rombo[256] = 
{
	0,0,0,0,0,0,2,2,
        0,0,0,0,0,2,2,2,	//	0,0,0,0,0,0,2,2, 2,2,0,0,0,0,0,0,
	0,0,0,0,2,2,2,2,
        0,0,0,2,2,2,2,2,	//	0,0,0,0,0,2,2,2, 2,2,2,0,0,0,0,0,
	0,0,2,2,2,2,2,2,
        0,2,2,2,2,2,2,2,	//	0,0,0,0,2,2,2,2, 2,2,2,2,0,0,0,0,
	2,2,2,2,2,2,2,2,
        2,2,2,2,2,2,2,2,	//	0,0,0,2,2,2,2,2, 2,2,2,2,2,0,0,0,
 
	2,2,0,0,0,0,0,0,
        2,2,2,0,0,0,0,0,	//	0,0,2,2,2,2,2,2, 2,2,2,2,2,2,0,0,
	2,2,2,2,0,0,0,0,
        2,2,2,2,2,0,0,0,	//	0,2,2,2,2,2,2,2, 2,2,2,2,2,2,2,0,
	2,2,2,2,2,2,0,0,
        2,2,2,2,2,2,2,0,	//	2,2,2,2,2,2,2,2, 2,2,2,2,2,2,2,2,
	2,2,2,2,2,2,2,2,
        2,2,2,2,2,2,2,2,	//	2,2,2,2,2,2,2,2, 2,2,2,2,2,2,2,2,

	1,1,1,1,1,1,1,1,
        1,1,1,1,1,1,1,1,	//	1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1,
	0,1,1,1,1,1,1,1,
        0,0,1,1,1,1,1,1,	//	1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1,
	0,0,0,1,1,1,1,1,
        0,0,0,0,1,1,1,1,	//	0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,0,
	0,0,0,0,0,1,1,1,
        0,0,0,0,0,0,1,1,	//	0,0,1,1,1,1,1,1, 1,1,1,1,1,1,0,0,

	1,1,1,1,1,1,1,1,
        1,1,1,1,1,1,1,1,	//	0,0,0,1,1,1,1,1, 1,1,1,1,1,0,0,0,
	1,1,1,1,1,1,1,0,
        1,1,1,1,1,1,0,0,	//	0,0,0,0,1,1,1,1, 1,1,1,1,0,0,0,0,
	1,1,1,1,1,0,0,0,
        1,1,1,1,0,0,0,0,	//	0,0,0,0,0,1,1,1, 1,1,1,0,0,0,0,0,
	1,1,1,0,0,0,0,0,
        1,1,0,0,0,0,0,0,	//	0,0,0,0,0,0,1,1, 1,1,0,0,0,0,0,0,
};

u8 romboGrande[1024] = 
{
	0,0,0,0,0,0,2,2,0,0,0,0,0,2,2,2,0,0,0,0,2,2,2,2,0,0,0,2,2,2,2,2,0,0,2,2,2,2,2,2,0,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,	

	3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,	

	3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,	
 
	2,2,0,0,0,0,0,0,2,2,2,0,0,0,0,0,2,2,2,2,0,0,0,0,2,2,2,2,2,0,0,0,2,2,2,2,2,2,0,0,2,2,2,2,2,2,2,0,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,	

	2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,

	0,0,0,0,0,0,1,1,0,0,0,0,0,1,1,1,0,0,0,0,1,1,1,1,0,0,0,1,1,1,1,1,0,0,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,	

	1,1,0,0,0,0,0,0,1,1,1,0,0,0,0,0,1,1,1,1,0,0,0,0,1,1,1,1,1,0,0,0,1,1,1,1,1,1,0,0,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,	

	2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,

	1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,

	2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,0,2,2,2,2,2,2,2,0,0,2,2,2,2,2,2,0,0,0,2,2,2,2,2,0,0,0,0,2,2,2,2,0,0,0,0,0,2,2,2,0,0,0,0,0,0,2,2,	

	2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,0,2,2,2,2,2,2,0,0,2,2,2,2,2,0,0,0,2,2,2,2,0,0,0,0,2,2,2,0,0,0,0,0,2,2,0,0,0,0,0,0,	

	1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,

	1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,0,0,1,1,1,1,1,1,0,0,0,1,1,1,1,1,0,0,0,0,1,1,1,1,0,0,0,0,0,1,1,1,0,0,0,0,0,0,1,1,	

	3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,	

	3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,	

	1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,0,0,1,1,1,1,1,0,0,0,1,1,1,1,0,0,0,0,1,1,1,0,0,0,0,0,1,1,0,0,0,0,0,0,	
};


u8 arriba[256] = 
{
3	,	3	,	3	,	3	,	3	,	3	,	3	,	3	,	3	,	3	,	3	,	3	,	3	,	3	,	3	,	3	,	 //	3	3	3	3	3	3	3	3	3	3	3	3	3	3	3	3
0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	3	,	3	,	0	,	0	,	 //	3	3	3	3	3	3	3	3	3	3	3	3	3	3	3	3
0	,	0	,	0	,	3	,	3	,	3	,	3	,	0	,	0	,	0	,	0	,	3	,	3	,	3	,	3	,	3	,	 //	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0
0	,	0	,	0	,	3	,	3	,	3	,	3	,	3	,	0	,	0	,	0	,	3	,	3	,	3	,	3	,	3	,	 //	0	0	0	0	3	3	0	0	0	0	3	3	0	0	0	0
3	,	3	,	3	,	3	,	3	,	3	,	3	,	3	,	3	,	3	,	3	,	3	,	3	,	3	,	3	,	3	,	 //	0	0	0	3	3	3	3	0	0	3	3	3	3	0	0	0
0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	3	,	3	,	0	,	0	,	0	,	0	,	 //	0	0	0	3	3	3	3	3	3	3	3	3	3	0	0	0
0	,	3	,	3	,	3	,	3	,	0	,	0	,	0	,	3	,	3	,	3	,	3	,	3	,	0	,	0	,	0	,	 //	0	0	0	3	3	3	3	3	3	3	3	3	3	0	0	0
3	,	3	,	3	,	3	,	3	,	0	,	0	,	0	,	3	,	3	,	3	,	3	,	3	,	0	,	0	,	0	,	 //	0	0	0	3	3	3	3	3	3	3	3	3	3	0	0	0
0	,	0	,	0	,	3	,	3	,	3	,	3	,	3	,	0	,	0	,	0	,	0	,	3	,	3	,	3	,	3	,	 //	0	0	0	3	3	3	3	3	3	3	3	3	3	0	0	0
0	,	0	,	0	,	0	,	0	,	3	,	3	,	3	,	0	,	0	,	0	,	0	,	0	,	0	,	3	,	3	,	 //	0	0	0	0	3	3	3	3	3	3	3	3	0	0	0	0
0	,	0	,	0	,	0	,	0	,	0	,	0	,	3	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	 //	0	0	0	0	0	3	3	3	3	3	3	0	0	0	0	0
0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	 //	0	0	0	0	0	0	3	3	3	3	0	0	0	0	0	0
3	,	3	,	3	,	3	,	3	,	0	,	0	,	0	,	3	,	3	,	3	,	3	,	0	,	0	,	0	,	0	,	 //	0	0	0	0	0	0	0	3	3	0	0	0	0	0	0	0
3	,	3	,	3	,	0	,	0	,	0	,	0	,	0	,	3	,	3	,	0	,	0	,	0	,	0	,	0	,	0	,	 //	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0
3	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	 //	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0
0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	 //	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0

};
u8 abajo[256]=
{
0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	 //	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0
0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	3	,	3	,	0	,	0	,	 //	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0
0	,	0	,	0	,	3	,	3	,	3	,	3	,	0	,	0	,	0	,	0	,	3	,	3	,	3	,	3	,	3	,	 //	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0
0	,	0	,	0	,	3	,	3	,	3	,	3	,	3	,	0	,	0	,	0	,	3	,	3	,	3	,	3	,	3	,	 //	0	0	0	0	3	3	0	0	0	0	3	3	0	0	0	0
0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	 //	0	0	0	3	3	3	3	0	0	3	3	3	3	0	0	0
0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	3	,	3	,	0	,	0	,	0	,	0	,	 //	0	0	0	3	3	3	3	3	3	3	3	3	3	0	0	0
0	,	3	,	3	,	3	,	3	,	0	,	0	,	0	,	3	,	3	,	3	,	3	,	3	,	0	,	0	,	0	,	 //	0	0	0	3	3	3	3	3	3	3	3	3	3	0	0	0
3	,	3	,	3	,	3	,	3	,	0	,	0	,	0	,	3	,	3	,	3	,	3	,	3	,	0	,	0	,	0	,	 //	0	0	0	3	3	3	3	3	3	3	3	3	3	0	0	0
0	,	0	,	0	,	3	,	3	,	3	,	3	,	3	,	0	,	0	,	0	,	0	,	3	,	3	,	3	,	3	,	 //	0	0	0	3	3	3	3	3	3	3	3	3	3	0	0	0
0	,	0	,	0	,	0	,	0	,	3	,	3	,	3	,	0	,	0	,	0	,	0	,	0	,	0	,	3	,	3	,	 //	0	0	0	0	3	3	3	3	3	3	3	3	0	0	0	0
0	,	0	,	0	,	0	,	0	,	0	,	0	,	3	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	 //	0	0	0	0	0	3	3	3	3	3	3	0	0	0	0	0
3	,	3	,	3	,	3	,	3	,	3	,	3	,	3	,	3	,	3	,	3	,	3	,	3	,	3	,	3	,	3	,	 //	0	0	0	0	0	0	3	3	3	3	0	0	0	0	0	0
3	,	3	,	3	,	3	,	3	,	0	,	0	,	0	,	3	,	3	,	3	,	3	,	0	,	0	,	0	,	0	,	 //	0	0	0	0	0	0	0	3	3	0	0	0	0	0	0	0
3	,	3	,	3	,	0	,	0	,	0	,	0	,	0	,	3	,	3	,	0	,	0	,	0	,	0	,	0	,	0	,	 //	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0
3	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	 //	3	3	3	3	3	3	3	3	3	3	3	3	3	3	3	3
3	,	3	,	3	,	3	,	3	,	3	,	3	,	3	,	3	,	3	,	3	,	3	,	3	,	3	,	3	,	3	,	 //	3	3	3	3	3	3	3	3	3	3	3	3	3	3	3	3

};
u8 derecha[256]=
{
0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	 //	0	0	0	0	0	0	0	0	0	0	0	0	0	0	3	3
0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	3	,	3	,	0	,	0	,	 //	0	0	0	0	0	0	0	0	0	0	0	0	0	0	3	3
0	,	0	,	0	,	3	,	3	,	3	,	3	,	0	,	0	,	0	,	0	,	3	,	3	,	3	,	3	,	3	,	 //	0	0	0	0	0	0	0	0	0	0	0	0	0	0	3	3
0	,	0	,	0	,	3	,	3	,	3	,	3	,	3	,	0	,	0	,	0	,	3	,	3	,	3	,	3	,	3	,	 //	0	0	0	0	3	3	0	0	0	0	3	3	0	0	3	3
0	,	0	,	0	,	0	,	0	,	0	,	3	,	3	,	0	,	0	,	0	,	0	,	0	,	0	,	3	,	3	,	 //	0	0	0	3	3	3	3	0	0	3	3	3	3	0	3	3
0	,	0	,	0	,	0	,	0	,	0	,	3	,	3	,	0	,	0	,	3	,	3	,	0	,	0	,	3	,	3	,	 //	0	0	0	3	3	3	3	3	3	3	3	3	3	0	3	3
0	,	3	,	3	,	3	,	3	,	0	,	3	,	3	,	3	,	3	,	3	,	3	,	3	,	0	,	3	,	3	,	 //	0	0	0	3	3	3	3	3	3	3	3	3	3	0	3	3
3	,	3	,	3	,	3	,	3	,	0	,	3	,	3	,	3	,	3	,	3	,	3	,	3	,	0	,	3	,	3	,	 //	0	0	0	3	3	3	3	3	3	3	3	3	3	0	3	3
0	,	0	,	0	,	3	,	3	,	3	,	3	,	3	,	0	,	0	,	0	,	0	,	3	,	3	,	3	,	3	,	 //	0	0	0	3	3	3	3	3	3	3	3	3	3	0	3	3
0	,	0	,	0	,	0	,	0	,	3	,	3	,	3	,	0	,	0	,	0	,	0	,	0	,	0	,	3	,	3	,	 //	0	0	0	0	3	3	3	3	3	3	3	3	0	0	3	3
0	,	0	,	0	,	0	,	0	,	0	,	0	,	3	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	 //	0	0	0	0	0	3	3	3	3	3	3	0	0	0	3	3
0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	 //	0	0	0	0	0	0	3	3	3	3	0	0	0	0	3	3
3	,	3	,	3	,	3	,	3	,	0	,	3	,	3	,	3	,	3	,	3	,	3	,	0	,	0	,	3	,	3	,	 //	0	0	0	0	0	0	0	3	3	0	0	0	0	0	3	3
3	,	3	,	3	,	0	,	0	,	0	,	3	,	3	,	3	,	3	,	0	,	0	,	0	,	0	,	3	,	3	,	 //	0	0	0	0	0	0	0	0	0	0	0	0	0	0	3	3
3	,	0	,	0	,	0	,	0	,	0	,	3	,	3	,	0	,	0	,	0	,	0	,	0	,	0	,	3	,	3	,	 //	0	0	0	0	0	0	0	0	0	0	0	0	0	0	3	3
0	,	0	,	0	,	0	,	0	,	0	,	3	,	3	,	0	,	0	,	0	,	0	,	0	,	0	,	3	,	3	,	 //	0	0	0	0	0	0	0	0	0	0	0	0	0	0	3	3

};
u8 izquierda[256]={
3	,	3	,	0	,	0	,	0	,	0	,	0	,	0	,	3	,	3	,	0	,	0	,	0	,	0	,	0	,	0	,	 //	3	3	0	0	0	0	0	0	0	0	0	0	0	0	0	0
3	,	3	,	0	,	0	,	0	,	0	,	0	,	0	,	3	,	3	,	0	,	0	,	3	,	3	,	0	,	0	,	 //	3	3	0	0	0	0	0	0	0	0	0	0	0	0	0	0
3	,	3	,	0	,	3	,	3	,	3	,	3	,	0	,	3	,	3	,	0	,	3	,	3	,	3	,	3	,	3	,	 //	3	3	0	0	0	0	0	0	0	0	0	0	0	0	0	0
3	,	3	,	0	,	3	,	3	,	3	,	3	,	3	,	3	,	3	,	0	,	3	,	3	,	3	,	3	,	3	,	 //	3	3	0	0	3	3	0	0	0	0	3	3	0	0	0	0
0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	 //	3	3	0	3	3	3	3	0	0	3	3	3	3	0	0	0
0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	3	,	3	,	0	,	0	,	0	,	0	,	 //	3	3	0	3	3	3	3	3	3	3	3	3	3	0	0	0
0	,	3	,	3	,	3	,	3	,	0	,	0	,	0	,	3	,	3	,	3	,	3	,	3	,	0	,	0	,	0	,	 //	3	3	0	3	3	3	3	3	3	3	3	3	3	0	0	0
3	,	3	,	3	,	3	,	3	,	0	,	0	,	0	,	3	,	3	,	3	,	3	,	3	,	0	,	0	,	0	,	 //	3	3	0	3	3	3	3	3	3	3	3	3	3	0	0	0
3	,	3	,	0	,	3	,	3	,	3	,	3	,	3	,	3	,	3	,	0	,	0	,	3	,	3	,	3	,	3	,	 //	3	3	0	3	3	3	3	3	3	3	3	3	3	0	0	0
3	,	3	,	0	,	0	,	0	,	3	,	3	,	3	,	3	,	3	,	0	,	0	,	0	,	0	,	3	,	3	,	 //	3	3	0	0	3	3	3	3	3	3	3	3	0	0	0	0
3	,	3	,	0	,	0	,	0	,	0	,	0	,	3	,	3	,	3	,	0	,	0	,	0	,	0	,	0	,	0	,	 //	3	3	0	0	0	3	3	3	3	3	3	0	0	0	0	0
3	,	3	,	0	,	0	,	0	,	0	,	0	,	0	,	3	,	3	,	0	,	0	,	0	,	0	,	0	,	0	,	 //	3	3	0	0	0	0	3	3	3	3	0	0	0	0	0	0
3	,	3	,	3	,	3	,	3	,	0	,	0	,	0	,	3	,	3	,	3	,	3	,	0	,	0	,	0	,	0	,	 //	3	3	0	0	0	0	0	3	3	0	0	0	0	0	0	0
3	,	3	,	3	,	0	,	0	,	0	,	0	,	0	,	3	,	3	,	0	,	0	,	0	,	0	,	0	,	0	,	 //	3	3	0	0	0	0	0	0	0	0	0	0	0	0	0	0
3	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	 //	3	3	0	0	0	0	0	0	0	0	0	0	0	0	0	0
0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	 //	3	3	0	0	0	0	0	0	0	0	0	0	0	0	0	0
};

u8 proyHorizontal[256] = {
0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	 //	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0
0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	 //	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0
0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	 //	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0
0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	1	,	1	,	1	,	0	,	1	,	1	,	1	,	 //	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0
0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	 //	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0
0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	 //	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0
0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	 //	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0
0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	1	,	0	,	1	,	1	,	1	,	0	,	1	,	 //	0	1	1	1	0	1	1	1	0	1	0	1	1	1	0	1
1	,	1	,	0	,	1	,	1	,	1	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	 //	1	1	0	1	1	1	0	0	1	1	1	1	1	0	1	0
0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	 //	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0
0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	 //	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0
0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	 //	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0
1	,	1	,	1	,	1	,	1	,	0	,	1	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	 //	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0
0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	 //	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0
0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	 //	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0
0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	 //	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0
};

u8 proyVertical[256]={
0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	1	,	 //	0	0	0	0	0	0	0	0	1	0	0	0	0	0	0	0
0	,	0	,	0	,	0	,	0	,	0	,	0	,	1	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	1	,	 //	0	0	0	0	0	0	0	1	0	0	0	0	0	0	0	0
0	,	0	,	0	,	0	,	0	,	0	,	0	,	1	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	 //	0	0	0	0	0	0	0	1	1	0	0	0	0	0	0	0
0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	 //	0	0	0	0	0	0	0	1	0	0	0	0	0	0	0	0
1	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	 //	0	0	0	0	0	0	0	1	1	0	0	0	0	0	0	0
1	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	 //	0	0	0	0	0	0	0	0	1	0	0	0	0	0	0	0
1	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	1	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	 //	0	0	0	0	0	0	0	0	1	0	0	0	0	0	0	0
1	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	1	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	 //	0	0	0	0	0	0	0	0	1	0	0	0	0	0	0	0
0	,	0	,	0	,	0	,	0	,	0	,	0	,	1	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	1	,	 //	0	0	0	0	0	0	0	1	1	0	0	0	0	0	0	0
0	,	0	,	0	,	0	,	0	,	0	,	0	,	1	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	 //	0	0	0	0	0	0	0	1	0	0	0	0	0	0	0	0
0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	1	,	 //	0	0	0	0	0	0	0	1	1	0	0	0	0	0	0	0
0	,	0	,	0	,	0	,	0	,	0	,	0	,	1	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	 //	0	0	0	0	0	0	0	0	1	0	0	0	0	0	0	0
1	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	 //	0	0	0	0	0	0	0	0	1	0	0	0	0	0	0	0
1	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	1	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	 //	0	0	0	0	0	0	0	1	1	0	0	0	0	0	0	0
1	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	1	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	 //	0	0	0	0	0	0	0	1	1	0	0	0	0	0	0	0
1	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	1	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	 //	0	0	0	0	0	0	0	0	1	0	0	0	0	0	0	0
};


/* Carga en memoria cada uno de los sprites que hemos dibujado */

void GuardarSpritesMemoria(){ 
	
int i;
	//sprite de 16*16
	for(i = 0; i < 16 * 16 / 2; i++) 
	{	
		gfxrombo[i] = rombo[i*2] | (rombo[(i*2)+1]<<8);				
	}
	//sprite de 32x32
	for(i = 0; i < 32 * 32 / 2; i++) 
	{	
		gfxromboGrande[i] = romboGrande[i*2] | (romboGrande[(i*2)+1]<<8);				
	}
	for(i = 0; i < 16 * 16 / 2; i++) 
	{	
		gfxArriba[i] = arriba[i*2] | (arriba[(i*2)+1]<<8);				
	}
	for(i = 0; i < 16 * 16 / 2; i++) 
	{	
		gfxAbajo[i] = abajo[i*2] | (abajo[(i*2)+1]<<8);				
	}
	for(i = 0; i < 16 * 16 / 2; i++) 
	{	
		gfxDerecha[i] = derecha[i*2] | (derecha[(i*2)+1]<<8);				
	}
	for(i = 0; i < 16 * 16 / 2; i++) 
	{	
		gfxIzquierda[i] = izquierda[i*2] | (izquierda[(i*2)+1]<<8);				
	}
	for(i = 0; i < 16 * 16 / 2; i++) 
	{	
		gfxProyHorizontal[i] = proyHorizontal[i*2] | (proyHorizontal[(i*2)+1]<<8);				
	}
	for(i = 0; i < 16 * 16 / 2; i++) 
	{	
		gfxProyVertical[i] = proyVertical[i*2] | (proyVertical[(i*2)+1]<<8);				
	}
	
}

/* Esta función dibuja un rombo en la posición x-y de pantalla. A cada rombo que se quiera mostrar en pantalla se le debe asignar un índice distinto, un valor entre 0 y 126 */

void MostrarRombo(int indice, int x, int y)
{ 
 
oamSet(&oamMain, //main graphics engine context
		indice,           //oam index (0 to 127)  
		x, y,   //x and y pixel location of the sprite
		0,                    //priority, lower renders last (on top)
		0,					  //this is the palette index if multiple palettes or the alpha value if bmp sprite	
		SpriteSize_16x16,     
		SpriteColorFormat_256Color, 
		gfxrombo,//+16*16/2,                  //pointer to the loaded graphics
		-1,                  //sprite rotation data  
		false,               //double the size when rotating?
		false,			//hide the sprite?
		false, false, //vflip, hflip
		false	//apply mosaic
		); 
	  
oamUpdate(&oamMain);  
}

/* Esta función borra de la pantalla el Rombo con el índice indicado */
void BorrarRombo(int indice, int x, int y)
{

oamSet(&oamMain, //main graphics engine context
		indice,           //oam index (0 to 127)  
		x, y,   //x and y pixel location of the sprite
		0,                    //priority, lower renders last (on top)
		0,					  //this is the palette index if multiple palettes or the alpha value if bmp sprite	
		SpriteSize_16x16,     
		SpriteColorFormat_256Color, 
		gfxrombo,//+16*16/2,                  //pointer to the loaded graphics
		-1,                  //sprite rotation data  
		false,               //double the size when rotating?
		true,			//hide the sprite?
		false, false, //vflip, hflip
		false	//apply mosaic
		); 
oamUpdate(&oamMain); 

}

void MostrarRomboGrande(int indice, int x, int y)
{ 
 
oamSet(&oamMain, //main graphics engine context
		indice,           //oam index (0 to 127)  
		x, y,   //x and y pixel location of the sprite
		0,                    //priority, lower renders last (on top)
		0,					  //this is the palette index if multiple palettes or the alpha value if bmp sprite	
		SpriteSize_32x32,     
		SpriteColorFormat_256Color, 
		gfxromboGrande,//+16*16/2,                  //pointer to the loaded graphics
		-1,                  //sprite rotation data  
		false,               //double the size when rotating?
		false,			//hide the sprite?
		false, false, //vflip, hflip
		false	//apply mosaic
		); 

	  
oamUpdate(&oamMain);  
}

void BorrarRomboGrande(int indice, int x, int y)
{

oamSet(&oamMain, //main graphics engine context
		indice,           //oam index (0 to 127)  
		x, y,   //x and y pixel location of the sprite
		0,                    //priority, lower renders last (on top)
		0,					  //this is the palette index if multiple palettes or the alpha value if bmp sprite	
		SpriteSize_32x32,     
		SpriteColorFormat_256Color, 
		gfxromboGrande,//+16*16/2,                  //pointer to the loaded graphics
		-1,                  //sprite rotation data  
		false,               //double the size when rotating?

		true,			//hide the sprite?
		false, false, //vflip, hflip
		false	//apply mosaic
		); 
oamUpdate(&oamMain); 

}


void MostrarArriba(int indice, int x, int y)
{ 
 
oamSet(&oamMain, //main graphics engine context
		indice,           //oam index (0 to 127)  
		x, y,   //x and y pixel location of the sprite
		0,                    //priority, lower renders last (on top)
		0,					  //this is the palette index if multiple palettes or the alpha value if bmp sprite	
		SpriteSize_16x16,     
		SpriteColorFormat_256Color, 
		gfxArriba,//+16*16/2,                  //pointer to the loaded graphics
		-1,                  //sprite rotation data  
		false,               //double the size when rotating?
		false,			//hide the sprite?
		false, false, //vflip, hflip
		false	//apply mosaic
		); 
	  
oamUpdate(&oamMain);  
}

/* Esta función borra de la pantalla el Rombo con el índice indicado */
void BorrarArriba(int indice, int x, int y)
{

oamSet(&oamMain, //main graphics engine context
		indice,           //oam index (0 to 127)  
		x, y,   //x and y pixel location of the sprite
		0,                    //priority, lower renders last (on top)
		0,					  //this is the palette index if multiple palettes or the alpha value if bmp sprite	
		SpriteSize_16x16,     
		SpriteColorFormat_256Color, 
		gfxArriba,//+16*16/2,                  //pointer to the loaded graphics
		-1,                  //sprite rotation data  
		false,               //double the size when rotating?
		true,			//hide the sprite?
		false, false, //vflip, hflip
		false	//apply mosaic
		); 
oamUpdate(&oamMain); 

}

void MostrarAbajo(int indice, int x, int y)
{ 
 
oamSet(&oamMain, //main graphics engine context
		indice,           //oam index (0 to 127)  
		x, y,   //x and y pixel location of the sprite
		0,                    //priority, lower renders last (on top)
		0,					  //this is the palette index if multiple palettes or the alpha value if bmp sprite	
		SpriteSize_16x16,     
		SpriteColorFormat_256Color, 
		gfxAbajo,//+16*16/2,                  //pointer to the loaded graphics
		-1,                  //sprite rotation data  
		false,               //double the size when rotating?
		false,			//hide the sprite?
		false, false, //vflip, hflip
		false	//apply mosaic
		); 
	  
oamUpdate(&oamMain);  
}

/* Esta función borra de la pantalla el Rombo con el índice indicado */
void BorrarAbajo(int indice, int x, int y)
{

oamSet(&oamMain, //main graphics engine context
		indice,           //oam index (0 to 127)  
		x, y,   //x and y pixel location of the sprite
		0,                    //priority, lower renders last (on top)
		0,					  //this is the palette index if multiple palettes or the alpha value if bmp sprite	
		SpriteSize_16x16,     
		SpriteColorFormat_256Color, 
		gfxAbajo,//+16*16/2,                  //pointer to the loaded graphics
		-1,                  //sprite rotation data  
		false,               //double the size when rotating?
		true,			//hide the sprite?
		false, false, //vflip, hflip
		false	//apply mosaic
		); 
oamUpdate(&oamMain); 

}

void MostrarDerecha(int indice, int x, int y)
{ 
 
oamSet(&oamMain, //main graphics engine context
		indice,           //oam index (0 to 127)  
		x, y,   //x and y pixel location of the sprite
		0,                    //priority, lower renders last (on top)
		0,					  //this is the palette index if multiple palettes or the alpha value if bmp sprite	
		SpriteSize_16x16,     
		SpriteColorFormat_256Color, 
		gfxDerecha,//+16*16/2,                  //pointer to the loaded graphics
		-1,                  //sprite rotation data  
		false,               //double the size when rotating?
		false,			//hide the sprite?
		false, false, //vflip, hflip
		false	//apply mosaic
		); 
	  
oamUpdate(&oamMain);  
}

/* Esta función borra de la pantalla el Rombo con el índice indicado */
void BorrarDerecha(int indice, int x, int y)
{

oamSet(&oamMain, //main graphics engine context
		indice,           //oam index (0 to 127)  
		x, y,   //x and y pixel location of the sprite
		0,                    //priority, lower renders last (on top)
		0,					  //this is the palette index if multiple palettes or the alpha value if bmp sprite	
		SpriteSize_16x16,     
		SpriteColorFormat_256Color, 
		gfxDerecha,//+16*16/2,                  //pointer to the loaded graphics
		-1,                  //sprite rotation data  
		false,               //double the size when rotating?
		true,			//hide the sprite?
		false, false, //vflip, hflip
		false	//apply mosaic
		); 
oamUpdate(&oamMain); 

}

void MostrarIzquierda(int indice, int x, int y)
{ 
 
oamSet(&oamMain, //main graphics engine context
		indice,           //oam index (0 to 127)  
		x, y,   //x and y pixel location of the sprite
		0,                    //priority, lower renders last (on top)
		0,					  //this is the palette index if multiple palettes or the alpha value if bmp sprite	
		SpriteSize_16x16,     
		SpriteColorFormat_256Color, 
		gfxIzquierda,//+16*16/2,                  //pointer to the loaded graphics
		-1,                  //sprite rotation data  
		false,               //double the size when rotating?
		false,			//hide the sprite?
		false, false, //vflip, hflip
		false	//apply mosaic
		); 
	  
oamUpdate(&oamMain);  
}

/* Esta función borra de la pantalla el Rombo con el índice indicado */
void BorrarIzquierda(int indice, int x, int y)
{

oamSet(&oamMain, //main graphics engine context
		indice,           //oam index (0 to 127)  
		x, y,   //x and y pixel location of the sprite
		0,                    //priority, lower renders last (on top)
		0,					  //this is the palette index if multiple palettes or the alpha value if bmp sprite	
		SpriteSize_16x16,     
		SpriteColorFormat_256Color, 
		gfxIzquierda,//+16*16/2,                  //pointer to the loaded graphics
		-1,                  //sprite rotation data  
		false,               //double the size when rotating?
		true,			//hide the sprite?
		false, false, //vflip, hflip
		false	//apply mosaic
		); 
oamUpdate(&oamMain); 

}
void MostrarProyH(int indice, int x, int y)
{ 
 
oamSet(&oamMain, //main graphics engine context
		indice,           //oam index (0 to 127)  
		x, y,   //x and y pixel location of the sprite
		0,                    //priority, lower renders last (on top)

		0,					  //this is the palette index if multiple palettes or the alpha value if bmp sprite	
		SpriteSize_16x16,     
		SpriteColorFormat_256Color, 

		gfxProyHorizontal,//+16*16/2,                  //pointer to the loaded graphics
		-1,                  //sprite rotation data  
		false,               //double the size when rotating?
		false,			//hide the sprite?
		false, false, //vflip, hflip
		false	//apply mosaic
		); 
	  
oamUpdate(&oamMain);  
}

/* Esta función borra de la pantalla el Rombo con el índice indicado */
void BorrarProyH(int indice, int x, int y)
{

oamSet(&oamMain, //main graphics engine context
		indice,           //oam index (0 to 127)  
		x, y,   //x and y pixel location of the sprite
		0,                    //priority, lower renders last (on top)
		0,					  //this is the palette index if multiple palettes or the alpha value if bmp sprite	
		SpriteSize_16x16,     
		SpriteColorFormat_256Color, 
		gfxProyHorizontal,//+16*16/2,                  //pointer to the loaded graphics
		-1,                  //sprite rotation data  
		false,               //double the size when rotating?
		true,			//hide the sprite?
		false, false, //vflip, hflip
		false	//apply mosaic
		); 
oamUpdate(&oamMain); 

}

void MostrarProyV(int indice, int x, int y)
{ 
 
oamSet(&oamMain, //main graphics engine context
		indice,           //oam index (0 to 127)  
		x, y,   //x and y pixel location of the sprite
		0,                    //priority, lower renders last (on top)

		0,					  //this is the palette index if multiple palettes or the alpha value if bmp sprite	
		SpriteSize_16x16,     
		SpriteColorFormat_256Color, 

		gfxProyVertical,//+16*16/2,                  //pointer to the loaded graphics
		-1,                  //sprite rotation data  
		false,               //double the size when rotating?
		false,			//hide the sprite?
		false, false, //vflip, hflip
		false	//apply mosaic
		); 
	  
oamUpdate(&oamMain);  
}

/* Esta función borra de la pantalla el Rombo con el índice indicado */
void BorrarProyV(int indice, int x, int y)
{

oamSet(&oamMain, //main graphics engine context
		indice,           //oam index (0 to 127)  
		x, y,   //x and y pixel location of the sprite
		0,                    //priority, lower renders last (on top)
		0,					  //this is the palette index if multiple palettes or the alpha value if bmp sprite	
		SpriteSize_16x16,     
		SpriteColorFormat_256Color, 
		gfxProyVertical,//+16*16/2,                  //pointer to the loaded graphics
		-1,                  //sprite rotation data  
		false,               //double the size when rotating?
		true,			//hide the sprite?
		false, false, //vflip, hflip
		false	//apply mosaic
		); 
oamUpdate(&oamMain); 

}

