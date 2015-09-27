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

#ifndef _CONSTANTS_H_
#define _CONSTANTS_H_

#include <types.h>

// IDs de las escenas del juego
#define G_sceneMenu 0   	// Escena del menu principal
#define G_sceneGame 1   	// Escena del juego

// Coordenadas de la esquina superior izquierda de cada mapa
#define G_mapStartLX 4 		// Posicion X inicial mapa izq (4 bytes * 1 tile)
#define G_mapStartLY 40 	// Posicion Y inicial mapa izq (8 bytes * 4 tiles)
#define G_mapStartRX 44		// Posicion X inicial mapa der (4 bytes * 11 tiles)
#define G_mapStartRY 40		// Posicion Y inicial mapa der (8 bytes * 4 tiles)

// Tamano de un mapa en tiles
#define G_mapWTiles 8 		// Ancho de un mapa en tiles
#define G_mapHTiles 19 		// Alto de un mapa en tiles

// Tamaño de un mapa en pixeles (bytes)
#define G_mapWBytes 32 		// Ancho de un mapa en bytes
#define G_mapHBytes 152 	// Ancho de un mapa en bytes

// Tamano de un tile
#define G_tileSizeW 4 		// Ancho de tile en bytes
#define G_tileSizeH 8		// Alto de tile en bytes

// Izquierda y derecha
#define G_left 0 			// Izquierda
#define G_right 1  			// Derecha

u8* const G_SCR_VMEM = (u8*)0xC000; // Pointer to the start of default video memory screen

// Offset para dibujar dentro del mapa
#define G_offsetX_m1 4 		// Offset X mapa 1
#define G_offsetX_m2 44		// Offset X mapa 2
#define G_offsetY 40 		// Offset Y (ambos mapas)

// Tamano del heroe en bytes
#define G_heroeW 4
#define G_heroeH 12

#define G_maxHealth 6	// Vida maxima de los personajes

//Bordes hasta los que el personaje puede moverse
#define G_borderRight_p1    32
#define G_borderLeft_p1      4
#define G_borderTop_p1      40 
#define G_borderBottom_p1  180

#define G_borderRight_p2    72
#define G_borderLeft_p2     44
#define G_borderTop_p2      40
#define G_borderBottom_p2  180

#endif