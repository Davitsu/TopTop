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
	updateSensorHeroe(heroe1);

	heroe2->id = G_heroe2;
	heroe2->x = 24;
	heroe2->y = 140;
	updateSensorHeroe(heroe2);
}

// Actualiza la posicion tile de los sensores del heroe
void updateSensorHeroe(struct Heroe *heroe) {
	heroe->sensorLT = byte2tile(heroe->x, heroe->y);
	heroe->sensorLC = byte2tile(heroe->x, heroe->y + G_heroeH - G_tileSizeH);
	heroe->sensorLD = byte2tile(heroe->x, heroe->y + G_heroeH - 1);
	heroe->sensorRT = byte2tile(heroe->x + G_heroeW - 1, heroe->y);
	heroe->sensorRC = byte2tile(heroe->x + G_heroeW - 1, heroe->y + G_heroeH - G_tileSizeH);
	heroe->sensorRD = byte2tile(heroe->x + G_heroeW - 1, heroe->y + G_heroeH - 1);
	heroe->sensorTL = byte2tile(heroe->x, heroe->y);
	heroe->sensorTR = byte2tile(heroe->x + G_heroeW - 1, heroe->y);
	heroe->sensorDL = byte2tile(heroe->x, heroe->y + G_heroeH - 1);
	heroe->sensorDR = byte2tile(heroe->x + G_heroeW - 1, heroe->y + G_heroeH - 1);
}

// Convierte la posicion en bytes a posicion en tiles
u8 byte2tile(u8 x, u8 y) {
	u8 res = x / G_tileSizeW + (y / G_tileSizeH) * G_mapWTiles;
	return res;
}