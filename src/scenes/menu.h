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

#ifndef _MENU_H_
#define _MENU_H_

#include <types.h>
#include "../sprites/animation.h"

void initMenu();
u8 updateMenu();

void drawMenuBorder();
void drawMenuBorderTile(u8 x, u8 y, u8 *spriteBorder);
void drawMenuBorderSprite(u8 x, u8 y, u8 *spriteBorder);
void drawMenu();
void drawTop(u8 x, u8 y);
void drawTopTile(u8 x, u8 y);
void drawOptions();
void drawMenuHeroes();
void swapBuffersMenu(u8**);

//extern TAnimation anim;

#endif