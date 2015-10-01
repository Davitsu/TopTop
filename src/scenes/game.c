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

u8 map1[G_mapHTiles][G_mapWTiles];
u8 map2[G_mapHTiles][G_mapWTiles];

extern u8* const G_SCR_VMEM = (u8*)0xC000; 

u8* const g_scrbuffers[2] = { (u8*)0xC000, (u8*)0x8000 }; // Direccion de los dos buffers

// Inicializa el menu
void initGame() {
   u8 x, y;

   // Lee y prepara los mapas
   for(y=0; y<G_mapHTiles; y++) {
      for(x=0; x<G_mapWTiles; x++) {
         // Obtenemos los datos de nuestros mapas
         map1[y][x] = G_map01[y*G_mapWTiles+x];
         map2[y][x] = G_map01[y*G_mapWTiles+x];
      }
   }

	drawGameBorder();

   // Inicializamos todas las entidades...
   initHeroes(&heroe1, &heroe2);

   // Preparamos el double buffer y dibujamos...
   cpct_memset_f64(g_scrbuffers[1], 0x00, 0x4000); // Limpiamos el segundo buffer (contiene valores aleatorios)
   cpct_waitVSYNC();                               // Esperamos al VSYNC para esperar a dibujar
   firstDraw();                                    // Dibujamos en el buffer actual
   cpct_waitVSYNC();                               // Volvemos a esperar al VSYNC
   swapBuffers(g_scrbuffers);                      // Cambiamos de buffer
   firstDraw();                                    // Dibujamos en este buffer
}

// Dibuja todo lo que habra en pantalla al comenzar la partida
void firstDraw() {
   drawGameBorder();
   drawMap();
   drawHeroes();
   drawHUD();
}

// Update del menu
u8 updateGame() {
   updateHeroes();
   
   cpct_waitVSYNC();
   swapBuffers(g_scrbuffers);

   repaintBackgroundOverSprite(heroe1.preX, heroe1.preY, G_left);
   repaintBackgroundOverSprite(heroe2.preX, heroe2.preY, G_right);
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
      //heroe1.health--;
      //drawHearts();
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

   }
 
   //PLAYER 2
   if (cpct_isKeyPressed(Key_CursorLeft) && heroe2.x > 0) {  //izquierda
      heroe2.x--;
      //heroe2.health--;
      //drawHearts();
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
   checkHeroeCollision(&heroe1, &map1[0][0]);
   updateAnimation(&heroe1.anim, 0, 0);

   updateSensorHeroe(&heroe2);
   checkHeroeCollision(&heroe2, &map2[0][0]);
   updateAnimation(&heroe2.anim, 0, 0);
}

// Comprueba las colisiones entre un heroe y tiles
void checkHeroeCollision(struct Heroe *heroe, u8 *map) {
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

   //Se dibuja el sprite del personaje 1
   pvideomem = cpct_getScreenPtr(g_scrbuffers[1], G_offsetX_m1 + heroe1.x, G_offsetY + heroe1.y);
   cpct_drawSpriteMasked(heroe1.anim.frames[heroe1.anim.frame_id]->sprite, pvideomem, G_heroeW, G_heroeH);

   //Se dibuja el sprite del personaje 2
   pvideomem = cpct_getScreenPtr(g_scrbuffers[1], G_offsetX_m2 + heroe2.x, G_offsetY + heroe2.y);
   cpct_drawSpriteMasked(heroe2.anim.frames[heroe2.anim.frame_id]->sprite, pvideomem, G_heroeW, G_heroeH);
}

// Dibuja el borde del area de juego
void drawGameBorder() {
   u8* pvideomem;
   u8 i;

   // Filas
   for(i=0; i<20; i++) {   // Fila superior
      pvideomem = cpct_getScreenPtr(g_scrbuffers[1], i*G_tileSizeW, 4*G_tileSizeH);
      cpct_drawTileAligned4x8(G_tile01, pvideomem);
   }

   for(i=0; i<24; i++) {   // Fila inferior
      pvideomem = cpct_getScreenPtr(g_scrbuffers[1], i*G_tileSizeW, 24*G_tileSizeH);
      cpct_drawTileAligned4x8(G_tile01, pvideomem);
   }

   // Columnas
   for(i=0; i<19; i++) {   // Columna izquierda
      pvideomem = cpct_getScreenPtr(g_scrbuffers[1], 0, 5*G_tileSizeH+i*G_tileSizeH);
      cpct_drawTileAligned4x8(G_tile01, pvideomem);
   }

   for(i=0; i<19; i++) {   // Columna central izq
      pvideomem = cpct_getScreenPtr(g_scrbuffers[1], 9*G_tileSizeW, 5*G_tileSizeH+i*G_tileSizeH);
      cpct_drawTileAligned4x8(G_tile01, pvideomem);
   }

   for(i=0; i<19; i++) {   // Columna central der
      pvideomem = cpct_getScreenPtr(g_scrbuffers[1], 10*G_tileSizeW, 5*G_tileSizeH+i*G_tileSizeH);
      cpct_drawTileAligned4x8(G_tile01, pvideomem);
   }
   
   for(i=0; i<19; i++) {   // Columna derecha
      pvideomem = cpct_getScreenPtr(g_scrbuffers[1], 19*G_tileSizeW, 5*G_tileSizeH+i*G_tileSizeH);
      cpct_drawTileAligned4x8(G_tile01, pvideomem);
   }
}

