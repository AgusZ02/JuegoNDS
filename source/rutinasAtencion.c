/*-------------------------------------
rutinasAtencion.c
-------------------------------------*/

#include <nds.h>
#include <stdio.h>
#include "definiciones.h"
#include "perifericos.h"
#include "fondos.h"
#include "sprites.h"


int ESTADO;
int seg3;
struct Bala balas[MAX_BALAS];
int vidasJugador;
int tick;
int seg;
int dif;
void RutAtencionTeclado ()
{	
	int tecla = TeclaPulsada();
	switch (tecla)
	{
	case START:
		if (ESTADO == PAUSA) 
		{
			ESTADO = INICIO;
	   		consoleClear();
		} else if(ESTADO == MUERTE){
			ESTADO = INICIO;
			consoleClear();
		} break;
	
	case L:
		if (ESTADO == JUEGO)
		{
			ESTADO = PAUSA;
		} break;
	
	case R:
		if (ESTADO == PAUSA)
		{
			ESTADO = JUEGO;
			MostrarPersonaje(ultimaPos);
			consoleClear();
		} break;
	}
}


void RutAtencionTempo()
{
	int i, puntos;
	
	if (ESTADO==JUEGO)
	{
		tick++;
		
		if (tick%(50-dif)==0) //La frecuencia de aparición de balas
		{
			dispararBala();
			seg++;
		}
		if (seg == 10) //Cada 50*10 ticks, se disminuye en 1 los ticks de frecuencia de aparición, aumentando así la dificultad del juego progresivamente
		{
			seg = 0;
			dif++;
		}
		

		iprintf("\x1b[01;00HPuntuacion=%d",tick);

		for(i = 0; i<MAX_BALAS; i++)
		{
			if (balas[i].viva)
			{
				if (balas[i].ubi==ARRIBA) //ARRIBA -> y++
				{
					if (ultimaPos==ARRIBA && balas[i].posY==80) //el jugador ha bloqueado el proyectil
					{
						balas[i].viva = 0;
						puntos++;
						BorrarProyV(i,balas[i].posX,balas[i].posY);
					}
					else if (ultimaPos!=ARRIBA && balas[i].posY > 80) //La bala le ha dado al jugador===No estaba bloqueandola
					{
						vidasJugador--;
						
						balas[i].viva = 0;
						BorrarProyV(i,balas[i].posX,balas[i].posY);
					}
					else //La bala sigue su recorrido
					{
						balas[i].posY++;
						MostrarProyV(i,balas[i].posX,balas[i].posY);	
					}
				}
				if (balas[i].ubi==ABAJO) //ABAJO -> y--
				{
					if (ultimaPos==ABAJO && balas[i].posY==110) //el jugador ha bloqueado el proyectil
					{
						balas[i].viva = 0;
						puntos++;	
						BorrarProyV(i,balas[i].posX,balas[i].posY);
					}
					else if (ultimaPos!=ABAJO && balas[i].posY < 110) //La bala le ha dado al jugador===No estaba bloqueandola
					{
						vidasJugador--;
						balas[i].viva = 0;
						BorrarProyV(i,balas[i].posX,balas[i].posY);
					}
					else //La bala sigue su recorrido
					{
						balas[i].posY--;
						MostrarProyV(i,balas[i].posX,balas[i].posY);	
					}
				}
				if (balas[i].ubi==DERECHA) //DERECHA -> x--
				{

					if (ultimaPos==DERECHA && balas[i].posX==140) //el jugador ha bloqueado el proyectil
					{
						balas[i].viva = 0;
						puntos++;	
						BorrarProyH(i,balas[i].posX,balas[i].posY);
					}
					else if (ultimaPos!=DERECHA && balas[i].posX < 140) //La bala le ha dado al jugador===No estaba bloqueandola
					{
						vidasJugador--;
						balas[i].viva = 0;
						BorrarProyH(i,balas[i].posX,balas[i].posY);
					}
					else //La bala sigue su recorrido
					{
						balas[i].posX--;
						MostrarProyH(i,balas[i].posX,balas[i].posY);
					}
					
				}
				if (balas[i].ubi==IZQUIERDA) //IZQUIERDA -> x++
				{
					if (ultimaPos==IZQUIERDA && balas[i].posX==110) //el jugador ha bloqueado el proyectil
					{
						balas[i].viva = 0;
						puntos++;
						BorrarProyH(i,balas[i].posX,balas[i].posY);
					}
					else if (ultimaPos!=IZQUIERDA && balas[i].posX > 110) //La bala le ha dado al jugador===No estaba bloqueandola
					{
						vidasJugador--;
						balas[i].viva = 0;
						BorrarProyH(i,balas[i].posX,balas[i].posY);
					}
					else //La bala sigue su recorrido
					{
						balas[i].posX++;
						MostrarProyH(i,balas[i].posX,balas[i].posY);
					}
					
				}
				iprintf("\x1b[04;00HVidas: %d",vidasJugador);
				if (vidasJugador <= 0)
				{
					int j;
					for (j = 0; j < MAX_BALAS; j++)
					{
						balas[j].viva = 0;
						if (balas[j].ubi == ARRIBA || balas[j].ubi == ABAJO)
						{
							BorrarProyV(j,balas[j].posX,balas[j].posY);
						} else{
							BorrarProyH(j,balas[j].posX,balas[j].posY);
						}
						
					}
					consoleClear();
					ESTADO = MUERTE;
				}
					
			}
		}
	}
}

void EstablecerVectorInt()
{
	irqSet(IRQ_TIMER0, RutAtencionTempo);
	irqSet(IRQ_KEYS, RutAtencionTeclado);
	
}

