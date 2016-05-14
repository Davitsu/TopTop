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

void initShot(struct Shot *shot) {
	shot->x = 0;
	shot->y = 0;
	shot->preX = shot->x;
	shot->preY = shot->y;
	shot->width = 0;
	shot->height = 0;
	shot->level = sl_1;
	shot->active = 0;
	shot->drawable = 0;
	shot->dir = sd_up;
	shot->anim.frames = (TAnimFrame**)g_aniShotR[shot->dir][shot->level];
	shot->anim.frame_id = 0;
	shot->anim.time = ANI_FPS_SHOT;
	shot->anim.status = as_cycle;
	shot->nextAnim = shot->anim.frames;
	shot->sensor1 = 0;
	shot->sensor2 = 0;
}

void createShot(struct Heroe *heroe, struct Shot *shot) {
	// Comprobamos si podemos disparar
	if(shot->active == 0 && shot->drawable == 0) {
		shot->active = 1;
		shot->drawable = 3;
		shot->level = heroe->level;

		// Si pulsa arriba, dispara hacia arriba. Si no, depende del lado al que mira el heroe
		if ((cpct_isKeyPressed(Key_W) && heroe->id == G_heroe1) || (cpct_isKeyPressed(Key_CursorUp) && heroe->id == G_heroe2)) {
			shot->dir = sd_up;
		}
		else if (heroe->side == G_left) {
			shot->dir = sd_left;
		}
		else {
			shot->dir = sd_right;
		}
		
		shot->nextAnim = (TAnimFrame**)g_aniShotR[shot->dir][shot->level];

		switch(shot->dir) {
			case sd_left:
				if(shot->level == sl_1) {
					shot->x = heroe->x - 1;
					shot->y = heroe->y + 5;
					shot->width = 4;
					shot->height = 1;
				}
				else if(shot->level == sl_2) {
					shot->x = heroe->x - 1;
					shot->y = heroe->y + 3;
					shot->width = 4;
					shot->height = 5;
				}
				else {
					shot->x = heroe->x - 1;
					shot->y = heroe->y + 2;
					shot->width = 4;
					shot->height = 7;
				}
				break;
			case sd_right:
				if(shot->level == sl_1) {
					shot->x = heroe->x + 1;
					shot->y = heroe->y + 5;
					shot->width = 4;
					shot->height = 1;
				}
				else if(shot->level == sl_2) {
					shot->x = heroe->x + 1;
					shot->y = heroe->y + 3;
					shot->width = 4;
					shot->height = 5;
				}
				else {
					shot->x = heroe->x + 1;
					shot->y = heroe->y + 2;
					shot->width = 4;
					shot->height = 7;
				}
				break;
			case sd_up:
				if(shot->level == sl_1) {
					shot->x = heroe->x + 2;
					shot->y = heroe->y;
					shot->width = 1;
					shot->height = 8;
				}
				else if(shot->level == sl_2) {
					shot->x = heroe->x + 1;
					shot->y = heroe->y;
					shot->width = 3;
					shot->height = 8;
				}
				else {
					shot->x = heroe->x;
					shot->y = heroe->y;
					shot->width = 4;
					shot->height = 8;
				}
				break;
		}

		shot->preX = shot->x;
		shot->preY = shot->y;

		//SFX
		//cpct_akp_SFXPlay(5, 15, 43, 0, 0, AY_CHANNEL_B);
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