// ------------------------------------------------------
//
// Copyright (c) 2015 RANTAN
//
// - David Girón Jareño - @Davitsu
// - Sandra María Garzón Hernández - @AlexySGH
//
// More games: rantangames.com
//
// ------------------------------------------------------

#include <types.h>

// COLOR PALETTE
const u8 G_palette[16] = {
   0x00, 0x0A, 0x13, 0x17, 0x1A, 0x0F, 0x19, 0x06,
   0x03, 0x02, 0x01, 0x04, 0x0D, 0x05, 0x10, 0x0E};

// ===============================================
// =											 =
// = 				CHARACTERS					 =
// =											 =
// ===============================================

// RED HAIRED GIRL
const u8 G_heroR_idle01[96] = {  	// idle - frame 1
	0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00, 
	0xAA, 0x54, 0x00, 0xFC, 0x00, 0xFC, 0xFF, 0x00, 
	0x00, 0xFC, 0x00, 0xFC, 0x00, 0xFC, 0x55, 0xA8, 
	0x00, 0xB8, 0x00, 0x30, 0x00, 0xFC, 0x00, 0xFC, 
	0x00, 0x00, 0x00, 0x30, 0x00, 0x20, 0x00, 0x54, 
	0x00, 0x20, 0x00, 0x30, 0x00, 0x20, 0x00, 0x74, 
	0x00, 0x71, 0x00, 0x30, 0x00, 0x71, 0x00, 0x74, 
	0x00, 0x3A, 0x00, 0x30, 0x00, 0x30, 0x00, 0x7E, 
	0xAA, 0x54, 0x00, 0xB2, 0x00, 0xF6, 0x55, 0xA8, 
	0x00, 0xB8, 0x00, 0xF3, 0x00, 0xB2, 0x00, 0xFC, 
	0xAA, 0x54, 0x00, 0x03, 0x00, 0x56, 0x55, 0xA8, 
	0xFF, 0x00, 0x55, 0xA2, 0x55, 0xA2, 0xFF, 0x00};

const u8 G_heroR_idle02[48] = { 	// idle - frame 2
	0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 
	0x54, 0xFC, 0xFC, 0x00, 
	0xFC, 0xFC, 0xFC, 0xA8, 
	0xB8, 0x30, 0xFC, 0xFC, 
	0x00, 0x30, 0x20, 0x54, 
	0x20, 0x30, 0x20, 0x74, 
	0x71, 0x30, 0x71, 0x74, 
	0x3A, 0x20, 0x30, 0x7E, 
	0x54, 0xF3, 0xF6, 0xA8, 
	0xB8, 0x03, 0x12, 0xFC, 
	0x54, 0xA2, 0xF6, 0xA8};

// BLUE HAIRED GUY
const u8 G_heroB_idle01[96] = { 	//idle - frame 1
	0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00, 
	0xAA, 0x41, 0x00, 0xC3, 0x00, 0xC3, 0xFF, 0x00, 
	0x00, 0xC3, 0x00, 0xC3, 0x00, 0xC3, 0x55, 0x82, 
	0x00, 0xC3, 0x00, 0xC3, 0x00, 0xC3, 0x00, 0xC3, 
	0x00, 0x00, 0x00, 0x61, 0x00, 0x82, 0x00, 0x41, 
	0x00, 0x20, 0x00, 0x30, 0x00, 0x82, 0x00, 0x61, 
	0x00, 0x75, 0x00, 0x30, 0x00, 0x75, 0x00, 0x61, 
	0x00, 0x3A, 0x00, 0x30, 0x00, 0x30, 0x55, 0x2A, 
	0xFF, 0x00, 0x00, 0xBA, 0x55, 0xAA, 0x55, 0x82, 
	0xAA, 0x10, 0x00, 0xFF, 0x00, 0xBA, 0xFF, 0x00, 
	0xFF, 0x00, 0x00, 0x0F, 0x55, 0x0A, 0xFF, 0x00, 
	0xFF, 0x00, 0x55, 0xAA, 0x55, 0xAA, 0xFF, 0x00};

// ===============================================
// =											 =
// = 				STAGE TILES					 =
// =											 =
// ===============================================

