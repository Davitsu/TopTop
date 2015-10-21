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

#include "audio.h"

// usamos la linea de comandos cpct_bin2c nombreDelArchivo para pasar de binario a array
__at(0x7C3F) const u8 G_toptop_music[630] = {
 0x41, 0x54, 0x31, 0x30, 0x01, 0x40, 0x42, 0x0f, 0x02, 0x06, 0x90, 0x00, 0x57, 0x7c, 0x60, 0x7c,
 0x73, 0x7c, 0x7a, 0x7c, 0xac, 0x7c, 0xc8, 0x7c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0d, 0x59,
 0x7c, 0x01, 0x00, 0x34, 0x30, 0x2c, 0x28, 0x24, 0x20, 0x1c, 0x18, 0x14, 0x10, 0x0c, 0x08, 0x04,
 0x00, 0x0d, 0x59, 0x7c, 0x01, 0x00, 0x36, 0x03, 0x0d, 0x59, 0x7c, 0x01, 0x00, 0xbc, 0xff, 0xff,
 0x3c, 0xb8, 0x01, 0x00, 0x38, 0xb4, 0xff, 0xff, 0x34, 0xb0, 0x01, 0x00, 0x30, 0xac, 0xff, 0xff,
 0x2c, 0xa8, 0x01, 0x00, 0x28, 0xa4, 0xff, 0xff, 0x24, 0xa0, 0x01, 0x00, 0x1c, 0x98, 0xff, 0xff,
 0x14, 0x90, 0x01, 0x00, 0x0c, 0x88, 0xff, 0xff, 0x04, 0x00, 0x0d, 0x59, 0x7c, 0x01, 0x00, 0xa8,
 0x09, 0x00, 0xa8, 0x06, 0x00, 0xa4, 0x04, 0x00, 0xa4, 0x03, 0x00, 0xa0, 0x01, 0x00, 0x20, 0x1c,
 0x1c, 0x18, 0x18, 0x14, 0x14, 0x14, 0x0d, 0x59, 0x7c, 0x01, 0x00, 0x3c, 0x38, 0x70, 0x03, 0x68,
 0x03, 0x60, 0x07, 0x58, 0x07, 0x50, 0x0c, 0x48, 0x0c, 0x0d, 0x59, 0x7c, 0x30, 0x00, 0x00, 0x00,
 0x07, 0x7d, 0x00, 0xb0, 0x7e, 0x3e, 0x7d, 0x81, 0x7d, 0x00, 0x08, 0x7d, 0x3e, 0x7d, 0x81, 0x7d,
 0x00, 0x08, 0x7d, 0x3e, 0x7d, 0xa6, 0x7d, 0x00, 0x74, 0x7e, 0x3e, 0x7d, 0x81, 0x7d, 0x00, 0xc8,
 0x7d, 0x3a, 0x7e, 0xfc, 0x7d, 0x01, 0xe1, 0x7c, 0x00, 0x42, 0x80, 0x00, 0x00, 0x02, 0xba, 0x65,
 0x01, 0xc0, 0x40, 0x02, 0xc6, 0x41, 0xc4, 0x43, 0x04, 0xc0, 0x45, 0x04, 0xc4, 0x41, 0x02, 0xc0,
 0x45, 0xba, 0x40, 0x02, 0xc4, 0x41, 0x10, 0xba, 0x45, 0xc0, 0x40, 0x02, 0xc6, 0x41, 0xc4, 0x43,
 0x04, 0xc0, 0x45, 0x04, 0xc4, 0x41, 0x02, 0xc0, 0x45, 0xba, 0x43, 0x02, 0xba, 0x41, 0x00, 0xd2,
 0xe9, 0x00, 0x00, 0x02, 0x04, 0xd2, 0x4d, 0x02, 0xd2, 0x4b, 0xd2, 0x49, 0x04, 0xd2, 0x4d, 0x02,
 0xd2, 0x4b, 0xd2, 0x49, 0x04, 0xd2, 0x4d, 0x02, 0xd2, 0x4b, 0xd2, 0x49, 0x04, 0xd2, 0x4d, 0x02,
 0xd2, 0x4b, 0xd2, 0x49, 0x04, 0xd2, 0x4d, 0x02, 0xd2, 0x4b, 0xd2, 0x49, 0x04, 0xd2, 0x4d, 0x02,
 0xd2, 0x4b, 0xd2, 0x49, 0x04, 0xd2, 0x4d, 0x02, 0xd2, 0x4b, 0xd2, 0x49, 0x04, 0xd2, 0x4d, 0x02,
 0xd2, 0x4b, 0x8a, 0xe5, 0x00, 0x00, 0x01, 0x0a, 0x90, 0x40, 0x0a, 0x8a, 0x40, 0x0a, 0x80, 0x40,
 0x02, 0x80, 0x40, 0x86, 0x43, 0x04, 0x8a, 0x45, 0x0a, 0x90, 0x40, 0x0a, 0x8a, 0x40, 0x0a, 0x80,
 0x40, 0x02, 0x80, 0x43, 0x86, 0x41, 0x00, 0x82, 0xe5, 0x00, 0x00, 0x01, 0x0a, 0x78, 0x40, 0x0a,
 0x82, 0x40, 0x0a, 0x78, 0x40, 0x02, 0x78, 0x40, 0x7e, 0x43, 0x04, 0x82, 0x45, 0x0a, 0x78, 0x40,
 0x0a, 0x82, 0x40, 0x0e, 0x80, 0x43, 0x86, 0x41, 0x00, 0xba, 0xe3, 0x00, 0x00, 0x03, 0x04, 0xc4,
 0x40, 0x04, 0xc0, 0x40, 0x04, 0xba, 0x40, 0x04, 0xb6, 0x40, 0x04, 0xb0, 0x40, 0x04, 0xac, 0x40,
 0x02, 0xa8, 0x45, 0xac, 0x43, 0x02, 0xae, 0x45, 0xac, 0x43, 0x02, 0xa8, 0x45, 0xa2, 0x43, 0x02,
 0xa2, 0x40, 0x10, 0xba, 0xeb, 0xfe, 0xff, 0x01, 0xc6, 0xc7, 0x00, 0x00, 0x00, 0x8a, 0xe5, 0x00,
 0x00, 0x03, 0x04, 0xc4, 0x6b, 0x04, 0x02, 0xc4, 0x60, 0x05, 0x82, 0x65, 0x03, 0x04, 0xba, 0x6b,
 0x04, 0x02, 0xba, 0x60, 0x05, 0x78, 0x65, 0x03, 0x04, 0xb0, 0x6b, 0x04, 0x02, 0xb0, 0x60, 0x05,
 0x7c, 0x65, 0x03, 0x04, 0xac, 0x6b, 0x04, 0x02, 0xae, 0x60, 0x05, 0x86, 0x65, 0x03, 0x04, 0xa2,
 0x6b, 0x04, 0x02, 0x8a, 0x65, 0x03, 0x12, 0xd2, 0x67, 0x01, 0x00, 0x98, 0xe5, 0x00, 0x00, 0x03,
 0x04, 0xd2, 0x6b, 0x02, 0x02, 0xd2, 0x49, 0x90, 0x65, 0x03, 0x04, 0xd2, 0x6b, 0x02, 0x02, 0xd2,
 0x49, 0x86, 0x65, 0x03, 0x04, 0xd2, 0x6b, 0x02, 0x02, 0xd2, 0x49, 0x8a, 0x65, 0x03, 0x04, 0xd2,
 0x6b, 0x02, 0x02, 0xd2, 0x49, 0x94, 0x65, 0x03, 0x04, 0xd2, 0x6b, 0x02, 0x02, 0x98, 0x65, 0x03,
 0x12, 0xc8, 0x67, 0x01, 0x00, 0x42, 0x80, 0x00, 0x00, 0x02, 0xba, 0x65, 0x01, 0xc0, 0x40, 0x02,
 0xc6, 0x41, 0xc4, 0x43, 0x04, 0xc0, 0x45, 0x04, 0xc4, 0x41, 0x02, 0xc0, 0x45, 0xba, 0x40, 0x02,
 0xc4, 0x41, 0x10, 0xba, 0x45, 0xc0, 0x40, 0x02, 0xc6, 0x41, 0xc4, 0x43, 0x04, 0xc0, 0x45, 0x04,
 0xc4, 0x41, 0x02, 0xc0, 0x45, 0xba, 0x43, 0x02, 0xba, 0x41, 0x04, 0xb0, 0x67, 0x03, 0xb6, 0x45,
 0x00, 0x42, 0x80, 0x00, 0x00, 0x00
};

