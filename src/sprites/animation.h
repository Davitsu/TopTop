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

#ifndef _ANIMATION_H_
#define _ANIMATION_H_

#include <types.h>

// Possible statuses of an animation
typedef enum {
   as_null = 0, 	  // We require this to represent a null status
   as_play = 1, 	  // Playing till the last frame
   as_cycle,   	  // Playing continuosly
   as_pause,    	  // Paused, waiting to continue
   as_end       	  // Animation has ended
} TAnimStatus;

// Description of an animation frame
typedef struct {
   u8* sprite;        // Sprite associated to this frame
   u8  time;          // Time that the sprite should be shown
} TAnimFrame;

// Describes an Animation as a secuence of sprites, controlled by time
//   Time is measured in main loop cycles
typedef struct {
   TAnimFrame**  frames;    // Vector containing all the frames of the animation
   u8            frame_id;  // Index of the current frame
   u8            time;      // Remaining time for this frame
   TAnimStatus   status;    // Status of the animation
} TAnimation;

#define ANI_FPS 12
#define ANI_FPS_RUN 5

//Animaciones Chica
extern const TAnimFrame G_allAniHeroR[28];             // guarda todos los frames de todas las animaciones

extern TAnimFrame* const G_aniHeroR_idle_left[3];     // declaramos las animaciones, se le pasa el numero de frames + 1(null)   
extern TAnimFrame* const G_aniHeroR_idle_right[3];
extern TAnimFrame* const G_aniHeroR_run_left[5];
extern TAnimFrame* const G_aniHeroR_run_right[5];
extern TAnimFrame* const G_aniHeroR_jump_left[2];
extern TAnimFrame* const G_aniHeroR_jump_right[2];
extern TAnimFrame* const G_aniHeroR_fall_left[2];
extern TAnimFrame* const G_aniHeroR_fall_right[2];
extern TAnimFrame* const G_aniHeroR_duck_left[3];
extern TAnimFrame* const G_aniHeroR_duck_right[3];
extern TAnimFrame* const G_aniHeroR_duckrun_left[5];
extern TAnimFrame* const G_aniHeroR_duckrun_right[5];

extern TAnimFrame** const g_aniHeroR[6][2];           // primer valor que se le pasa -> numero de animaciones, segundo valor -> numero de lados (siempre 2: izquierda y derecha)

//Animaciones Chico
extern const TAnimFrame G_allAniHeroB[28];

extern TAnimFrame* const G_aniHeroB_idle_left[3];
extern TAnimFrame* const G_aniHeroB_idle_right[3];
extern TAnimFrame* const G_aniHeroB_run_left[5];
extern TAnimFrame* const G_aniHeroB_run_right[5];
extern TAnimFrame* const G_aniHeroB_jump_left[2];
extern TAnimFrame* const G_aniHeroB_jump_right[2];
extern TAnimFrame* const G_aniHeroB_fall_left[2];
extern TAnimFrame* const G_aniHeroB_fall_right[2];
extern TAnimFrame* const G_aniHeroB_duck_left[3];
extern TAnimFrame* const G_aniHeroB_duck_right[3];
extern TAnimFrame* const G_aniHeroB_duckrun_left[5];
extern TAnimFrame* const G_aniHeroB_duckrun_right[5];

extern TAnimFrame** const g_aniHeroB[6][2];
 
// UTILITY FUNCTIONS
i8 updateAnimation(TAnimation* anim, TAnimFrame** newAnim, TAnimStatus newStatus);



#endif