// Dibuja un sprite en el tile indicado (coordenadas de tile, no en pixeles) en el mapa indicado (izquierdo o derecho)
void drawTile(u8 xTile, u8 yTile, u8 side) {
   u8 *pvideomem, *map, *sprTile, offSetX;

   if(side == G_left) {
      offSetX = G_offsetX_m1;
      map = *map1;
   }
   else {
      offSetX = G_offsetX_m2;
      map = *map2;
   }

   pvideomem = cpct_getScreenPtr(g_scrbuffers[1], xTile * G_tileSizeW + offSetX, yTile*G_tileSizeH+G_offsetY);

   // Comprobamos el tipo del tile saber que grafico dibujar
   if(map[yTile*G_mapWTiles+xTile] == 0x00) {
      sprTile = (u8*)G_tile01;
   }
   else {
      sprTile = (u8*)G_tileBlack;
   }
   // Lo dibujamos
   cpct_drawTileAligned4x8_f(sprTile, pvideomem);
}

// Redibuja los tiles adyacentes al player (limpia su rastro)
void repaintBackgroundOverSprite(u8 x, u8 y, u8 side) {
   byte2tile2(&x, &y);

   // Ahora limpiamos el area de tiles adyacentes al jugador (3x4 tiles)
   // Siendo sprites de 8x12 pixeles puede parecer que solo necesitamos 2x3 tiles,
   // pero al usar el doble buffer, tambien hace falta limpiar los tiles de la izquierda
   // y arriba. Vamos limpiando columnas de 1x4 hasta completar todos los tiles: 

   // [x][-][-][-] <- Columna y-1
   if(y-1 >= 0) {
      drawTile(x, y-1, side);
      if(x+1 < G_mapWTiles) drawTile(x+1, y-1, side);
      if(x-1 >= 0) drawTile(x-1, y-1, side);
   }

   // [-][x][-][-] <- Columna y
   drawTile(x, y, side);
   if(x+1 < G_mapWTiles) drawTile(x+1, y, side);
   if(x-1 >= 0) drawTile(x-1, y, side);

   // [-][-][x][-] <- Columna y+1
   if(y+1 < G_mapHTiles) {
      drawTile(x, y+1, side);
      if(x+1 < G_mapWTiles) drawTile(x+1, y+1, side);
      if(x-1 >= 0) drawTile(x-1, y+1, side);
   }

   // [-][-][-][x] <- Columna y+2
   if(y+2 < G_mapHTiles) {
      drawTile(x, y+2, side);
      if(x+1 < G_mapWTiles) drawTile(x+1, y+2, side);
      if(x-1 >= 0) drawTile(x-1, y+2, side);
   }
}

// Dibuja el mapa completo (Solo debe llamarse al principio de cada nivel)
void drawMap() {
   u8 x, y;

   for(y=0; y<G_mapHTiles; y++) {
      for(x=0; x<G_mapWTiles; x++) {
         drawTile(x, y, G_left);
         drawTile(x, y, G_right);
      }
   }
}

// Intercambia los buffers
void swapBuffers(u8** scrbuffers) {
   u8* aux; // Auxiliary pointer for making the change
   
   // Change what is shown on the screen (present backbuffer (1) is changed to 
   // front-buffer, so it is shown at the screen)
   // cpct_setVideoMemoryPage requires the 6 Most Significant bits of the address,
   // so we have to shift them 10 times to the right (as addresses have 16 bits)
   //
   cpct_setVideoMemoryPage( (u16)(scrbuffers[1]) >> 10 );
   
   // Once backbuffer is being shown at the screen, we switch our two 
   // variables to start using (0) as backbuffer and (1) as front-buffer
   aux = scrbuffers[0];
   scrbuffers[0] = scrbuffers[1];
   scrbuffers[1] = aux;
}

// Dibuja el HUD
void drawHUD() {
   drawHUDBorder();
   drawHearts();
}

