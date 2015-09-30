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
   as_cycle,   	 	  // Playing continuosly
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

//Animaciones Chica
extern const TAnimFrame G_allAniHeroR[4];

extern TAnimFrame* const G_aniHeroR_idle_left[3];
extern TAnimFrame* const G_aniHeroR_idle_right[3];

extern TAnimFrame** const g_aniHeroR[1][2];

//Animaciones Chico
extern const TAnimFrame G_allAniHeroB[4];

extern TAnimFrame* const G_aniHeroB_idle_left[3];
extern TAnimFrame* const G_aniHeroB_idle_right[3];

extern TAnimFrame** const g_aniHeroB[1][2];
 
// UTILITY FUNCTIONS
i8 updateAnimation(TAnimation* anim, TAnimFrame** newAnim, TAnimStatus newStatus);



#endif