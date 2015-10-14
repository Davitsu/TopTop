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

#ifndef _SPRITES_H_
#define _SPRITES_H_

#include <types.h>

extern const u8 G_palette[16];

// ===============================================
// =											 =
// = 				CHARACTERS					 =
// =											 =
// ===============================================

extern const u8 G_heroR_idle_left01[96];
extern const u8 G_heroR_idle_left02[96];
extern const u8 G_heroR_idle_right01[96];
extern const u8 G_heroR_idle_right02[96];
extern const u8 G_heroR_run_left01[96];
extern const u8 G_heroR_run_left02[96];
extern const u8 G_heroR_run_left03[96];
extern const u8 G_heroR_run_left04[96];
extern const u8 G_heroR_run_right01[96];
extern const u8 G_heroR_run_right02[96];
extern const u8 G_heroR_run_right03[96];
extern const u8 G_heroR_run_right04[96];
extern const u8 G_heroR_jump_left01[96];
extern const u8 G_heroR_jump_right01[96];
extern const u8 G_heroR_fall_left01[96];
extern const u8 G_heroR_fall_right01[96];
extern const u8 G_heroR_duck_left01[96];
extern const u8 G_heroR_duck_left02[96];
extern const u8 G_heroR_duck_right01[96];
extern const u8 G_heroR_duck_right02[96];
extern const u8 G_heroR_duckrun_left01[96];
extern const u8 G_heroR_duckrun_left02[96];
extern const u8 G_heroR_duckrun_left03[96];
extern const u8 G_heroR_duckrun_left04[96];
extern const u8 G_heroR_duckrun_right01[96];
extern const u8 G_heroR_duckrun_right02[96];
extern const u8 G_heroR_duckrun_right03[96];
extern const u8 G_heroR_duckrun_right04[96];

extern const u8 G_heroB_idle_left01[96];
extern const u8 G_heroB_idle_left02[96];
extern const u8 G_heroB_idle_right01[96];
extern const u8 G_heroB_idle_right02[96];
extern const u8 G_heroB_run_left01[96];
extern const u8 G_heroB_run_left02[96];
extern const u8 G_heroB_run_left03[96];
extern const u8 G_heroB_run_left04[96];
extern const u8 G_heroB_run_right01[96];
extern const u8 G_heroB_run_right02[96];
extern const u8 G_heroB_run_right03[96];
extern const u8 G_heroB_run_right04[96];
extern const u8 G_heroB_jump_left01[96];
extern const u8 G_heroB_jump_right01[96];
extern const u8 G_heroB_fall_left01[96];
extern const u8 G_heroB_fall_right01[96];
extern const u8 G_heroB_duck_left01[96];
extern const u8 G_heroB_duck_right01[96];
extern const u8 G_heroB_duck_left02[96];
extern const u8 G_heroB_duck_right02[96];
extern const u8 G_heroB_duckrun_left01[96];
extern const u8 G_heroB_duckrun_right01[96];
extern const u8 G_heroB_duckrun_left02[96];
extern const u8 G_heroB_duckrun_right02[96];
extern const u8 G_heroB_duckrun_left03[96];
extern const u8 G_heroB_duckrun_right03[96];
extern const u8 G_heroB_duckrun_left04[96];
extern const u8 G_heroB_duckrun_right04[96];

// ===============================================
// =											 =
// = 				STAGE TILES					 =
// =											 =
// ===============================================

extern const u8 G_tile01[32];
extern const u8 G_tile02[32];
extern const u8 G_tile03[32];
extern const u8 G_tile04[32];
extern const u8 G_tileBlack[32];

// ===============================================
// =											 =
// = 				   DOORS					 =
// =											 =
// ===============================================

extern const u8 G_doorR_levelLocked_01[32];
extern const u8 G_doorR_levelLocked_02[32];
extern const u8 G_doorR_levelLocked_03[32];
extern const u8 G_doorR_levelLocked_04[32];
extern const u8 G_doorB_levelLocked_01[32];
extern const u8 G_doorB_levelLocked_02[32];
extern const u8 G_doorB_levelLocked_03[32];
extern const u8 G_doorB_levelLocked_04[32];
extern const u8 G_doorR_levelOpen01[32];
extern const u8 G_doorR_levelOpen02[32];
extern const u8 G_doorR_levelOpen03[32];
extern const u8 G_doorR_levelOpen04[32];
extern const u8 G_doorB_levelOpen01[32];
extern const u8 G_doorB_levelOpen02[32];
extern const u8 G_doorB_levelOpen03[32];
extern const u8 G_doorB_levelOpen04[32];
extern const u8 G_doorR_init01[32];
extern const u8 G_doorR_init02[32];
extern const u8 G_doorR_init03[32];
extern const u8 G_doorR_init04[32];
extern const u8 G_doorB_init01[32];
extern const u8 G_doorB_init02[32];
extern const u8 G_doorB_init03[32];
extern const u8 G_doorB_init04[32];
extern const u8 G_doorR_open01[32];
extern const u8 G_doorR_open02[32];
extern const u8 G_doorR_open03[32];
extern const u8 G_doorR_open04[32];
extern const u8 G_doorB_open01[32];
extern const u8 G_doorB_open02[32];
extern const u8 G_doorB_open03[32];
extern const u8 G_doorB_open04[32];

