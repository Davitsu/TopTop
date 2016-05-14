//-----------------------------LICENSE NOTICE------------------------------------
//  This file is part of TopTop: An Amstrad CPC Game
//  Copyright (C) 2015 Rantan (@RantanGames)
//
//  This program is free software: you can redistribute it and/or modify
//  it under the terms of the GNU General Public License as published by
//  the Free Software Foundation, either version 3 of the License, or
//  (at your option) any later version.
//
//  This program is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU General Public License for more details.
//
//  You should have received a copy of the GNU General Public License
//  along with this program.  If not, see <http://www.gnu.org/licenses/>.
//------------------------------------------------------------------------------

#include <stdio.h>

#include <cpctelera.h>
#include "shot.h"
#include "../sprites/animation.h"
#include "../sprites/sprites.h"
#include "../constants.h"

void initShots(struct Shot *shots) {
	u8 i;

	for(i=0; i<G_maxShots; i++) {
		shots[i].x = 0;
		shots[i].y = 0;
		shots[i].preX = shots[i].x;
		shots[i].preY = shots[i].y;
		shots[i].width = 0;
		shots[i].height = 0;
		shots[i].level = sl_1;
		shots[i].active = 0;
		shots[i].drawable = 0;
		shots[i].dir = sd_up;
		shots[i].anim.frames = (TAnimFrame**)g_aniShotR[shots[i].dir][shots[i].level];
		shots[i].anim.frame_id = 0;
		shots[i].anim.time = ANI_FPS_SHOT;
		shots[i].anim.status = as_cycle;
		shots[i].nextAnim = shots[i].anim.frames;
		shots[i].sensor1 = 0;
		shots[i].sensor2 = 0;
	}
}

void createShot(struct Heroe *heroe, struct Shot *shots) {
	u8 i;
	u8 j = 0;
	u8 found = 0;

	// Comprobamos si es posible disparar (si hay menos de 3 en pantalla)
	for(i=0; i<G_maxShots && found==0; i++) {
		// Si hay un disparo no activo, ese sera el que usaremos
		if(shots[i].active == 0 && shots[i].drawable == 0) {
			found = 1;
			j = i;
		}
	}

	// Si hemos encontrado un disparo para usar, seguimos
	// si no, se acaba la funcion, no podemos disparar
	if(found == 1) {
		shots[j].active = 1;
		shots[j].drawable = 3;
		shots[j].level = heroe->level;

		// Si pulsa arriba, dispara hacia arriba. Si no, depende del lado al que mira el heroe
		if ((cpct_isKeyPressed(Key_W) && heroe->id == G_heroe1) || (cpct_isKeyPressed(Key_CursorUp) && heroe->id == G_heroe2)) {
			shots[j].dir = sd_up;
		}
		else if (heroe->side == G_left) {
			shots[j].dir = sd_left;
		}
		else {
			shots[j].dir = sd_right;
		}
		
		shots[j].nextAnim = (TAnimFrame**)g_aniShotR[shots[j].dir][shots[j].level];

		switch(shots[j].dir) {
			case sd_left:
				if(shots[j].level == sl_1) {
					shots[j].x = heroe->x - 1;
					shots[j].y = heroe->y + 5;
					shots[j].width = 4;
					shots[j].height = 1;
				}
				else if(shots[j].level == sl_2) {
					shots[j].x = heroe->x - 1;
					shots[j].y = heroe->y + 3;
					shots[j].width = 4;
					shots[j].height = 5;
				}
				else {
					shots[j].x = heroe->x - 1;
					shots[j].y = heroe->y + 2;
					shots[j].width = 4;
					shots[j].height = 7;
				}
				break;
			case sd_right:
				if(shots[j].level == sl_1) {
					shots[j].x = heroe->x + 1;
					shots[j].y = heroe->y + 5;
					shots[j].width = 4;
					shots[j].height = 1;
				}
				else if(shots[j].level == sl_2) {
					shots[j].x = heroe->x + 1;
					shots[j].y = heroe->y + 3;
					shots[j].width = 4;
					shots[j].height = 5;
				}
				else {
					shots[j].x = heroe->x + 1;
					shots[j].y = heroe->y + 2;
					shots[j].width = 4;
					shots[j].height = 7;
				}
				break;
			case sd_up:
				if(shots[j].level == sl_1) {
					shots[j].x = heroe->x + 2;
					shots[j].y = heroe->y;
					shots[j].width = 1;
					shots[j].height = 8;
				}
				else if(shots[j].level == sl_2) {
					shots[j].x = heroe->x + 1;
					shots[j].y = heroe->y;
					shots[j].width = 3;
					shots[j].height = 8;
				}
				else {
					shots[j].x = heroe->x;
					shots[j].y = heroe->y;
					shots[j].width = 4;
					shots[j].height = 8;
				}
				break;
		}

		shots[j].preX = shots[j].x;
		shots[j].preY = shots[j].y;

		//SFX
		cpct_akp_SFXPlay(5, 15, 43, 0, 0, AY_CHANNEL_B);
	}
}

// Actualiza la posicion tile de los sensores del disparo
void updateSensorShot(struct Shot *shot) {
	switch(shot->dir) {
		case sd_left:
			shot->sensor1 = byte2tile1(shot->x, shot->y + shot->height / 2);
			break;
		case sd_right:
			shot->sensor1 = byte2tile1(shot->x + shot->width, shot->y + shot->height / 2);
			break;
		case sd_up:
			shot->sensor1 = byte2tile1(shot->x + shot->width / 2, shot->y);
			break;
	}
}