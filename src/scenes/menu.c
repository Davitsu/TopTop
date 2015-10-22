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
#include "../sprites/animation.h"
#include "../constants.h"
#include "../audio/audio.h"

extern u8* const G_SCR_VMEM_MENU = (u8*)0xC000; 

u8* const g_scrbuffersMenu[2] = { (u8*)0xC000, (u8*)0x8000 }; // Direccion de los dos buffers

//TAnimation anim;

// Inicializa el menu
void initMenu(u8 menu) {
  cpct_akp_musicInit(G_toptop_effects); 
  cpct_akp_SFXInit(G_toptop_effects);

	drawMenuBorder();

  //anim.frames = (TAnimFrames**)g_aniHeroeR[0][G_left];

	// Preparamos el double buffer y dibujamos...
	cpct_memset_f64(g_scrbuffersMenu[1], 0x00, 0x4000); // Limpiamos el segundo buffer (contiene valores aleatorios)
	cpct_waitVSYNC();                               	  // Esperamos al VSYNC para esperar a dibujar
	if(menu == 0) drawMenu();                        	  // Dibujamos en el buffer actual
	else drawCredits();
  cpct_waitVSYNC();                               	  // Volvemos a esperar al VSYNC
	swapBuffersMenu(g_scrbuffersMenu);             	 	  // Cambiamos de buffer
	if(menu == 0) drawMenu();                        	  // Dibujamos en este buffer
  else drawCredits();
}

// Update del menu
u8 updateMenu(u8 menu) { 

	cpct_waitVSYNC();

  // Reproduce musica (1 vez cada frame)
  cpct_akp_musicPlay(); 

  cpct_waitVSYNC(); // ---------- Comienza Segundo Frame (para redibujar elementos, 1 vez cada 2 frames)
   
  // Reproduce musica (1 vez cada frame)
  cpct_akp_musicPlay(); // La musica se reproduce cada frame 

	swapBuffersMenu(g_scrbuffersMenu);

  // Scan Keyboard
  cpct_scanKeyboard_f();

  if(menu == 0) {                     //Escena menu
    if (cpct_isKeyPressed(Key_1)) {
      //SFX
      cpct_akp_SFXPlay(6, 15, 65, 0, 0, AY_CHANNEL_B);
      return G_sceneGame;
    }
    else if(cpct_isKeyPressed(Key_2)) {
      //SFX
      cpct_akp_SFXPlay(6, 15, 65, 0, 0, AY_CHANNEL_B);
      return G_sceneCredits;
    }
  }
  else {                              //Escena de creditos
    if (cpct_isKeyPressed(Key_5)) {
      return G_sceneMenu;
    }
    return G_sceneCredits;
  }
}

void drawMenu() {
	u8 *pvideomem;
  //u8 i;

	drawMenuBorder();
  drawLogo();

  // Dibujar opciones
  pvideomem = cpct_getScreenPtr(g_scrbuffersMenu[1], 26, 115);  
  cpct_drawStringM0("1.JUGAR", pvideomem, 3, 0);
  pvideomem = cpct_getScreenPtr(g_scrbuffersMenu[1], 20, 130);  
  cpct_drawStringM0("2.CREDITOS", pvideomem, 1, 0);

  pvideomem = cpct_getScreenPtr(g_scrbuffersMenu[1], 14, 182);
  cpct_drawStringM0("RANTAN   2015", pvideomem, 6, 0);

  // logo Rantan
  pvideomem = cpct_getScreenPtr(g_scrbuffersMenu[1], 42, 181);
  cpct_drawSprite(G_logoRantan, pvideomem, 4, 8);

  //PERSONAJES
  //Se dibuja el sprite del personaje 1
  pvideomem = cpct_getScreenPtr(g_scrbuffersMenu[1], 34, 155);
  cpct_drawSpriteMasked(G_heroR_idle_right01, pvideomem, G_heroeW, G_heroeH);

  //Se dibuja el sprite del personaje 2
  pvideomem = cpct_getScreenPtr(g_scrbuffersMenu[1], 42, 155);
  cpct_drawSpriteMasked(G_heroB_idle_left01, pvideomem, G_heroeW, G_heroeH);
}