const u8 G_tile01[32] = { 		// pared fija del escenario
	0xC0, 0xC0, 0xC0, 0xC0, 
	0xCC, 0xC8, 0xCC, 0xCC, 
	0x0C, 0xC8, 0x0C, 0x0C, 
	0x0C, 0xC8, 0x0C, 0x0C, 
	0xC0, 0xC0, 0xC0, 0xC0, 
	0xCC, 0xCC, 0xCC, 0xC8, 
	0x0C, 0x0C, 0x0C, 0xC8, 
	0x0C, 0x0C, 0x0C, 0xC8};


const u8 G_tile02[32] = { 		// pared rompible - frame 1
	0x40, 0xCC, 0xCC, 0x80, 
	0xC4, 0x4C, 0x0C, 0x48, 
	0x8C, 0x8C, 0x0C, 0x0C, 
	0xCC, 0x0C, 0x0C, 0x0C, 
	0x4C, 0x0C, 0x0C, 0x0C, 
	0x0C, 0x0C, 0x0C, 0x0C, 
	0x84, 0x8C, 0x0C, 0x48, 
	0x40, 0x0C, 0x0C, 0x80};


const u8 G_tile03[32] = { 		// pared rompible - frame 2
	0x40, 0xCC, 0xCC, 0x80, 
	0xC4, 0xC4, 0x0C, 0x48, 
	0x8C, 0xC8, 0x0C, 0x0C, 
	0xCC, 0x0C, 0x84, 0x84, 
	0x4C, 0x48, 0x40, 0x0C, 
	0x0C, 0x84, 0x48, 0x0C, 
	0x84, 0x8C, 0x48, 0x48, 
	0x40, 0x0C, 0x0C, 0x80};


const u8 G_tile04[32] = { 		// pared rompible - frame 3
	0x40, 0x4C, 0x48, 0x00, 
	0x44, 0x84, 0x84, 0x80, 
	0x84, 0x40, 0x48, 0x48, 
	0x4C, 0x84, 0x40, 0x84, 
	0x48, 0x48, 0x00, 0x84, 
	0x0C, 0x80, 0x80, 0x48, 
	0x84, 0x8C, 0x48, 0x80, 
	0x40, 0x0C, 0xC0, 0x00};

const u8 G_tileBlack[32] = {  	// tile para limpiar
	0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00};

// ===============================================
// =											 =
// = 				   DOORS					 =
// =											 =
// ===============================================

const u8 G_door01R[128] = { 							//puerta cerrada roja
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x01, 0xFC, 0xFC, 0x02, 0x00, 0x00, 
	0x00, 0x01, 0xFC, 0x03, 0x03, 0xFC, 0x02, 0x00, 
	0x00, 0x56, 0x03, 0xFC, 0xFC, 0x03, 0xA9, 0x00, 
	0x00, 0xA9, 0xFC, 0xFC, 0xFC, 0xFC, 0x56, 0x00, 
	0x01, 0xA9, 0x03, 0x03, 0x03, 0x03, 0x56, 0x02, 
	0x01, 0xA9, 0xFC, 0x56, 0xA9, 0xFC, 0x56, 0x02, 
	0x01, 0xA9, 0xFC, 0x56, 0xA9, 0xFC, 0x56, 0x02, 
	0x01, 0xA9, 0x03, 0xA9, 0x56, 0x03, 0x56, 0x02, 
	0x01, 0xA9, 0xFC, 0x56, 0xA9, 0xFC, 0x56, 0x02, 
	0x01, 0xA9, 0xFC, 0x56, 0xA9, 0xFC, 0x56, 0x02, 
	0x01, 0xA9, 0x03, 0xA9, 0x56, 0x03, 0x56, 0x02, 
	0x01, 0xA9, 0xFC, 0x56, 0xA9, 0xFC, 0x56, 0x02, 
	0x01, 0xA9, 0xFC, 0x56, 0xA9, 0xFC, 0x56, 0x02, 
	0x01, 0xA9, 0x03, 0x03, 0x03, 0x03, 0x56, 0x02, 
	0x01, 0xA9, 0x03, 0x03, 0x03, 0x03, 0x56, 0x02};


