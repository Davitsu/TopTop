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
#include "../heroe/heroe.h"
#include "../constants.h"
#include "../maps/maps.h"

struct Heroe heroe1;
struct Heroe heroe2;

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
   drawHUD();
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
   if (cpct_isKeyPressed(Key_A) && heroe1.x > G_borderLeft_p1) {  //izquierda
      heroe1.x--;
   }
   else if (cpct_isKeyPressed(Key_D) && heroe1.x < G_borderRight_p1) {  //derecha
      heroe1.x++;
   }
   else if (cpct_isKeyPressed(Key_W) && heroe1.y > G_borderTop_p1) {  //arriba
      heroe1.y-=2;
   }
   else if (cpct_isKeyPressed(Key_S) && heroe1.y < G_borderBottom_p1) { //abajo
      heroe1.y+=2;
   }
   else {   //si no se pulsa ninguna

   }
 
   //PLAYER 2
   if (cpct_isKeyPressed(Key_CursorLeft) && heroe2.x > G_borderLeft_p2) {  //izquierda
      heroe2.x--;
   }
   else if (cpct_isKeyPressed(Key_CursorRight) && heroe2.x < G_borderRight_p2) {  //derecha
      heroe2.x++;
   }
   else if (cpct_isKeyPressed(Key_CursorUp) && heroe2.y > G_borderTop_p2) {  //arriba
      heroe2.y-=2;
   }
   else if (cpct_isKeyPressed(Key_CursorDown) && heroe2.y < G_borderBottom_p2) { //abajo
      heroe2.y+=2;
   }
   else {   //si no se pulsa ninguna
      //estado idle
   }
}

