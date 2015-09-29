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

#include <stdio.h>

#include <cpctelera.h>
#include "heroe.h"
#include "../sprites/animation.h"
#include "../sprites/sprites.h"

// Crea a los personajes
void initHeroes(struct Heroe* heroe1, struct Heroe* heroe2) {
   heroe1->x = 28;
   heroe1->y = 180;
   heroe1->health = 6;

   heroe2->x = 48;
   heroe2->y = 180;
   heroe2->health = 6;
}