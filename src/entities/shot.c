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
		shots[i].width = 0;
		shots[i].height= 0;
		shots[i].level = 0;
		shots[i].alive = 0;
		shots[i].dir = sd_up;
		shots[i].anim.frames = (TAnimFrame**)g_aniShotR[0][shots[i].level];
		shots[i].anim.frame_id = 0;
		shots[i].anim.time = ANI_FPS_SHOT;
		shots[i].anim.status = as_cycle;
		shots[i].nextAnim = shots[i].anim.frames;
	}
}

void createShot(struct Heroe *heroe) {
	if(heroe->id == G_heroe1) {
		// Disparo Chica
	}
	else {
		// Disparo Chico
	}
}