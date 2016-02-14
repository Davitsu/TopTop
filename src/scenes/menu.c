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
#include "menu.h"
#include "../sprites/sprites.h"
#include "../constants.h"
#include "../audio/audio.h"

u8* const g_scrbuffersMenu[2] = { (u8*)0xC000, (u8*)0x8000 }; // Direccion de los dos buffers

u8 future;
u8 spaceDown;

// Inicializa el menu
void initMenu() {
  ////cpct_akp_musicInit(G_toptop_music); 
  ////cpct_akp_SFXInit(G_toptop_effects);

  future = 0;
  spaceDown = 0;

	// Preparamos el double buffer y dibujamos...
	cpct_memset_f64(g_scrbuffersMenu[1], 0x00, 0x4000); // Limpiamos el segundo buffer (contiene valores aleatorios)
  drawMenu();                        	                // Dibujamos en el buffer actual
  cpct_waitVSYNC();                               	  // Volvemos a esperar al VSYNC
	swapBuffersMenu(g_scrbuffersMenu);             	 	  // Cambiamos de buffer
  cpct_memset_f64(g_scrbuffersMenu[1], 0x00, 0x4000);     // Limpiamos el primer buffer
  drawMenu();                                     	  // Dibujamos en este buffer
}

// Update del menu
u8 updateMenu() { 
	cpct_waitVSYNC();

  // Reproduce musica (1 vez cada frame)
  ////cpct_akp_musicPlay(); 

  // Scan Keyboard
  cpct_scanKeyboard();

  if (cpct_isKeyPressed(Key_Space)) {
    if(spaceDown == 0) {
      spaceDown = 1;
      if(future == 0) {
        future = 1;
        ////cpct_akp_SFXPlay(6, 15, 65, 0, 0, AY_CHANNEL_A); 
        drawMenuHeroesFuture();
        cpct_waitVSYNC();
        cpct_akp_musicPlay(); 
        swapBuffersMenu(g_scrbuffersMenu);
        drawMenuHeroesFuture();
      }
      else {
        future = 0;
        ////cpct_akp_SFXPlay(6, 15, 65, 0, 0, AY_CHANNEL_A);
        drawMenuHeroes();
        cpct_waitVSYNC();
        cpct_akp_musicPlay(); 
        swapBuffersMenu(g_scrbuffersMenu);
        drawMenuHeroes();
      }
    }
  }
  else {
    spaceDown = 0;
  }

  swapBuffersMenu(g_scrbuffersMenu);                  // Cambiamos de buffer

  if (cpct_isKeyPressed(Key_1) || cpct_isKeyPressed(Key_Enter) || cpct_isKeyPressed(Key_Return)) {
    ////cpct_akp_SFXPlay(6, 15, 65, 0, 0, AY_CHANNEL_A);
    return G_sceneGame;
  }

  return G_sceneMenu;
}

void drawMenu() {
	drawMenuBorder();
  drawLogo();
}

/*void drawCredits() {
  u8 *pvideomem;

  drawMenuBorder();
  pvideomem = cpct_getScreenPtr(g_scrbuffersMenu[1], 26, 115);  
  cpct_drawStringM0("CREDITOS", pvideomem, 3, 0);
}*/

void drawLogo() {
  // TOPTOP LOGO
  drawTop(8, 16);
  drawTop(28, 56);

  drawOptions();
  drawMenuHeroes();
}

void drawTop(u8 x, u8 y) {
  drawTopTile(x, y);
  drawTopTile(x + 4, y);
  drawTopTile(x + 8, y);
  drawTopTile(x + 4, y + 8);
  drawTopTile(x + 4, y + 16);
  drawTopTile(x + 4, y + 24);
  //O
  drawTopTile(x + 16, y);
  drawTopTile(x + 20, y);
  drawTopTile(x + 24, y);
  drawTopTile(x + 16, y + 8);
  drawTopTile(x + 16, y + 16);
  drawTopTile(x + 16, y + 24);
  drawTopTile(x + 20, y + 24);
  drawTopTile(x + 24, y + 24);
  drawTopTile(x + 24, y + 16);
  drawTopTile(x + 24, y + 8);
  //P
  drawTopTile(x + 32, y);
  drawTopTile(x + 36, y);
  drawTopTile(x + 40, y);
  drawTopTile(x + 32, y + 8);
  drawTopTile(x + 32, y + 16);
  drawTopTile(x + 32, y + 24);
  drawTopTile(x + 40, y + 8);
  drawTopTile(x + 40, y + 16);
  drawTopTile(x + 36, y + 16);
}