// Dibuja los personajes
void drawHeroes() {
   u8* pvideomem;
   u8 c;

   c = cpct_px2byteM0(0,0);  // Para dibujar el color solido - Colour pattern 0-0 (black-black)

   //Se dibuja el rectangulo negro para borrar el rastro
   pvideomem = cpct_getScreenPtr((u8*)0xC000, heroe1.preX, heroe1.preY);
   cpct_drawSolidBox(pvideomem, c, 4, 12);

   //Se dibuja el sprite del personaje 1
   pvideomem = cpct_getScreenPtr((u8*)0xC000, heroe1.x, heroe1.y);
   cpct_drawSprite(G_heroR_idle01, pvideomem, 4, 12); 

   //Se dibuja el rectangulo negro para borrar el rastro
   pvideomem = cpct_getScreenPtr((u8*)0xC000, heroe2.preX, heroe2.preY);
   cpct_drawSolidBox(pvideomem, c, 4, 12);

   //Se dibuja el sprite del personaje 2
   pvideomem = cpct_getScreenPtr((u8*)0xC000, heroe2.x, heroe2.y);
   cpct_drawSprite(G_heroB_idle01, pvideomem, 4, 12);
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

// Dibuja el HUD
void drawHUD() {
   u8* pvideomem;
   u8 i;

   //Marco del HUD
   pvideomem = cpct_getScreenPtr((u8*)0xC000, 0, 0);
   cpct_drawSprite(G_border01, pvideomem, 4, 8); 

   pvideomem = cpct_getScreenPtr((u8*)0xC000, 0, 8);
   cpct_drawSprite(G_border11, pvideomem, 4, 8); 
   pvideomem = cpct_getScreenPtr((u8*)0xC000, 0, 16);
   cpct_drawSprite(G_border11, pvideomem, 4, 8); 

   pvideomem = cpct_getScreenPtr((u8*)0xC000, 0, 24);
   cpct_drawSprite(G_border10, pvideomem, 4, 8);    

   for(i = 0; i < 7; i++) {
      pvideomem = cpct_getScreenPtr((u8*)0xC000, i*4+4, 0);
      cpct_drawSprite(G_border02, pvideomem, 4, 8); 

      pvideomem = cpct_getScreenPtr((u8*)0xC000, i*4+4, 24);
      cpct_drawSprite(G_border09, pvideomem, 4, 8); 

      pvideomem = cpct_getScreenPtr((u8*)0xC000, i*4+48, 0);
      cpct_drawSprite(G_border02, pvideomem, 4, 8); 

      pvideomem = cpct_getScreenPtr((u8*)0xC000, i*4+48, 24);
      cpct_drawSprite(G_border09, pvideomem, 4, 8); 
   }

   pvideomem = cpct_getScreenPtr((u8*)0xC000, 32, 0);
   cpct_drawSprite(G_border03, pvideomem, 4, 8); 
   pvideomem = cpct_getScreenPtr((u8*)0xC000, 36, 0);
   cpct_drawSprite(G_border04, pvideomem, 4, 8); 
   pvideomem = cpct_getScreenPtr((u8*)0xC000, 32, 8);
   cpct_drawSprite(G_border05, pvideomem, 4, 8); 
   pvideomem = cpct_getScreenPtr((u8*)0xC000, 36, 8);
   cpct_drawSprite(G_border06, pvideomem, 4, 8); 
   pvideomem = cpct_getScreenPtr((u8*)0xC000, 36, 16);
   cpct_drawSprite(G_border07, pvideomem, 4, 8);
   pvideomem = cpct_getScreenPtr((u8*)0xC000, 32, 24);
   cpct_drawSprite(G_border09, pvideomem, 4, 8);
   pvideomem = cpct_getScreenPtr((u8*)0xC000, 36, 24);
   cpct_drawSprite(G_border08, pvideomem, 4, 8);

   pvideomem = cpct_getScreenPtr((u8*)0xC000, 40, 0);
   cpct_drawSprite(G_border12, pvideomem, 4, 8);
   pvideomem = cpct_getScreenPtr((u8*)0xC000, 44, 0);
   cpct_drawSprite(G_border13, pvideomem, 4, 8);
   pvideomem = cpct_getScreenPtr((u8*)0xC000, 44, 8);
   cpct_drawSprite(G_border14, pvideomem, 4, 8);
   pvideomem = cpct_getScreenPtr((u8*)0xC000, 40, 8);
   cpct_drawSprite(G_border15, pvideomem, 4, 8);
   pvideomem = cpct_getScreenPtr((u8*)0xC000, 76, 0);
   cpct_drawSprite(G_border16, pvideomem, 4, 8);
   pvideomem = cpct_getScreenPtr((u8*)0xC000, 76, 24);
   cpct_drawSprite(G_border17, pvideomem, 4, 8);
   pvideomem = cpct_getScreenPtr((u8*)0xC000, 44, 24); 
   cpct_drawSprite(G_border09, pvideomem, 4, 8);
   pvideomem = cpct_getScreenPtr((u8*)0xC000, 40, 24); 
   cpct_drawSprite(G_border20, pvideomem, 4, 8);
   pvideomem = cpct_getScreenPtr((u8*)0xC000, 40, 16); 
   cpct_drawSprite(G_border18, pvideomem, 4, 8);
   pvideomem = cpct_getScreenPtr((u8*)0xC000, 76, 8); 
   cpct_drawSprite(G_border19, pvideomem, 4, 8);
   pvideomem = cpct_getScreenPtr((u8*)0xC000, 76, 16); 
   cpct_drawSprite(G_border19, pvideomem, 4, 8);


   // DIBUJAR CORAZONES
   //if(heroe1.health == 6) {
      pvideomem = cpct_getScreenPtr((u8*)0xC000, 12, 6); 
      cpct_drawSprite(G_heartR_full, pvideomem, 4, 8);
      pvideomem = cpct_getScreenPtr((u8*)0xC000, 16, 6); 
      cpct_drawSprite(G_heartR_full, pvideomem, 4, 8);
      pvideomem = cpct_getScreenPtr((u8*)0xC000, 20, 6); 
      cpct_drawSprite(G_heartR_full, pvideomem, 4, 8);
   //}

      pvideomem = cpct_getScreenPtr((u8*)0xC000, 64, 6); 
      cpct_drawSprite(G_heartB_full, pvideomem, 4, 8);
      pvideomem = cpct_getScreenPtr((u8*)0xC000, 60, 6); 
      cpct_drawSprite(G_heartB_full, pvideomem, 4, 8);
      pvideomem = cpct_getScreenPtr((u8*)0xC000, 56, 6); 
      cpct_drawSprite(G_heartB_full, pvideomem, 4, 8);

}