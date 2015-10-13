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

extern u8* const G_SCR_VMEM_MENU = (u8*)0xC000; 

u8* const g_scrbuffersMenu[2] = { (u8*)0xC000, (u8*)0x8000 }; // Direccion de los dos buffers

// Inicializa el menu
void initMenu() {
	drawMenuBorder();

	// Preparamos el double buffer y dibujamos...
	cpct_memset_f64(g_scrbuffersMenu[1], 0x00, 0x4000); // Limpiamos el segundo buffer (contiene valores aleatorios)
	cpct_waitVSYNC();                               	// Esperamos al VSYNC para esperar a dibujar
	drawMenu();                                     	// Dibujamos en el buffer actual
	cpct_waitVSYNC();                               	// Volvemos a esperar al VSYNC
	swapBuffersMenu(g_scrbuffersMenu);             	 	// Cambiamos de buffer
	drawMenu();                                     	// Dibujamos en este buffer
}

// Update del menu
u8 updateMenu() { 

	cpct_waitVSYNC();
	swapBuffersMenu(g_scrbuffersMenu);



	return G_sceneMenu;
}

void drawMenu() {
	u8 *pvideomem;

	drawMenuBorder();

	// Dibujar opciones
    pvideomem = cpct_getScreenPtr(g_scrbuffersMenu[1], 26, 115);  
    cpct_drawStringM0("1.JUGAR", pvideomem, 5, 0);
    pvideomem = cpct_getScreenPtr(g_scrbuffersMenu[1], 20, 130);  
    cpct_drawStringM0("2.TUTORIAL", pvideomem, 5, 0);
    pvideomem = cpct_getScreenPtr(g_scrbuffersMenu[1], 20, 145);  
    cpct_drawStringM0("3.CREDITOS", pvideomem, 5, 0);
    pvideomem = cpct_getScreenPtr(g_scrbuffersMenu[1], 26, 160);  
    cpct_drawStringM0("4.SALIR", pvideomem, 5, 0);

    //pvideomem = cpct_getScreenPtr(g_scrbuffersMenu[1], 26, 160);  
    //cpct_drawStringM0("RANTAN 2015  AMSTRAD GAME", pvideomem, 5, 0);
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