void drawCredits() {
  u8 *pvideomem;

  drawMenuBorder();
  pvideomem = cpct_getScreenPtr(g_scrbuffersMenu[1], 26, 115);  
  cpct_drawStringM0("CREDITOS", pvideomem, 3, 0);

}

void drawLogo() {
  u8 *pvideomem;
  // TOPTOP LOGO
  //T
  pvideomem = cpct_getScreenPtr(g_scrbuffersMenu[1], 8, 16);
  cpct_drawTileAligned4x8(G_tile01, pvideomem);
  pvideomem = cpct_getScreenPtr(g_scrbuffersMenu[1], 12, 16);
  cpct_drawTileAligned4x8(G_tile01, pvideomem);
  pvideomem = cpct_getScreenPtr(g_scrbuffersMenu[1], 16, 16);
  cpct_drawTileAligned4x8(G_tile01, pvideomem);
  pvideomem = cpct_getScreenPtr(g_scrbuffersMenu[1], 12, 24);
  cpct_drawTileAligned4x8(G_tile01, pvideomem);
  pvideomem = cpct_getScreenPtr(g_scrbuffersMenu[1], 12, 32);
  cpct_drawTileAligned4x8(G_tile01, pvideomem);
  pvideomem = cpct_getScreenPtr(g_scrbuffersMenu[1], 12, 40);
  cpct_drawTileAligned4x8(G_tile01, pvideomem);
  //O
  pvideomem = cpct_getScreenPtr(g_scrbuffersMenu[1], 24, 16);
  cpct_drawTileAligned4x8(G_tile01, pvideomem);
  pvideomem = cpct_getScreenPtr(g_scrbuffersMenu[1], 28, 16);
  cpct_drawTileAligned4x8(G_tile01, pvideomem);
  pvideomem = cpct_getScreenPtr(g_scrbuffersMenu[1], 32, 16);
  cpct_drawTileAligned4x8(G_tile01, pvideomem);
  pvideomem = cpct_getScreenPtr(g_scrbuffersMenu[1], 24, 24);
  cpct_drawTileAligned4x8(G_tile01, pvideomem);
  pvideomem = cpct_getScreenPtr(g_scrbuffersMenu[1], 24, 32);
  cpct_drawTileAligned4x8(G_tile01, pvideomem);
  pvideomem = cpct_getScreenPtr(g_scrbuffersMenu[1], 24, 40);
  cpct_drawTileAligned4x8(G_tile01, pvideomem);
  pvideomem = cpct_getScreenPtr(g_scrbuffersMenu[1], 28, 40);
  cpct_drawTileAligned4x8(G_tile01, pvideomem);
  pvideomem = cpct_getScreenPtr(g_scrbuffersMenu[1], 32, 40);
  cpct_drawTileAligned4x8(G_tile01, pvideomem);
  pvideomem = cpct_getScreenPtr(g_scrbuffersMenu[1], 32, 32);
  cpct_drawTileAligned4x8(G_tile01, pvideomem);
  pvideomem = cpct_getScreenPtr(g_scrbuffersMenu[1], 32, 24);
  cpct_drawTileAligned4x8(G_tile01, pvideomem);
  //P
  pvideomem = cpct_getScreenPtr(g_scrbuffersMenu[1], 40, 16);
  cpct_drawTileAligned4x8(G_tile01, pvideomem);
  pvideomem = cpct_getScreenPtr(g_scrbuffersMenu[1], 44, 16);
  cpct_drawTileAligned4x8(G_tile01, pvideomem);
  pvideomem = cpct_getScreenPtr(g_scrbuffersMenu[1], 48, 16);
  cpct_drawTileAligned4x8(G_tile01, pvideomem);
  pvideomem = cpct_getScreenPtr(g_scrbuffersMenu[1], 40, 24);
  cpct_drawTileAligned4x8(G_tile01, pvideomem);
  pvideomem = cpct_getScreenPtr(g_scrbuffersMenu[1], 40, 32);
  cpct_drawTileAligned4x8(G_tile01, pvideomem);
  pvideomem = cpct_getScreenPtr(g_scrbuffersMenu[1], 40, 40);
  cpct_drawTileAligned4x8(G_tile01, pvideomem);
  pvideomem = cpct_getScreenPtr(g_scrbuffersMenu[1], 48, 24);
  cpct_drawTileAligned4x8(G_tile01, pvideomem);
  pvideomem = cpct_getScreenPtr(g_scrbuffersMenu[1], 48, 32);
  cpct_drawTileAligned4x8(G_tile01, pvideomem);
  pvideomem = cpct_getScreenPtr(g_scrbuffersMenu[1], 44, 32);
  cpct_drawTileAligned4x8(G_tile01, pvideomem);

  //T
  pvideomem = cpct_getScreenPtr(g_scrbuffersMenu[1], 28, 56);
  cpct_drawTileAligned4x8(G_tile01, pvideomem);
  pvideomem = cpct_getScreenPtr(g_scrbuffersMenu[1], 32, 56);
  cpct_drawTileAligned4x8(G_tile01, pvideomem);
  pvideomem = cpct_getScreenPtr(g_scrbuffersMenu[1], 36, 56);
  cpct_drawTileAligned4x8(G_tile01, pvideomem);
  pvideomem = cpct_getScreenPtr(g_scrbuffersMenu[1], 32, 64);
  cpct_drawTileAligned4x8(G_tile01, pvideomem);
  pvideomem = cpct_getScreenPtr(g_scrbuffersMenu[1], 32, 72);
  cpct_drawTileAligned4x8(G_tile01, pvideomem);
  pvideomem = cpct_getScreenPtr(g_scrbuffersMenu[1], 32, 80);
  cpct_drawTileAligned4x8(G_tile01, pvideomem);
  //O
  pvideomem = cpct_getScreenPtr(g_scrbuffersMenu[1], 44, 56);
  cpct_drawTileAligned4x8(G_tile01, pvideomem);
  pvideomem = cpct_getScreenPtr(g_scrbuffersMenu[1], 48, 56);
  cpct_drawTileAligned4x8(G_tile01, pvideomem);
  pvideomem = cpct_getScreenPtr(g_scrbuffersMenu[1], 52, 56);
  cpct_drawTileAligned4x8(G_tile01, pvideomem);
  pvideomem = cpct_getScreenPtr(g_scrbuffersMenu[1], 44, 64);
  cpct_drawTileAligned4x8(G_tile01, pvideomem);
  pvideomem = cpct_getScreenPtr(g_scrbuffersMenu[1], 44, 72);
  cpct_drawTileAligned4x8(G_tile01, pvideomem);
  pvideomem = cpct_getScreenPtr(g_scrbuffersMenu[1], 44, 80);
  cpct_drawTileAligned4x8(G_tile01, pvideomem);
  pvideomem = cpct_getScreenPtr(g_scrbuffersMenu[1], 48, 80);
  cpct_drawTileAligned4x8(G_tile01, pvideomem);
  pvideomem = cpct_getScreenPtr(g_scrbuffersMenu[1], 52, 80);
  cpct_drawTileAligned4x8(G_tile01, pvideomem);
  pvideomem = cpct_getScreenPtr(g_scrbuffersMenu[1], 52, 72);
  cpct_drawTileAligned4x8(G_tile01, pvideomem);
  pvideomem = cpct_getScreenPtr(g_scrbuffersMenu[1], 52, 64);
  cpct_drawTileAligned4x8(G_tile01, pvideomem);
  //P
  pvideomem = cpct_getScreenPtr(g_scrbuffersMenu[1], 60, 56);
  cpct_drawTileAligned4x8(G_tile01, pvideomem);
  pvideomem = cpct_getScreenPtr(g_scrbuffersMenu[1], 64, 56);
  cpct_drawTileAligned4x8(G_tile01, pvideomem);
  pvideomem = cpct_getScreenPtr(g_scrbuffersMenu[1], 68, 56);
  cpct_drawTileAligned4x8(G_tile01, pvideomem);
  pvideomem = cpct_getScreenPtr(g_scrbuffersMenu[1], 60, 64);
  cpct_drawTileAligned4x8(G_tile01, pvideomem);
  pvideomem = cpct_getScreenPtr(g_scrbuffersMenu[1], 60, 72);
  cpct_drawTileAligned4x8(G_tile01, pvideomem);
  pvideomem = cpct_getScreenPtr(g_scrbuffersMenu[1], 60, 80);
  cpct_drawTileAligned4x8(G_tile01, pvideomem);
  pvideomem = cpct_getScreenPtr(g_scrbuffersMenu[1], 68, 64);
  cpct_drawTileAligned4x8(G_tile01, pvideomem);
  pvideomem = cpct_getScreenPtr(g_scrbuffersMenu[1], 68, 72);
  cpct_drawTileAligned4x8(G_tile01, pvideomem);
  pvideomem = cpct_getScreenPtr(g_scrbuffersMenu[1], 64, 72);
  cpct_drawTileAligned4x8(G_tile01, pvideomem);
}