const u8 G_door01B[128] = { 							//puerta cerrada azul
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x05, 0xC3, 0xC3, 0x0A, 0x00, 0x00, 
	0x00, 0x05, 0xC3, 0x0F, 0x0F, 0xC3, 0x0A, 0x00, 
	0x00, 0x4B, 0x0F, 0xC3, 0xC3, 0x0F, 0x87, 0x00, 
	0x00, 0x87, 0xC3, 0xC3, 0xC3, 0xC3, 0x4B, 0x00, 
	0x05, 0x87, 0x0F, 0x0F, 0x0F, 0x0F, 0x4B, 0x0A, 
	0x05, 0x87, 0xC3, 0x4B, 0x87, 0xC3, 0x4B, 0x0A, 
	0x05, 0x87, 0xC3, 0x4B, 0x87, 0xC3, 0x4B, 0x0A, 
	0x05, 0x87, 0x0F, 0x87, 0x4B, 0x0F, 0x4B, 0x0A, 
	0x05, 0x87, 0xC3, 0x4B, 0x87, 0xC3, 0x4B, 0x0A, 
	0x05, 0x87, 0xC3, 0x4B, 0x87, 0xC3, 0x4B, 0x0A, 
	0x05, 0x87, 0x0F, 0x87, 0x4B, 0x0F, 0x4B, 0x0A, 
	0x05, 0x87, 0xC3, 0x4B, 0x87, 0xC3, 0x4B, 0x0A, 
	0x05, 0x87, 0xC3, 0x4B, 0x87, 0xC3, 0x4B, 0x0A, 
	0x05, 0x87, 0x0F, 0x0F, 0x0F, 0x0F, 0x4B, 0x0A, 
	0x05, 0x87, 0x0F, 0x0F, 0x0F, 0x0F, 0x4B, 0x0A};


const u8 G_door02R[128] = { 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x01, 0xFC, 0xFC, 0x02, 0x00, 0x00, 
	0x00, 0x01, 0xFC, 0x03, 0x03, 0xFC, 0x02, 0x00, 
	0x00, 0x56, 0x02, 0x00, 0x00, 0x01, 0xA9, 0x00, 
	0x00, 0xA9, 0x00, 0x00, 0x00, 0x56, 0xFC, 0x00, 
	0x01, 0xA8, 0x00, 0x00, 0x00, 0xA9, 0x56, 0x02, 
	0x01, 0xA8, 0x00, 0x00, 0x00, 0xA9, 0x56, 0x02, 
	0x01, 0xA8, 0x00, 0x00, 0x56, 0xFC, 0xFC, 0x02, 
	0x01, 0xA8, 0x00, 0x00, 0xA9, 0x03, 0x56, 0x02, 
	0x01, 0xA8, 0x00, 0x00, 0xA9, 0x03, 0x56, 0x02, 
	0x01, 0xA8, 0x00, 0x56, 0xFC, 0xFC, 0xFC, 0x02, 
	0x01, 0xA8, 0x00, 0xA9, 0x03, 0x03, 0x56, 0x02, 
	0x01, 0xA8, 0x00, 0xA9, 0x03, 0x03, 0x56, 0x02, 
	0x01, 0xA8, 0x56, 0xFC, 0xFC, 0xFC, 0xFC, 0x02, 
	0x01, 0xA8, 0xA9, 0x03, 0x03, 0x03, 0x56, 0x02, 
	0x01, 0xA9, 0xA9, 0x03, 0x03, 0x03, 0x56, 0x02};


const u8 G_door02B[128] = { 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x05, 0xC3, 0xC3, 0x0A, 0x00, 0x00, 
	0x00, 0x05, 0xC3, 0x0F, 0x0F, 0xC3, 0x0A, 0x00, 
	0x00, 0x4B, 0x0A, 0x00, 0x00, 0x05, 0x87, 0x00, 
	0x00, 0x87, 0x00, 0x00, 0x00, 0x4B, 0xC3, 0x00, 
	0x05, 0x82, 0x00, 0x00, 0x00, 0x87, 0x4B, 0x0A, 
	0x05, 0x82, 0x00, 0x00, 0x00, 0x87, 0x4B, 0x0A, 
	0x05, 0x82, 0x00, 0x00, 0x4B, 0xC3, 0xC3, 0x0A, 
	0x05, 0x82, 0x00, 0x00, 0x87, 0x0F, 0x4B, 0x0A, 
	0x05, 0x82, 0x00, 0x00, 0x87, 0x0F, 0x4B, 0x0A, 
	0x05, 0x82, 0x00, 0x4B, 0xC3, 0xC3, 0xC3, 0x0A, 
	0x05, 0x82, 0x00, 0x87, 0x0F, 0x0F, 0x4B, 0x0A, 
	0x05, 0x82, 0x00, 0x87, 0x0F, 0x0F, 0x4B, 0x0A, 
	0x05, 0x82, 0x4B, 0xC3, 0xC3, 0xC3, 0xC3, 0x0A, 
	0x05, 0x82, 0x87, 0x0F, 0x0F, 0x0F, 0x4B, 0x0A, 
	0x05, 0x87, 0x87, 0x0F, 0x0F, 0x0F, 0x4B, 0x0A};


