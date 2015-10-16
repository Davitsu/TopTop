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

#ifndef _HEROE_H_
#define _HEROE_H_

#include <types.h>
#include "../sprites/animation.h"
#include "../constants.h"

// Expected Frames per Second drawing Ratio   
#define FPS      50

// Los estados del personaje
typedef enum StateY {
	sy_land, 
	sy_jump,
	sy_fall, 
	sy_duck
};

extern const u8 jumpValues[G_jumpSize];

//Entidad heroe
typedef struct Heroe {
	u8 id;
	u8 x;
	u8 y;
	u8 preX[2];
	u8 preY[2];
	enum StateY stateY;
	u8 jumpFactor;
	u8 jumpPressed;
	u8 duckPressed;
	u8 shotPressed;
	u8 health;
	u8 cooldown;
	enum shotLevel level;
	u8 side;
	TAnimation anim;
	TAnimFrame** nextAnim;
	u8 sensorLT; 	// Sensor Left Top
	u8 sensorLC; 	// Sensor Left Center
	u8 sensorLD;	// Sensor Left Down
	u8 sensorRT; 	// Sensor Right Top
	u8 sensorRC; 	// Sensor Right Center
	u8 sensorRD; 	// Sensor Right Down
	u8 sensorTL; 	// Sensor Top Left
	u8 sensorTR; 	// Sensor Top Right
	u8 sensorDL; 	// Sensor Down Left
	u8 sensorDR; 	// Sensor Down Right
	u8 sensorCC;	// Sensor Center Center
};

void initHeroes(struct Heroe *heroe1, struct Heroe *heroe2);
void updateJump(struct Heroe *heroe);
void updateCooldown(struct Heroe *heroe);
void updateSensorHeroe(struct Heroe *heroe);
void swapPrePos(struct Heroe *heroe);
u8 byte2tile1(u8, u8);
void byte2tile2(u8*, u8*);
void setAniHeroe(struct Heroe*, u8);

#endif