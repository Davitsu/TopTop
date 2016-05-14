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

const u8 jumpValues[G_jumpSize] = {6, 5, 4, 3, 2, 2, 1, 1, 0}; 	// Valores de la velocidad de salto/caida en cada frame

// Crea a los personajes
void initHeroes(struct Heroe *heroe, u8 idHeroe) {
	if(idHeroe == G_heroe1) {
		heroe->id = G_heroe1;
		heroe->side = G_left;
		heroe->x = 24;
		heroe->y = 140;
		heroe->anim.frames = (TAnimFrame**)g_aniHeroR[0][heroe->side];
	}
	else {
		heroe->id = G_heroe2;
		heroe->side = G_right;
		heroe->x = 4;
		heroe->y = 140;
		heroe->anim.frames = (TAnimFrame**)g_aniHeroB[0][heroe->side];
	}

	heroe->anim.frame_id = 0;
	heroe->anim.time = ANI_FPS_RUN;
	heroe->anim.status = as_cycle;
	heroe->nextAnim = heroe->anim.frames;
	heroe->preX = heroe->x;
	heroe->preY = heroe->y;
	heroe->stateY = sy_land;
	heroe->jumpPressed = 0;
	heroe->duckPressed = 0;
	heroe->shotPressed = 0;
	heroe->upPressed = 0;
	heroe->health = 6;
	heroe->cooldown = 0;
	heroe->level = sl_1;
	heroe->readyNextLevel = 0;
	updateSensorHeroe(heroe);
}

void resetHeroes(struct Heroe *heroe) {
	if(heroe->id == G_heroe1) {
		heroe->x = 24;
		heroe->y = 140;
		heroe->side = G_left;
	}
	else {
		heroe->x = 4;
		heroe->y = 140;
		heroe->side = G_right;
	}
	heroe->preX = heroe->x;
	heroe->preY = heroe->y;
	heroe->stateY = sy_land;
	heroe->cooldown = 0;
	heroe->readyNextLevel = 0;
	updateSensorHeroe(heroe);
}

// Actualiza el salto del heroe
void updateJump(struct Heroe *heroe) {
	if(heroe->stateY == sy_jump) {
		// Actualiza el salto
		heroe->y -= jumpValues[heroe->jumpFactor];

		if(heroe->jumpFactor < G_jumpSize-1) { 	// Si el salto no ha terminado seguimos subiendo
			heroe->jumpFactor++;
		}
		else { 									// Si ha terminado pasamos a caer
			heroe->stateY = sy_fall;
			heroe->jumpFactor--;
		}
	}
	else if(heroe->stateY == sy_fall) {
		// Actualiza la caida
		heroe->y += jumpValues[heroe->jumpFactor];

		if(heroe->jumpFactor > 2) { 			// Aceleramos hasta la posicion 6 del array
			heroe->jumpFactor--;
		}
	}
}

// Actualizamos el cooldown
void updateCooldown(struct Heroe *heroe) {
	if(heroe->cooldown > 0) {
		heroe->cooldown--;
	}
}

// Actualiza la posicion tile de los sensores del heroe
void updateSensorHeroe(struct Heroe *heroe) {
	heroe->sensorLT = byte2tile1(heroe->x, heroe->y + 2);
	heroe->sensorLC = byte2tile1(heroe->x, heroe->y + G_heroeH - G_tileSizeH);
	heroe->sensorLD = byte2tile1(heroe->x, heroe->y + G_heroeH - 3);
	heroe->sensorRT = byte2tile1(heroe->x + G_heroeW - 1, heroe->y + 2);
	heroe->sensorRC = byte2tile1(heroe->x + G_heroeW - 1, heroe->y + G_heroeH - G_tileSizeH);
	heroe->sensorRD = byte2tile1(heroe->x + G_heroeW - 1, heroe->y + G_heroeH - 3);
	heroe->sensorTL = byte2tile1(heroe->x + 1, heroe->y + 1);
	heroe->sensorTR = byte2tile1(heroe->x + G_heroeW - 2, heroe->y + 1);
	heroe->sensorDL = byte2tile1(heroe->x + 1, heroe->y + G_heroeH - 1);
	heroe->sensorDR = byte2tile1(heroe->x + G_heroeW - 2, heroe->y + G_heroeH - 1);
	heroe->sensorCT = byte2tile1(heroe->x + (G_heroeW / 2) - 1, heroe->y + 3);
	heroe->sensorCC = byte2tile1(heroe->x + (G_heroeW / 2) - 1, heroe->y + G_heroeH - 4);
}

// Convierte la posicion en bytes a posicion en tiles (1 dimension)
u8 byte2tile1(u8 x, u8 y) {
	u8 res = x / G_tileSizeW + (y / G_tileSizeH) * G_mapWTiles;
	return res;
}

// Convierte la posicion en bytes a posicion en tiles (2 dimensiones)
void byte2tile2(u8 *x, u8 *y) {
	*x = *x / G_tileSizeW; //*x = *x >> 2;
	*y = *y / G_tileSizeH; //*y = *y >> 3;
}

// Prepara la siguiente animacion
void setAniHeroe(struct Heroe *heroe, u8 idAni) {
	if(heroe->id == G_heroe1) {
		heroe->nextAnim = (TAnimFrame**)g_aniHeroR[idAni][heroe->side];
	}
	else {
		heroe->nextAnim = (TAnimFrame**)g_aniHeroB[idAni][heroe->side];
	}
}