// ===============================================
// =											 =
// = 				   ITEMS					 =
// =											 =
// ===============================================

const u8 G_redPotion[32] = { 	// pocion de curacion roja
	0x00, 0x00, 0x00, 0x00, 
	0x00, 0x98, 0x64, 0x00, 
	0x00, 0x44, 0x88, 0x00, 
	0x00, 0x88, 0x44, 0x00, 
	0x10, 0x00, 0x00, 0x20, 
	0x10, 0xFC, 0xFC, 0x20, 
	0x44, 0x03, 0x03, 0x88, 
	0x00, 0xCC, 0xCC, 0x00};


const u8 G_bluePotion[32] = { 	// pocion de curacion azul
	0x00, 0x00, 0x00, 0x00, 
	0x00, 0x98, 0x64, 0x00, 
	0x00, 0x44, 0x88, 0x00, 
	0x00, 0x88, 0x44, 0x00, 
	0x10, 0x00, 0x00, 0x20, 
	0x10, 0xC3, 0xC3, 0x20, 
	0x44, 0x0F, 0x0F, 0x88, 
	0x00, 0xCC, 0xCC, 0x00};

const u8 G_yellowPotion[32] = { // pocion de invencibilidad
	0x00, 0x00, 0x00, 0x00, 
	0x00, 0x98, 0x64, 0x00, 
	0x00, 0x44, 0x88, 0x00, 
	0x00, 0x88, 0x44, 0x00, 
	0x10, 0x00, 0x00, 0x20, 
	0x10, 0x3C, 0x3C, 0x20, 
	0x44, 0xF0, 0xF0, 0x88, 
	0x00, 0xCC, 0xCC, 0x00};

// ===============================================
// =											 =
// = 				 CORAZONES					 =
// =											 =
// ===============================================

const u8 G_heartR_full[32] = { 
	0x10, 0x20, 0x30, 0x00, 
	0x74, 0xB8, 0xFC, 0x20, 
	0x74, 0xFC, 0xFC, 0x20, 
	0x74, 0xFC, 0xFC, 0x20, 
	0x10, 0xFC, 0xB8, 0x00, 
	0x00, 0x74, 0x20, 0x00, 
	0x00, 0x10, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00};


const u8 G_heartB_full[32] = { 
	0x10, 0x20, 0x30, 0x00, 
	0x61, 0x92, 0xC3, 0x20, 
	0x61, 0xC3, 0xC3, 0x20, 
	0x61, 0xC3, 0xC3, 0x20, 
	0x10, 0xC3, 0x92, 0x00, 
	0x00, 0x61, 0x20, 0x00, 
	0x00, 0x10, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00};


const u8 G_heartR_half[32] = { 
	0x10, 0x20, 0x30, 0x00, 
	0x74, 0xB8, 0x00, 0x20, 
	0x74, 0xA8, 0x00, 0x20, 
	0x74, 0xA8, 0x00, 0x20, 
	0x10, 0xA8, 0x10, 0x00, 
	0x00, 0x20, 0x20, 0x00, 
	0x00, 0x10, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00};


const u8 G_heartB_half[32] = { 
	0x10, 0x20, 0x30, 0x00, 
	0x61, 0x92, 0x00, 0x20, 
	0x61, 0x82, 0x00, 0x20, 
	0x61, 0x82, 0x00, 0x20, 
	0x10, 0x82, 0x10, 0x00, 
	0x00, 0x20, 0x20, 0x00, 
	0x00, 0x10, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00};