// ===============================================
// =											 =
// = 				   ITEMS					 =
// =											 =
// ===============================================

extern const u8 G_redPotion[32];
extern const u8 G_bluePotion[32];
extern const u8 G_yellowPotion[32];
extern const u8 G_key[32];

// ===============================================
// =											 =
// = 				   BUTTONS					 =
// =											 =
// ===============================================

extern const u8 G_buttonR_normal[32];
extern const u8 G_buttonR_pressed[32]; 
extern const u8 G_buttonB_normal[32];
extern const u8 G_buttonB_pressed[32];

// ===============================================
// =											 =
// = 				 RETRATOS					 =
// =											 =
// ===============================================

extern const u8 G_portraitR[300];
extern const u8 G_portraitB[300];

// ===============================================
// =											 =
// = 				 CORAZONES					 =
// =											 =
// ===============================================

extern const u8 G_heartR_full[32];
extern const u8 G_heartB_full[32];
extern const u8 G_heartR_half[32];
extern const u8 G_heartB_half[32];
extern const u8 G_heart_empty[32];

// ===============================================
// =											 =
// = 				 BORDES HUD					 =
// =											 =
// ===============================================

extern const u8 G_border01[32];
extern const u8 G_border02[32];
extern const u8 G_border03[32];
extern const u8 G_border04[32];
extern const u8 G_border05[32];
extern const u8 G_border06[32];
extern const u8 G_border07[32];
extern const u8 G_border08[32];
extern const u8 G_border09[32];
extern const u8 G_border10[32];
extern const u8 G_border11[32];
extern const u8 G_border12[32];
extern const u8 G_border13[32];
extern const u8 G_border14[32];
extern const u8 G_border15[32];
extern const u8 G_border16[32];
extern const u8 G_border17[32];
extern const u8 G_border18[32];
extern const u8 G_border19[32];
extern const u8 G_border20[32];

// ===============================================
// =											 =
// = 			     DISPAROS					 =
// =											 =
// ===============================================

extern const u8 G_shotR_left1_01[8];
extern const u8 G_shotR_right1_01[8];
extern const u8 G_shotR_left1_02[8];
extern const u8 G_shotR_right1_02[8];
extern const u8 G_shotR_up1_01[16];
extern const u8 G_shotR_up1_02[16];
extern const u8 G_shotR_left2_01[40];
extern const u8 G_shotR_right2_01[40];
extern const u8 G_shotR_left2_02[40];
extern const u8 G_shotR_right2_02[40];
extern const u8 G_shotR_up2_01[48];
extern const u8 G_shotR_up2_02[48];
extern const u8 G_shotR_left3_01[56];
extern const u8 G_shotR_right3_01[56];
extern const u8 G_shotR_left3_02[56];
extern const u8 G_shotR_right3_02[56];
extern const u8 G_shotR_up3_01[64];
extern const u8 G_shotR_up3_02[64];
extern const u8 G_shotB_left1_01[8];
extern const u8 G_shotB_right1_01[8];
extern const u8 G_shotB_left1_02[8];
extern const u8 G_shotB_right1_02[8];
extern const u8 G_shotB_up1_01[16];
extern const u8 G_shotB_up1_02[16];
extern const u8 G_shotB_left2_01[40];
extern const u8 G_shotB_right2_01[40];
extern const u8 G_shotB_left2_02[40];
extern const u8 G_shotB_right2_02[40];
extern const u8 G_shotB_up2_01[48];
extern const u8 G_shotB_up2_02[48];
extern const u8 G_shotB_left3_01[56];
extern const u8 G_shotB_right3_01[56];
extern const u8 G_shotB_left3_02[56];
extern const u8 G_shotB_right3_02[56];
extern const u8 G_shotB_up3_01[64];
extern const u8 G_shotB_up3_02[64];

#endif
