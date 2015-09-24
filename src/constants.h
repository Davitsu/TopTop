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

#define G_sceneMenu 0   // Escena del menu principal
#define G_sceneGame 1   // Escena del juego

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