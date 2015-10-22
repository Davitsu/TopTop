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
#include "screens.h"
#include "../sprites/sprites.h"
#include "../sprites/animation.h"
#include "../constants.h"
#include "../audio/audio.h"

extern u8* const G_SCR_VMEM_SCREENS = (u8*)0xC000; 

u8* const scrbuffersScreens[2] = { (u8*)0xC000, (u8*)0x8000 }; // Direccion de los dos buffers

// Inicializa las pantallas
void initScreens(u8 screen) {
	drawScreensBorder();

	// Preparamos el double buffer y dibujamos...
	cpct_memset_f64(scrbuffersScreens[1], 0x00, 0x4000); // Limpiamos el segundo buffer (contiene valores aleatorios)
	cpct_waitVSYNC();                               	 // Esperamos al VSYNC para esperar a dibujar
	if(screen == 0) drawGameOver();                      // Dibujamos en el buffer actual
	//else if(screen == 1) drawNextLevel();
	//else if(screen == 2) drawGameComplete();
	cpct_waitVSYNC();                               	 // Volvemos a esperar al VSYNC
	swapBuffersScreens(scrbuffersScreens);             	 // Cambiamos de buffer
	cpct_memset_f64(scrbuffersScreens[1], 0x00, 0x4000); // Limpiamos el primer buffer
	if(screen == 0) drawGameOver();                   	 // Dibujamos en este buffer
	//else if(screen == 1) drawNextLevel();
	//else if(screen == 2) drawGameComplete();
}

// Update de las pantallas
u8 updateScreens(u8 screen) { 
	cpct_waitVSYNC();
	
	// Reproduce musica (1 vez cada frame)
    cpct_akp_musicPlay(); 

    cpct_waitVSYNC(); // ---------- Comienza Segundo Frame (para redibujar elementos, 1 vez cada 2 frames)
   
    // Reproduce musica (1 vez cada frame)
    cpct_akp_musicPlay(); // La musica se reproduce cada frame 

	swapBuffersScreens(scrbuffersScreens);

	// Scan Keyboard
	cpct_scanKeyboard_f();

	if(cpct_isKeyPressed(Key_1)) {
		//SFX
		cpct_akp_SFXPlay(6, 15, 65, 0, 0, AY_CHANNEL_B);
		if(screen == 0 || screen == 2) return G_sceneGame;
		//else if(screen == 1) 
	}
	else if(cpct_isKeyPressed(Key_2)) {
		//SFX
		cpct_akp_SFXPlay(6, 15, 65, 0, 0, AY_CHANNEL_B);
		if(screen == 0 || screen == 2) return G_sceneMenu;
	}
	else {
		return G_sceneGameOver;
	}
}

void drawGameOver() {
	u8 *pvideomem;

	drawScreensBorder();

	pvideomem = cpct_getScreenPtr(scrbuffersScreens[1], 26, 115);  
  	cpct_drawStringM0("1.REINTENTAR", pvideomem, 3, 0);
  	pvideomem = cpct_getScreenPtr(scrbuffersScreens[1], 20, 130);  
  	cpct_drawStringM0("2.IR AL MENU", pvideomem, 1, 0);
}

/*void drawNextLevel() {
	u8 *pvideomem;

	drawScreensBorder();

	pvideomem = cpct_getScreenPtr(scrbuffersScreens[1], 26, 115);  
  	cpct_drawStringM0("1.CONTINUAR", pvideomem, 3, 0);
  	pvideomem = cpct_getScreenPtr(scrbuffersScreens[1], 20, 130);  
  	cpct_drawStringM0("2.IR AL MENU", pvideomem, 1, 0);
}

void drawGameComplete() {
	u8 *pvideomem;

	drawScreensBorder();

	pvideomem = cpct_getScreenPtr(scrbuffersScreens[1], 26, 115);  
  	cpct_drawStringM0("1.VOLVER A JUGAR", pvideomem, 3, 0);
  	pvideomem = cpct_getScreenPtr(scrbuffersScreens[1], 20, 130);  
  	cpct_drawStringM0("2.IR AL MENU", pvideomem, 1, 0);
}*/

void drawScreensBorder() {
	u8* pvideomem;
	u8 i;

	pvideomem = cpct_getScreenPtr(scrbuffersScreens[1], 0, 0);
	cpct_drawTileAligned4x8_f(G_border01, pvideomem); 

	pvideomem = cpct_getScreenPtr(scrbuffersScreens[1], 76, 0);
	cpct_drawTileAligned4x8_f(G_border16, pvideomem); 

	pvideomem = cpct_getScreenPtr(scrbuffersScreens[1], 76, 192);
	cpct_drawTileAligned4x8_f(G_border17, pvideomem); 

	pvideomem = cpct_getScreenPtr(scrbuffersScreens[1], 0, 192);
	cpct_drawTileAligned4x8_f(G_border10, pvideomem); 

	for(i = 0; i < 18; i++) {
		pvideomem = cpct_getScreenPtr(scrbuffersScreens[1], i*4+4, 0);
		cpct_drawSprite(G_border02, pvideomem, 4, 8); 

		pvideomem = cpct_getScreenPtr(scrbuffersScreens[1], i*4+4, 192);
		cpct_drawSprite(G_border09, pvideomem, 4, 8);  
	}

	for(i = 0; i < 23; i++) {
		pvideomem = cpct_getScreenPtr(scrbuffersScreens[1], 0, i*8+8);
		cpct_drawSprite(G_border11, pvideomem, 4, 8); 

		pvideomem = cpct_getScreenPtr(scrbuffersScreens[1], 76, i*8+8);
		cpct_drawSprite(G_border19, pvideomem, 4, 8);  
	}
}

// Intercambia los buffers
void swapBuffersScreens(u8** scrbuffersScreens) {
   u8* aux; // Auxiliary pointer for making the change
   
   // Change what is shown on the screen (present backbuffer (1) is changed to 
   // front-buffer, so it is shown at the screen)
   // cpct_setVideoMemoryPage requires the 6 Most Significant bits of the address,
   // so we have to shift them 10 times to the right (as addresses have 16 bits)
   //
   cpct_setVideoMemoryPage( (u16)(scrbuffersScreens[1]) >> 10 );
   
   // Once backbuffer is being shown at the screen, we switch our two 
   // variables to start using (0) as backbuffer and (1) as front-buffer
   aux = scrbuffersScreens[0];
   scrbuffersScreens[0] = scrbuffersScreens[1];
   scrbuffersScreens[1] = aux;
}