// DIBUJAR CORAZONES
void drawHearts() {
   u8* pvideomem1, pvideomem2, pvideomem3;
   
   pvideomem1 = cpct_getScreenPtr(g_scrbuffers[1], 12, 8);
   pvideomem2 = cpct_getScreenPtr(g_scrbuffers[1], 16, 8);
   pvideomem3 = cpct_getScreenPtr(g_scrbuffers[1], 20, 8);

   //HEROE 1
   switch(heroe1.health) {
      case 6:
         cpct_drawTileAligned4x8_f(G_heartR_full, pvideomem1);
         cpct_drawTileAligned4x8_f(G_heartR_full, pvideomem2); 
         cpct_drawTileAligned4x8_f(G_heartR_full, pvideomem3);
      break;
      case 5:
         cpct_drawTileAligned4x8_f(G_heartR_full, pvideomem1);
         cpct_drawTileAligned4x8_f(G_heartR_full, pvideomem2);
         cpct_drawTileAligned4x8_f(G_heartR_half, pvideomem3);
      break;
      case 4: 
         cpct_drawTileAligned4x8_f(G_heartR_full, pvideomem1);
         cpct_drawTileAligned4x8_f(G_heartR_full, pvideomem2);
         cpct_drawTileAligned4x8_f(G_heart_empty, pvideomem3);
      break;
      case 3:
         cpct_drawTileAligned4x8_f(G_heartR_full, pvideomem1);
         cpct_drawTileAligned4x8_f(G_heartR_half, pvideomem2);
         cpct_drawTileAligned4x8_f(G_heart_empty, pvideomem3);
      break;
      case 2:
         cpct_drawTileAligned4x8_f(G_heartR_full, pvideomem1);
         cpct_drawTileAligned4x8_f(G_heart_empty, pvideomem2);
         cpct_drawTileAligned4x8_f(G_heart_empty, pvideomem3);
      break;
      case 1:
         cpct_drawTileAligned4x8_f(G_heartR_half, pvideomem1);
         cpct_drawTileAligned4x8_f(G_heart_empty, pvideomem2);
         cpct_drawTileAligned4x8_f(G_heart_empty, pvideomem3);
      break;
      case 0:
         cpct_drawTileAligned4x8_f(G_heart_empty, pvideomem1);
         cpct_drawTileAligned4x8_f(G_heart_empty, pvideomem2);
         cpct_drawTileAligned4x8_f(G_heart_empty, pvideomem3);
      break;
   }

   pvideomem1 = cpct_getScreenPtr(g_scrbuffers[1], 64, 8);
   pvideomem2 = cpct_getScreenPtr(g_scrbuffers[1], 60, 8);
   pvideomem3 = cpct_getScreenPtr(g_scrbuffers[1], 56, 8);

   //HEROE 2
   switch(heroe2.health) {
      case 6:
         cpct_drawTileAligned4x8_f(G_heartB_full, pvideomem);
         cpct_drawTileAligned4x8_f(G_heartB_full, pvideomem);
         cpct_drawTileAligned4x8_f(G_heartB_full, pvideomem);
      break;
      case 5:
         cpct_drawTileAligned4x8_f(G_heartB_full, pvideomem);
         cpct_drawTileAligned4x8_f(G_heartB_full, pvideomem);
         cpct_drawTileAligned4x8_f(G_heartB_half, pvideomem);
      break;
      case 4:
         cpct_drawTileAligned4x8_f(G_heartB_full, pvideomem);
         cpct_drawTileAligned4x8_f(G_heartB_full, pvideomem);
         cpct_drawTileAligned4x8_f(G_heart_empty, pvideomem);
      break;
      case 3:
         cpct_drawTileAligned4x8_f(G_heartB_full, pvideomem);
         cpct_drawTileAligned4x8_f(G_heartB_half, pvideomem);
         cpct_drawTileAligned4x8_f(G_heart_empty, pvideomem);
      break;
      case 2:
         cpct_drawTileAligned4x8_f(G_heartB_full, pvideomem);
         cpct_drawTileAligned4x8_f(G_heart_empty, pvideomem);
         cpct_drawTileAligned4x8_f(G_heart_empty, pvideomem);
      break;
      case 1:
         cpct_drawTileAligned4x8_f(G_heartB_half, pvideomem);
         cpct_drawTileAligned4x8_f(G_heart_empty, pvideomem);
         cpct_drawTileAligned4x8_f(G_heart_empty, pvideomem);
      break;
      case 0:
         cpct_drawTileAligned4x8_f(G_heart_empty, pvideomem);
         cpct_drawTileAligned4x8_f(G_heart_empty, pvideomem);
         cpct_drawTileAligned4x8_f(G_heart_empty, pvideomem);
      break;
   }
}