void drawTopTile(u8 x, u8 y) {
  u8 *pvideomem = 0;

  pvideomem = cpct_getScreenPtr(g_scrbuffersMenu[1], x, y);
  cpct_drawTileAligned4x8(G_tile01, pvideomem);
}

void drawMenuBorder() {
 	u8 i;

 	drawMenuBorderTile(0, 0, G_border01);
 	drawMenuBorderTile(76, 0, G_border16);
 	drawMenuBorderTile(76, 192, G_border17);
 	drawMenuBorderTile(0, 192, G_border10);

  for(i = 0; i < 18; i++) {
    drawMenuBorderSprite(i*4+4, 0, G_border02);
    drawMenuBorderSprite(i*4+4, 192, G_border09); 
  }

  for(i = 0; i < 23; i++) {
    drawMenuBorderSprite(0, i*8+8, G_border11);
    drawMenuBorderSprite(76, i*8+8, G_border19);
  }
}	

void drawMenuBorderTile(u8 x, u8 y, u8 *spriteBorder) {
  u8 *pvideomem = 0;

  pvideomem = cpct_getScreenPtr(g_scrbuffersMenu[1], x, y);
  cpct_drawTileAligned4x8(spriteBorder, pvideomem);
}

void drawMenuBorderSprite(u8 x, u8 y, u8 *spriteBorder) {
  u8 *pvideomem;

  pvideomem = cpct_getScreenPtr(g_scrbuffersMenu[1], x, y);
  cpct_drawSprite(spriteBorder, pvideomem, 4, 8);
}

void drawOptions() {
  u8 *pvideomem = 0;

  pvideomem = cpct_getScreenPtr(g_scrbuffersMenu[1], 12, 105);  
  cpct_drawStringM0("OOOOOOOOOOOOOO", pvideomem, 1, 0);
  pvideomem = cpct_getScreenPtr(g_scrbuffersMenu[1], 12, 140);  
  cpct_drawStringM0("OOOOOOOOOOOOOO", pvideomem, 1, 0);

  // Dibujar opciones
  /*pvideomem = cpct_getScreenPtr(g_scrbuffersMenu[1], 26, 123); 
  cpct_drawStringM0("1.JUGAR", pvideomem, 3, 0);*/
  /*pvideomem = cpct_getScreenPtr(g_scrbuffersMenu[1], 20, 130);  
  cpct_drawStringM0("2.CREDITOS", pvideomem, 1, 0);*/

  pvideomem = cpct_getScreenPtr(g_scrbuffersMenu[1], 14, 182);
  cpct_drawStringM0("RANTAN   2015", pvideomem, 6, 0);

  // logo Rantan
  pvideomem = cpct_getScreenPtr(g_scrbuffersMenu[1], 42, 181);
  cpct_drawSprite(G_logoRantan, pvideomem, 4, 8);
}

void drawMenuHeroes() {
  u8 *pvideomem = 0;

  //PERSONAJES
  //Se dibuja el sprite del personaje 1
  pvideomem = cpct_getScreenPtr(g_scrbuffersMenu[1], 34, 156);
  cpct_drawSpriteMasked(G_heroR_idle_right01, pvideomem, G_heroeW, 12);

  //Se dibuja el sprite del personaje 2
  pvideomem = cpct_getScreenPtr(g_scrbuffersMenu[1], 42, 156);
  cpct_drawSpriteMasked(G_heroB_idle_left01, pvideomem, G_heroeW, 12);

  pvideomem = cpct_getScreenPtr(g_scrbuffersMenu[1], 2, 123); 
  cpct_drawStringM0("      1.JUGAR      ", pvideomem, 3, 0);
}

void drawMenuHeroesFuture() {
  u8 *pvideomem = 0;

  //PERSONAJES
  //Se dibuja el sprite del personaje 1
  pvideomem = cpct_getScreenPtr(g_scrbuffersMenu[1], 34, 157);
  cpct_drawSprite(G_future1, pvideomem, G_heroeW, 11);

  //Se dibuja el sprite del personaje 2
  pvideomem = cpct_getScreenPtr(g_scrbuffersMenu[1], 42, 157);
  cpct_drawSprite(G_future2, pvideomem, G_heroeW, 11);

  cpct_waitVSYNC();

  // Reproduce musica (1 vez cada frame)
  ////cpct_akp_musicPlay(); 

  pvideomem = cpct_getScreenPtr(g_scrbuffersMenu[1], 2, 123); 
  cpct_drawStringM0("1.REGRESA AL FUTURO", pvideomem, 3, 0);

  cpct_waitVSYNC();

  // Reproduce musica (1 vez cada frame)
  ////cpct_akp_musicPlay(); 
}

void swapBuffersMenu(u8** scrbuffers) {
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