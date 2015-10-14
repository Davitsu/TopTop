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

#ifndef _GAME_H_
#define _GAME_H_

#include <types.h>
#include "../constants.h"
#include "../entities/heroe.h"
#include "../entities/shot.h"

void initGame();
void firstDraw();
u8 updateGame();
void createHeroes();
void updateHeroe(struct Heroe*);
void checkHeroeCollision(struct Heroe*, u8*);
void drawHeroes();
void updateShots(struct Heroe*, struct Shot*);
void checkShotsCollision(struct Shot*, u8*, u8);
void drawShots();
void drawGameBorder();
void drawHUD();
void drawTile(u8, u8, u8);
void changeTile(u8, u8, u8, u8);
void redrawTiles(u8);
void repaintBackgroundOverSprite(u8, u8, u8);
void repaintBackgroundOverShot(u8, u8, u8);
void drawMap();
void swapBuffers(u8**);
void swapPrePosShot(u8*, u8*);
void drawHUDBorder();
void drawHearts();
void drawLevel();
void drawPortraits();
void interactHeroeWithMap(struct Heroe*, u8*);

extern struct Heroe heroe1;
extern struct Heroe heroe2;

extern struct Shot shots1[G_maxShots];
extern struct Shot shots2[G_maxShots];

extern u8 map1[G_mapHTiles][G_mapWTiles];
extern u8 map2[G_mapHTiles][G_mapWTiles];

extern u8 level;
extern u8 gotItem;	// 0 = nada, 1 = pocion curacion, 2 = pocion amarilla, 3 = llave

extern u8* const g_SCR_VMEM; 	// Pointer to the start of default video memory screen

#endif