__at(0x7EB4) const u8 G_toptop_effects[252] = {
 0x41, 0x54, 0x31, 0x30, 0x01, 0x40, 0x42, 0x0f, 0x02, 0xff, 0xda, 0x00, 0xd2, 0x7e, 0xdb, 0x7e,
 0xea, 0x7e, 0xf9, 0x7e, 0x22, 0x7f, 0x36, 0x7f, 0x4b, 0x7f, 0x67, 0x7f, 0x73, 0x7f, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00, 0x0d, 0xd4, 0x7e, 0x01, 0x00, 0x7c, 0x01, 0x78, 0x02, 0x74, 0x03, 0x70,
 0x05, 0x6c, 0x08, 0x0d, 0xd4, 0x7e, 0x01, 0x00, 0x36, 0x0c, 0x7c, 0x0b, 0x78, 0x09, 0x78, 0x07,
 0x34, 0x30, 0x0d, 0xd4, 0x7e, 0x01, 0x00, 0x7c, 0x07, 0x74, 0x0c, 0x6c, 0x10, 0x68, 0x0c, 0x64,
 0x07, 0x60, 0x0c, 0x78, 0x07, 0x70, 0x0c, 0x68, 0x10, 0x64, 0x0c, 0x60, 0x07, 0x5c, 0x0c, 0x74,
 0x07, 0x6c, 0x0c, 0x64, 0x10, 0x60, 0x0c, 0x5c, 0x07, 0x58, 0x0c, 0x0d, 0xd4, 0x7e, 0x01, 0x00,
 0x7c, 0x0c, 0x34, 0x30, 0x2c, 0x28, 0x24, 0x20, 0x1c, 0x18, 0x14, 0x10, 0x0c, 0x08, 0x04, 0x0d,
 0xd4, 0x7e, 0x01, 0x00, 0x3e, 0x2c, 0x7c, 0x16, 0x74, 0x0c, 0x6c, 0x0a, 0x60, 0x08, 0x54, 0x04,
 0x4c, 0x03, 0x48, 0x01, 0x0d, 0xd4, 0x7e, 0x01, 0x00, 0x3c, 0x7c, 0x04, 0x7c, 0x07, 0x30, 0x70,
 0x04, 0x70, 0x07, 0x0e, 0x00, 0x08, 0x68, 0x07, 0x74, 0x04, 0x7c, 0x07, 0x7c, 0x04, 0x7c, 0x07,
 0x0d, 0xd4, 0x7e, 0x01, 0x00, 0x3c, 0xb0, 0xff, 0xff, 0x20, 0x14, 0x04, 0x0d, 0xd4, 0x7e, 0x01,
 0x00, 0x3e, 0x15, 0x32, 0x00, 0x22, 0x00, 0x16, 0x00, 0x0a, 0x00, 0x06, 0x00, 0x3e, 0x15, 0x32,
 0x00, 0x22, 0x00, 0x16, 0x00, 0x0a, 0x00, 0x06, 0x00, 0x3e, 0x13, 0x32, 0x00, 0x22, 0x00, 0x16,
 0x00, 0x0a, 0x00, 0x0d, 0xd4, 0x7e, 0x40, 0x00, 0x00, 0x00, 0xaa, 0x7f, 0x00, 0xab, 0x7f, 0xab,
 0x7f, 0xab, 0x7f, 0x01, 0xa0, 0x7f, 0x00, 0x42, 0x80, 0x00, 0x00, 0x00
};
