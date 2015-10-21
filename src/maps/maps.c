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

#include <types.h>

const u8 G_map01[152] = {
	0x18, 0x19, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
	0x1A, 0x1B, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
	0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 
	0x00, 0x00, 0x04, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 
	0x01, 0x00, 0x05, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 
	0xFF, 0x00, 0x05, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 
	0xFF, 0x70, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 
	0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 
	0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
	0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x5E, 0xFF, 
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0x10, 0x11, 
	0x03, 0xFF, 0xFF, 0xFF, 0x08, 0xFF, 0x12, 0x13};

const u8 G_map02[152] = { 
	0x04, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0x1C, 0x1D, 
	0x05, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0x1E, 0x1F, 
	0x05, 0x00, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 
	0x05, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x7A, 0x7B, 
	0x05, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x7C, 0x7D, 
	0x00, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0xFF, 0x00, 0x00, 0x00, 
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x72, 0x73, 
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x74, 0x75, 
	0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
	0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0x02, 0xFF, 
	0x00, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
	0x68, 0x69, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 
	0x6A, 0x6B, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x14, 0x15, 0xFF, 0xFF, 0xFF, 0xFF, 0x60, 0x61, 
	0x16, 0x17, 0xFF, 0xFF, 0x08, 0xFF, 0x62, 0x63};

const u8 G_map03[152] = { 
	0x18, 0x19, 0xFF, 0xFF, 0xFF, 0x05, 0x05, 0x05, 
	0x1A, 0x1B, 0xFF, 0xFF, 0xFF, 0x05, 0x05, 0x05, 
	0x00, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0x05, 
	0x00, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
	0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
	0x04, 0x00, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 
	0xFF, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
	0xFF, 0x05, 0xFF, 0x08, 0x08, 0x08, 0xFF, 0xFF, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 
	0x32, 0x33, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x08, 
	0x34, 0x35, 0xFF, 0x03, 0x08, 0x08, 0x08, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x05, 0xFF, 0xFF, 0xFF, 0x2A, 0x2B, 0x05, 0x05, 
	0x05, 0xFF, 0xFF, 0xFF, 0x2C, 0x2D, 0x05, 0x05, 
	0x05, 0x05, 0x05, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
	0xFF, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
	0x08, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0x10, 0x11, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0x12, 0x13};

const u8 G_map04[152] = { 
	0xFF, 0xFF, 0xFF, 0x1C, 0x1D, 0xFF, 0xFF, 0xFF, 
	0xFF, 0xFF, 0xFF, 0x1E, 0x1F, 0xFF, 0xFF, 0xFF, 
	0x28, 0xFF, 0xFF, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 
	0x00, 0xFF, 0xFF, 0x00, 0x00, 0xFF, 0xFF, 0x00, 
	0xFF, 0xFF, 0xFF, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 
	0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 
	0xFF, 0xFF, 0xFF, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 
	0x00, 0xFF, 0xFF, 0x00, 0x00, 0xFF, 0xFF, 0x00, 
	0xFF, 0xFF, 0xFF, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 
	0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 
	0x00, 0xFF, 0x05, 0x05, 0x05, 0x05, 0x00, 0xFF, 
	0xFF, 0xFF, 0x05, 0x04, 0x02, 0x05, 0xFF, 0xFF, 
	0xFF, 0xFF, 0x05, 0x05, 0x05, 0x05, 0xFF, 0xFF, 
	0xFF, 0x00, 0x05, 0x05, 0x05, 0x05, 0xFF, 0xFF, 
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 
	0x14, 0x15, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
	0x16, 0x17, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0xFF};

const u8 G_map07[152] = { 
	0x00, 0x05, 0x05, 0x01, 0x00, 0x18, 0x19, 0x05, 
	0x00, 0x05, 0x05, 0x05, 0x00, 0x1A, 0x1B, 0x05, 
	0x00, 0x05, 0x05, 0x05, 0x00, 0x00, 0x00, 0x05, 
	0xFF, 0xFF, 0x05, 0x05, 0x05, 0x05, 0x05, 0xFF, 
	0xFF, 0xFF, 0xFF, 0x05, 0x05, 0x05, 0xFF, 0xFF, 
	0xFF, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
	0xFF, 0xFF, 0xFF, 0x08, 0x08, 0xFF, 0x08, 0x08, 
	0x00, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
	0x00, 0xFF, 0xFF, 0x5E, 0xFF, 0xFF, 0xFF, 0xFF, 
	0xFF, 0xFF, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
	0x04, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0xFF, 
	0xFF, 0x08, 0x08, 0x08, 0x08, 0x00, 0x32, 0x33, 
	0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x34, 0x35, 
	0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x2A, 0x2B, 0xFF, 0xFF, 0xFF, 0xFF, 0x10, 0x11, 
	0x2C, 0x2D, 0xFF, 0xFF, 0xFF, 0xFF, 0x12, 0x13};

const u8 G_map08[152] = { 
	0x68, 0x69, 0xFF, 0x00, 0x1C, 0x1D, 0xFF, 0x02, 
	0x6A, 0x6B, 0xFF, 0x00, 0x1E, 0x1F, 0xFF, 0xFF, 
	0x00, 0x00, 0xFF, 0x00, 0x00, 0x00, 0xFF, 0xFF, 
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
	0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 
	0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0xFF, 0xFF, 0xFF, 
	0x00, 0x00, 0x00, 0xFF, 0x00, 0xFF, 0xFF, 0xFF, 
	0x05, 0x05, 0xFF, 0xFF, 0x05, 0x05, 0x05, 0x00, 
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
	0x04, 0x08, 0xFF, 0x08, 0xFF, 0x08, 0x08, 0x08, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x05, 0x60, 0x61, 
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x05, 0x62, 0x63, 
	0xFF, 0xFF, 0x00, 0xFF, 0xFF, 0x05, 0x00, 0x00, 
	0xFF, 0xFF, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
	0xFF, 0xFF, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
	0x00, 0xFF, 0x00, 0xFF, 0xFF, 0x00, 0x00, 0xFF, 
	0x14, 0x15, 0xFF, 0xFF, 0xFF, 0xFF, 0x28, 0xFF, 
	0x16, 0x17, 0x08, 0x08, 0x08, 0x08, 0x00, 0x00};