const u8 G_heart_empty[32] = { 
	0x10, 0x20, 0x30, 0x00, 
	0x20, 0x10, 0x00, 0x20, 
	0x20, 0x00, 0x00, 0x20, 
	0x20, 0x00, 0x00, 0x20, 
	0x10, 0x00, 0x10, 0x00, 
	0x00, 0x20, 0x20, 0x00, 
	0x00, 0x10, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00};

// ===============================================
// =											 =
// = 				 BORDES HUD					 =
// =											 =
// ===============================================

const u8 G_border01[32] = { 
	0x50, 0xF0, 0xF0, 0xF0, 
	0xA0, 0xA0, 0x00, 0x00, 
	0xF0, 0x00, 0x00, 0x00, 
	0xA0, 0x00, 0x00, 0x00, 
	0xA0, 0x00, 0x00, 0x00, 
	0xA0, 0x00, 0x00, 0x00, 
	0xA0, 0x00, 0x00, 0x00, 
	0xA0, 0x00, 0x00, 0x00};


const u8 G_border02[32] = { 
	0xF0, 0xF0, 0xF0, 0xF0, 
	0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00};


const u8 G_border03[32] = { 
	0xF0, 0xF0, 0xF0, 0xF0, 
	0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 
	0x50, 0xF0, 0xF0, 0xF0, 
	0xA0, 0xA0, 0x00, 0x00, 
	0xF0, 0x00, 0x00, 0x00, 
	0xA0, 0x00, 0x00, 0x00};


const u8 G_border04[32] = { 
	0xF0, 0xF0, 0xF0, 0x00, 
	0x00, 0x00, 0xA0, 0xA0, 
	0x00, 0x00, 0x50, 0xA0, 
	0x00, 0x00, 0x00, 0xA0, 
	0xF0, 0xF0, 0xF0, 0xF0, 
	0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00};


const u8 G_border05[32] = { 
	0xA0, 0x00, 0x00, 0x00, 
	0xA0, 0x00, 0x00, 0x00, 
	0xF0, 0x00, 0x00, 0x00, 
	0xA0, 0xA0, 0x00, 0x00, 
	0x50, 0xF0, 0xF0, 0xF0, 
	0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00};


const u8 G_border06[32] = { 
	0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 
	0xF0, 0xF0, 0xF0, 0xF0, 
	0x00, 0x00, 0x00, 0xA0, 
	0x00, 0x00, 0x00, 0xA0, 
	0x00, 0x00, 0x00, 0xA0};


const u8 G_border07[32] = { 
	0x00, 0x00, 0x00, 0xA0, 
	0x00, 0x00, 0x00, 0xA0, 
	0x00, 0x00, 0x00, 0xA0, 
	0x00, 0x00, 0x00, 0xA0, 
	0x00, 0x00, 0x00, 0xA0, 
	0x00, 0x00, 0x00, 0xA0, 
	0x00, 0x00, 0x00, 0xA0, 
	0x00, 0x00, 0x00, 0xA0};


const u8 G_border08[32] = { 
	0x00, 0x00, 0x00, 0xA0, 
	0x00, 0x00, 0x00, 0xA0, 
	0x00, 0x00, 0x00, 0xA0, 
	0x00, 0x00, 0x00, 0xA0, 
	0x00, 0x00, 0x50, 0xA0, 
	0x00, 0x00, 0xA0, 0xA0, 
	0xF0, 0xF0, 0xF0, 0x00, 
	0x00, 0x00, 0x00, 0x00};


const u8 G_border09[32] = { 
	0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 
	0xF0, 0xF0, 0xF0, 0xF0, 
	0x00, 0x00, 0x00, 0x00};


const u8 G_border10[32] = { 
	0xA0, 0x00, 0x00, 0x00, 
	0xA0, 0x00, 0x00, 0x00, 
	0xA0, 0x00, 0x00, 0x00, 
	0xA0, 0x00, 0x00, 0x00, 
	0xF0, 0x00, 0x00, 0x00, 
	0xA0, 0xA0, 0x00, 0x00, 
	0x50, 0xF0, 0xF0, 0xF0, 
	0x00, 0x00, 0x00, 0x00};


