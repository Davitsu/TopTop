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

#include <cpctelera.h>
#include "game.h"
#include "../sprites/sprites.h"
#include "../constants.h"

// Inicializa el menu
void initGame() {
	drawGameBorder();
}

// Update del menu
u8 updateGame() {
	// Code...
	return G_sceneGame;
}

// Dibuja el borde del area de juego
void drawGameBorder() {
   u8* pvideomem;
   u8 i;

   for(i=0; i<20; i++) {
      pvideomem = cpct_getScreenPtr((u8*)0xC000, i*4, 4*8);
      cpct_drawTileAligned4x8(G_tile01, pvideomem);
   }

   for(i=0; i<24; i++) {
      pvideomem = cpct_getScreenPtr((u8*)0xC000, i*4, 24*8);
      cpct_drawTileAligned4x8(G_tile01, pvideomem);
   }

   for(i=0; i<19; i++) {
      pvideomem = cpct_getScreenPtr((u8*)0xC000, 0, 5*8+i*8);
      cpct_drawTileAligned4x8(G_tile01, pvideomem);
   }

   for(i=0; i<19; i++) {
      pvideomem = cpct_getScreenPtr((u8*)0xC000, 9*4, 5*8+i*8);
      cpct_drawTileAligned4x8(G_tile01, pvideomem);
   }

   for(i=0; i<19; i++) {
      pvideomem = cpct_getScreenPtr((u8*)0xC000, 10*4, 5*8+i*8);
      cpct_drawTileAligned4x8(G_tile01, pvideomem);
   }
   
   for(i=0; i<19; i++) {
      pvideomem = cpct_getScreenPtr((u8*)0xC000, 19*4, 5*8+i*8);
      cpct_drawTileAligned4x8(G_tile01, pvideomem);
   }
}