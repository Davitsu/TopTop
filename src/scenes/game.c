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
#include "../sprites/animation.h"
#include "../entities/heroe.h"
#include "../constants.h"
#include "../maps/maps.h"

struct Heroe heroe1;
struct Heroe heroe2;

u8 map1[152];
u8 map2[152];

extern u8* const G_SCR_VMEM = (u8*)0xC000; 

// Inicializa el menu
void initGame() {
   u8 x, y;

   // Lee y prepara los mapas
   for(y=0; y<G_mapHTiles; y++) {
      for(x=0; x<G_mapWTiles; x++) {
         // Obtenemos los datos de nuestros mapas
         map1[y*G_mapWTiles+x] = G_map01[y*G_mapWTiles+x];
         map2[y*G_mapWTiles+x] = G_map01[y*G_mapWTiles+x];

         // Si el tile es pared... (mejorar este codigo, evitar duplicar los ifs)
         if(map1[y*G_mapWTiles+x] == 0x00) {
            drawTile(G_tile01, x, y, G_left);
         }
         if(map2[y*G_mapWTiles+x] == 0x00) {
            drawTile(G_tile01, x, y, G_right);
         }
      }
   }

	drawGameBorder();
   initHeroes(&heroe1, &heroe2);
}

// Update del menu
u8 updateGame() {
   updateHeroes();
   cpct_waitVSYNC();             // Wait for VSYNC and...
   drawHeroes();
   
	return G_sceneGame;
}

void updateHeroes() {
   heroe1.preX = heroe1.x;
   heroe1.preY = heroe1.y;

   heroe2.preX = heroe2.x;
   heroe2.preY = heroe2.y;

   // Scan Keyboard
   cpct_scanKeyboard_f();

   //PLAYER 1
   if (cpct_isKeyPressed(Key_A) && heroe1.x > 0) {  //izquierda
      heroe1.x--;
   }
   else if (cpct_isKeyPressed(Key_D) && heroe1.x < G_mapWBytes - G_heroeW) {  //derecha
      heroe1.x++;
   }
   else if (cpct_isKeyPressed(Key_W) && heroe1.y > 0) {  //arriba
      heroe1.y-=2;
   }
   else if (cpct_isKeyPressed(Key_S) && heroe1.y < G_mapHBytes - G_heroeH) { //abajo
      heroe1.y+=2;
   }
   else {   //si no se pulsa ninguna
      //estado idle
   }
 
   //PLAYER 2
   if (cpct_isKeyPressed(Key_CursorLeft) && heroe2.x > 0) {  //izquierda
      heroe2.x--;
   }
   else if (cpct_isKeyPressed(Key_CursorRight) && heroe2.x < G_mapWBytes - G_heroeW) {  //derecha
      heroe2.x++;
   }
   else if (cpct_isKeyPressed(Key_CursorUp) && heroe2.y > 0) {  //arriba
      heroe2.y-=2;
   }
   else if (cpct_isKeyPressed(Key_CursorDown) && heroe2.y < G_mapHBytes - G_heroeH) { //abajo
      heroe2.y+=2;
   }
   else {   //si no se pulsa ninguna
      //estado idle
   }

   updateSensorHeroe(&heroe1);
   checkHeroeCollision(&heroe1, map1);

   updateSensorHeroe(&heroe2);
   checkHeroeCollision(&heroe2, map2);
}

// Comprueba las colisiones entre un heroe y tiles
void checkHeroeCollision(struct Heroe *heroe, u8 map[]) {
   // Colisiones horizontales
   if(map[heroe->sensorLT] == 0x00 || map[heroe->sensorLC] == 0x00 || map[heroe->sensorLD] == 0x00 ||
      map[heroe->sensorRT] == 0x00 || map[heroe->sensorRC] == 0x00 || map[heroe->sensorRD] == 0x00) {
      heroe->x = heroe->preX;
   }

   // Colisiones verticales
   if(map[heroe->sensorTL] == 0x00 || map[heroe->sensorTR] == 0x00 ||
      map[heroe->sensorDL] == 0x00 || map[heroe->sensorDR] == 0x00) {
      heroe->y = heroe->preY;
   }
}

// Dibuja los personajes
void drawHeroes() {
   u8* pvideomem;
   u8 c;

   c = cpct_px2byteM0(0,0);  // Para dibujar el color solido - Colour pattern 0-0 (black-black)

   //Se dibuja el rectangulo negro para borrar el rastro
   pvideomem = cpct_getScreenPtr(G_SCR_VMEM, G_offsetX_m1 + heroe1.preX, G_offsetY + heroe1.preY);
   cpct_drawSolidBox(pvideomem, c, G_heroeW, G_heroeH);

   //Se dibuja el sprite del personaje 1
   pvideomem = cpct_getScreenPtr(G_SCR_VMEM, G_offsetX_m1 + heroe1.x, G_offsetY + heroe1.y);
   cpct_drawSprite(G_heroR_idle01, pvideomem, G_heroeW, G_heroeH); 

   //Se dibuja el rectangulo negro para borrar el rastro
   pvideomem = cpct_getScreenPtr(G_SCR_VMEM, G_offsetX_m2 + heroe2.preX, G_offsetY + heroe2.preY);
   cpct_drawSolidBox(pvideomem, c, G_heroeW, G_heroeH);

   //Se dibuja el sprite del personaje 2
   pvideomem = cpct_getScreenPtr(G_SCR_VMEM, G_offsetX_m2 + heroe2.x, G_offsetY + heroe2.y);
   cpct_drawSprite(G_heroB_idle01, pvideomem, G_heroeW, G_heroeH);
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
void drawTile(u8 *spriteTile, u8 xTile, u8 yTile, u8 side) {
   u8* pvideomem;

   // Mapa izq (side 0)
   if(side == G_left) 
      pvideomem = cpct_getScreenPtr(G_SCR_VMEM, xTile * G_tileSizeW + G_offsetX_m1, yTile*G_tileSizeH+G_offsetY);
   // Mapa der (side 1)
   else      
      pvideomem = cpct_getScreenPtr(G_SCR_VMEM, xTile * G_tileSizeW + G_offsetX_m2, yTile*G_tileSizeH+G_offsetY);
   
   cpct_drawTileAligned4x8(spriteTile, pvideomem);
}