const u8 G_border11[32] = { 
	0xA0, 0x00, 0x00, 0x00, 
	0xA0, 0x00, 0x00, 0x00, 
	0xA0, 0x00, 0x00, 0x00, 
	0xA0, 0x00, 0x00, 0x00, 
	0xA0, 0x00, 0x00, 0x00, 
	0xA0, 0x00, 0x00, 0x00, 
	0xA0, 0x00, 0x00, 0x00, 
	0xA0, 0x00, 0x00, 0x00};


const u8 G_border12[32] = { 
	0x00, 0xF0, 0xF0, 0xF0, 
	0x50, 0x50, 0x00, 0x00, 
	0x50, 0xA0, 0x00, 0x00, 
	0x50, 0x00, 0x00, 0x00, 
	0xF0, 0xF0, 0xF0, 0xF0, 
	0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00};


const u8 G_border13[32] = { 
	0xF0, 0xF0, 0xF0, 0xF0, 
	0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 
	0xF0, 0xF0, 0xF0, 0xA0, 
	0x00, 0x00, 0x50, 0x50, 
	0x00, 0x00, 0x00, 0xF0, 
	0x00, 0x00, 0x00, 0x50};


const u8 G_border14[32] = { 
	0x00, 0x00, 0x00, 0x50, 
	0x00, 0x00, 0x00, 0x50, 
	0x00, 0x00, 0x00, 0xF0, 
	0x00, 0x00, 0x50, 0x50, 
	0xF0, 0xF0, 0xF0, 0xA0, 
	0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00};


const u8 G_border15[32] = { 
	0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 
	0xF0, 0xF0, 0xF0, 0xF0, 
	0x50, 0x00, 0x00, 0x00, 
	0x50, 0x00, 0x00, 0x00, 
	0x50, 0x00, 0x00, 0x00};


const u8 G_border16[32] = { 
	0xF0, 0xF0, 0xF0, 0xA0, 
	0x00, 0x00, 0x50, 0x50, 
	0x00, 0x00, 0x00, 0xF0, 
	0x00, 0x00, 0x00, 0x50, 
	0x00, 0x00, 0x00, 0x50, 
	0x00, 0x00, 0x00, 0x50, 
	0x00, 0x00, 0x00, 0x50, 
	0x00, 0x00, 0x00, 0x50};

const u8 G_border17[32] = { 
	0x00, 0x00, 0x00, 0x50, 
	0x00, 0x00, 0x00, 0x50, 
	0x00, 0x00, 0x00, 0x50, 
	0x00, 0x00, 0x00, 0x50, 
	0x00, 0x00, 0x00, 0xF0, 
	0x00, 0x00, 0x50, 0x50, 
	0xF0, 0xF0, 0xF0, 0xA0, 
	0x00, 0x00, 0x00, 0x00};

const u8 G_border18[32] = { 
	0x50, 0x00, 0x00, 0x00, 
	0x50, 0x00, 0x00, 0x00, 
	0x50, 0x00, 0x00, 0x00, 
	0x50, 0x00, 0x00, 0x00, 
	0x50, 0x00, 0x00, 0x00, 
	0x50, 0x00, 0x00, 0x00, 
	0x50, 0x00, 0x00, 0x00, 
	0x50, 0x00, 0x00, 0x00};

const u8 G_border19[32] = { 
	0x00, 0x00, 0x00, 0x50, 
	0x00, 0x00, 0x00, 0x50, 
	0x00, 0x00, 0x00, 0x50, 
	0x00, 0x00, 0x00, 0x50, 
	0x00, 0x00, 0x00, 0x50, 
	0x00, 0x00, 0x00, 0x50, 
	0x00, 0x00, 0x00, 0x50, 
	0x00, 0x00, 0x00, 0x50};

const u8 G_border20[32] = { 
	0x50, 0x00, 0x00, 0x00, 
	0x50, 0x00, 0x00, 0x00, 
	0x50, 0x00, 0x00, 0x00, 
	0x50, 0x00, 0x00, 0x00, 
	0x50, 0xA0, 0x00, 0x00, 
	0x50, 0x50, 0x00, 0x00, 
	0x00, 0xF0, 0xF0, 0xF0, 
	0x00, 0x00, 0x00, 0x00};
