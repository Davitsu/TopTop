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
#include "heroe.h"
#include "../sprites/animation.h"
#include "../sprites/sprites.h"
#include "../constants.h"

// Crea a los personajes
void initHeroes(struct Heroe *heroe1, struct Heroe *heroe2) {
	heroe1->id = G_heroe1;
	heroe1->x = 24;
	heroe1->y = 140;
	heroe1->health = 6;
	heroe1->anim.frames = (TAnimFrame**)G_aniHeroR_run_right;
	heroe1->anim.frame_id = 0;
	heroe1->anim.time = ANI_FPS_RUN;
	heroe1->anim.status = as_cycle;
	updateSensorHeroe(heroe1);

	heroe2->id = G_heroe2;
	heroe2->x = 24;
	heroe2->y = 140;
	heroe2->health = 6;
	heroe2->anim.frames = (TAnimFrame**)G_aniHeroB_run_left;
	heroe2->anim.frame_id = 0;
	heroe2->anim.time = ANI_FPS_RUN;
	heroe2->anim.status = as_cycle;
	updateSensorHeroe(heroe2);
}

// Actualiza la posicion tile de los sensores del heroe
void updateSensorHeroe(struct Heroe *heroe) {
	heroe->sensorLT = byte2tile1(heroe->x, heroe->y);
	heroe->sensorLC = byte2tile1(heroe->x, heroe->y + G_heroeH - G_tileSizeH);
	heroe->sensorLD = byte2tile1(heroe->x, heroe->y + G_heroeH - 1);
	heroe->sensorRT = byte2tile1(heroe->x + G_heroeW - 1, heroe->y);
	heroe->sensorRC = byte2tile1(heroe->x + G_heroeW - 1, heroe->y + G_heroeH - G_tileSizeH);
	heroe->sensorRD = byte2tile1(heroe->x + G_heroeW - 1, heroe->y + G_heroeH - 1);
	heroe->sensorTL = byte2tile1(heroe->x, heroe->y);
	heroe->sensorTR = byte2tile1(heroe->x + G_heroeW - 1, heroe->y);
	heroe->sensorDL = byte2tile1(heroe->x, heroe->y + G_heroeH - 1);
	heroe->sensorDR = byte2tile1(heroe->x + G_heroeW - 1, heroe->y + G_heroeH - 1);
}

// Convierte la posicion en bytes a posicion en tiles (1 dimension)
u8 byte2tile1(u8 x, u8 y) {
	u8 res = x / G_tileSizeW + (y / G_tileSizeH) * G_mapWTiles;
	return res;
}

// Convierte la posicion en bytes a posicion en tiles (2 dimensiones)
void byte2tile2(u8 *x, u8 *y) {
	*x = *x / G_tileSizeW;
	*y = *y / G_tileSizeH;
}