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

#ifndef _SCREENS_H_
#define _SCREENS_H_

#include <types.h>
#include "../sprites/animation.h"

void initScreens(u8 screen);
u8 updateScreens(u8 screen);

void drawScreensBorder();
void drawGameOver();
void drawNextLevel();
void drawGameComplete();
void swapBuffersScreens(u8**);

extern u8* const g_SCR_VMEM_SCREENS; 	// Pointer to the start of default video memory screen

#endif