void drawMenuBorder() {
	u8* pvideomem;
  u8 i;

  pvideomem = cpct_getScreenPtr(g_scrbuffersMenu[1], 0, 0);
  cpct_drawTileAligned4x8_f(G_border01, pvideomem); 

  pvideomem = cpct_getScreenPtr(g_scrbuffersMenu[1], 76, 0);
  cpct_drawTileAligned4x8_f(G_border16, pvideomem); 

  pvideomem = cpct_getScreenPtr(g_scrbuffersMenu[1], 76, 192);
  cpct_drawTileAligned4x8_f(G_border17, pvideomem); 

  pvideomem = cpct_getScreenPtr(g_scrbuffersMenu[1], 0, 192);
  cpct_drawTileAligned4x8_f(G_border10, pvideomem); 

  for(i = 0; i < 18; i++) {
    pvideomem = cpct_getScreenPtr(g_scrbuffersMenu[1], i*4+4, 0);
    cpct_drawSprite(G_border02, pvideomem, 4, 8); 

    pvideomem = cpct_getScreenPtr(g_scrbuffersMenu[1], i*4+4, 192);
    cpct_drawSprite(G_border09, pvideomem, 4, 8);  
  }

  for(i = 0; i < 23; i++) {
    pvideomem = cpct_getScreenPtr(g_scrbuffersMenu[1], 0, i*8+8);
    cpct_drawSprite(G_border11, pvideomem, 4, 8); 

    pvideomem = cpct_getScreenPtr(g_scrbuffersMenu[1], 76, i*8+8);
    cpct_drawSprite(G_border19, pvideomem, 4, 8);  
  }
}	

// Intercambia los buffers
void swapBuffersMenu(u8** scrbuffersMenu) {
   u8* aux; // Auxiliary pointer for making the change
   
   // Change what is shown on the screen (present backbuffer (1) is changed to 
   // front-buffer, so it is shown at the screen)
   // cpct_setVideoMemoryPage requires the 6 Most Significant bits of the address,
   // so we have to shift them 10 times to the right (as addresses have 16 bits)
   //
   cpct_setVideoMemoryPage( (u16)(scrbuffersMenu[1]) >> 10 );
   
   // Once backbuffer is being shown at the screen, we switch our two 
   // variables to start using (0) as backbuffer and (1) as front-buffer
   aux = scrbuffersMenu[0];
   scrbuffersMenu[0] = scrbuffersMenu[1];
   scrbuffersMenu[1] = aux;
}