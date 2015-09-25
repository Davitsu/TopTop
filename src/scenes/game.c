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
#include "../maps/maps.h"

// Inicializa el menu
void initGame() {
   u8 x, y;

   // Lee y prepara los mapas
   for(y=0; y<G_mapH; y++) {
      for(x=0; x<G_mapW; x++) {
         // Obtenemos los datos de nuestros mapas
         mapLeft[y*G_mapW+x] = G_map01[y*G_mapW+x];
         mapRight[y*G_mapW+x] = G_map01[y*G_mapW+x];

         // Si el tile es pared... (mejorar este codigo, evitar duplicar los ifs)
         if(mapLeft[y*G_mapW+x] == 0x00) {
            drawTile(G_tile01, x, y, G_left);
         }
         if(mapRight[y*G_mapW+x] == 0x00) {
            drawTile(G_tile01, x, y, G_right);
         }
      }
   }

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

   // Filas
   for(i=0; i<20; i++) {   // Fila superior
      pvideomem = cpct_getScreenPtr(G_SCR_VMEM, i*G_tileSizeW, 4*G_tileSizeH);
      cpct_drawTileAligned4x8(G_tile01, pvideomem);
   }

   for(i=0; i<24; i++) {   // Fila inferior
      pvideomem = cpct_getScreenPtr(G_SCR_VMEM, i*G_tileSizeW, 24*G_tileSizeH);
      cpct_drawTileAligned4x8(G_tile01, pvideomem);
   }

   // Columnas
   for(i=0; i<19; i++) {   // Columna izquierda
      pvideomem = cpct_getScreenPtr(G_SCR_VMEM, 0, 5*G_tileSizeH+i*G_tileSizeH);
      cpct_drawTileAligned4x8(G_tile01, pvideomem);
   }

   for(i=0; i<19; i++) {   // Columna central izq
      pvideomem = cpct_getScreenPtr(G_SCR_VMEM, 9*G_tileSizeW, 5*G_tileSizeH+i*G_tileSizeH);
      cpct_drawTileAligned4x8(G_tile01, pvideomem);
   }

   for(i=0; i<19; i++) {   // Columna central der
      pvideomem = cpct_getScreenPtr(G_SCR_VMEM, 10*G_tileSizeW, 5*G_tileSizeH+i*G_tileSizeH);
      cpct_drawTileAligned4x8(G_tile01, pvideomem);
   }
   
   for(i=0; i<19; i++) {   // Columna derecha
      pvideomem = cpct_getScreenPtr(G_SCR_VMEM, 19*G_tileSizeW, 5*G_tileSizeH+i*G_tileSizeH);
      cpct_drawTileAligned4x8(G_tile01, pvideomem);
   }
}

// Dibuja un sprite en el tile indicado (coordenadas de tile, no en pixeles)
void drawTile(u8* spriteTile, u8 xTile, u8 yTile, u8 side) {
   u8* pvideomem;

   // Mapa izq (side 0)
   if(side == G_left) 
      pvideomem = cpct_getScreenPtr(G_SCR_VMEM, xTile * G_tileSizeW + G_mapStartLX, yTile*G_tileSizeH+G_mapStartLY);
   // Mapa der (side 1)
   else      
      pvideomem = cpct_getScreenPtr(G_SCR_VMEM, xTile * G_tileSizeW + G_mapStartRX, yTile*G_tileSizeH+G_mapStartRY);
   
   cpct_drawTileAligned4x8(spriteTile, pvideomem);
}