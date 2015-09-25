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

//Sprite del jugador
struct Heroe {
  u8 x, y, preX, preY, health;
};

struct Heroe heroe1;
struct Heroe heroe2;

// Inicializa el menu
void initGame() {
	drawGameBorder();
   createHeroes();
}

// Update del menu
u8 updateGame() {
   u8 alive = 1;

   while(alive) {
      updatePlayers();
      cpct_waitVSYNC();             // Wait for VSYNC and...
      drawHeroes();
   }
	return G_sceneGame;
}

// Crea a los personajes
void createHeroes() {
   heroe1.x = 28;
   heroe1.y = 180;

   heroe2.x = 48;
   heroe2.y = 180;
}

// Dibuja los personajes
void drawHeroes() {
   u8* pvideomem;
   u8 c;

   c = cpct_px2byteM0(0,0);  // Colour pattern 8-8 (black-black)

   pvideomem = cpct_getScreenPtr((u8*)0xC000, heroe1.x, heroe1.y);
   cpct_drawSpriteMasked(G_heroR_idle01, pvideomem, 4, 12); 

   //pvideomem = cpct_getScreenPtr((u8*)0xC000, heroe1.x+4, heroe1.y);
   //cpct_drawSolidBox(pvideomem, c, 4, 12);

   pvideomem = cpct_getScreenPtr((u8*)0xC000, heroe2.x, heroe2.y);
   cpct_drawSprite(G_heroB_idle01, pvideomem, 4, 12);
}

void updatePlayers() {
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
      //estado idle
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