// DIBUJAR EL BORDE DEL HUD
void drawHUDBorder() {
   u8* pvideomem;
   u8 i;

   //Marco del HUD
   pvideomem = cpct_getScreenPtr(g_scrbuffers[1], 0, 0);
   cpct_drawTileAligned4x8_f(G_border01, pvideomem); 

   pvideomem = cpct_getScreenPtr(g_scrbuffers[1], 0, 8);
   cpct_drawTileAligned4x8_f(G_border11, pvideomem); 
   pvideomem = cpct_getScreenPtr(g_scrbuffers[1], 0, 16);
   cpct_drawTileAligned4x8_f(G_border11, pvideomem); 

   pvideomem = cpct_getScreenPtr(g_scrbuffers[1], 0, 24);
   cpct_drawTileAligned4x8_f(G_border10, pvideomem);    

   for(i = 0; i < 7; i++) {
      pvideomem = cpct_getScreenPtr(g_scrbuffers[1], i*4+4, 0);
      cpct_drawSprite(G_border02, pvideomem, 4, 8); 

      pvideomem = cpct_getScreenPtr(g_scrbuffers[1], i*4+4, 24);
      cpct_drawSprite(G_border09, pvideomem, 4, 8); 

      pvideomem = cpct_getScreenPtr(g_scrbuffers[1], i*4+48, 0);
      cpct_drawSprite(G_border02, pvideomem, 4, 8); 

      pvideomem = cpct_getScreenPtr(g_scrbuffers[1], i*4+48, 24);
      cpct_drawSprite(G_border09, pvideomem, 4, 8); 
   }

   pvideomem = cpct_getScreenPtr(g_scrbuffers[1], 32, 0);
   cpct_drawTileAligned4x8_f(G_border03, pvideomem); 
   pvideomem = cpct_getScreenPtr(g_scrbuffers[1], 36, 0);
   cpct_drawTileAligned4x8_f(G_border04, pvideomem); 
   pvideomem = cpct_getScreenPtr(g_scrbuffers[1], 32, 8);
   cpct_drawTileAligned4x8_f(G_border05, pvideomem); 
   pvideomem = cpct_getScreenPtr(g_scrbuffers[1], 36, 8);
   cpct_drawTileAligned4x8_f(G_border06, pvideomem); 
   pvideomem = cpct_getScreenPtr(g_scrbuffers[1], 36, 16);
   cpct_drawTileAligned4x8_f(G_border07, pvideomem);
   pvideomem = cpct_getScreenPtr(g_scrbuffers[1], 32, 24);
   cpct_drawTileAligned4x8_f(G_border09, pvideomem);
   pvideomem = cpct_getScreenPtr(g_scrbuffers[1], 36, 24);
   cpct_drawTileAligned4x8_f(G_border08, pvideomem);

   pvideomem = cpct_getScreenPtr(g_scrbuffers[1], 40, 0);
   cpct_drawTileAligned4x8_f(G_border12, pvideomem);
   pvideomem = cpct_getScreenPtr(g_scrbuffers[1], 44, 0);
   cpct_drawTileAligned4x8_f(G_border13, pvideomem);
   pvideomem = cpct_getScreenPtr(g_scrbuffers[1], 44, 8);
   cpct_drawTileAligned4x8_f(G_border14, pvideomem);
   pvideomem = cpct_getScreenPtr(g_scrbuffers[1], 40, 8);
   cpct_drawTileAligned4x8_f(G_border15, pvideomem);
   pvideomem = cpct_getScreenPtr(g_scrbuffers[1], 76, 0);
   cpct_drawTileAligned4x8_f(G_border16, pvideomem);
   pvideomem = cpct_getScreenPtr(g_scrbuffers[1], 76, 24);
   cpct_drawTileAligned4x8_f(G_border17, pvideomem);
   pvideomem = cpct_getScreenPtr(g_scrbuffers[1], 44, 24); 
   cpct_drawTileAligned4x8_f(G_border09, pvideomem);
   pvideomem = cpct_getScreenPtr(g_scrbuffers[1], 40, 24); 
   cpct_drawTileAligned4x8_f(G_border20, pvideomem);
   pvideomem = cpct_getScreenPtr(g_scrbuffers[1], 40, 16); 
   cpct_drawTileAligned4x8_f(G_border18, pvideomem);
   pvideomem = cpct_getScreenPtr(g_scrbuffers[1], 76, 8); 
   cpct_drawTileAligned4x8_f(G_border19, pvideomem);
   pvideomem = cpct_getScreenPtr(g_scrbuffers[1], 76, 16); 
   cpct_drawTileAligned4x8_f(G_border19, pvideomem);
}