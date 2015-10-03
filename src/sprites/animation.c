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

#include <cpctelera.h>
#include "animation.h"
#include "../sprites/sprites.h"

// Animaciones Chica
const TAnimFrame G_allAniHeroR[16] = {
	{ G_heroR_idle_left01,  ANI_FPS }, 			// 0// << Idle Left
	{ G_heroR_idle_left02,  ANI_FPS }, 			// 1// |
	{ G_heroR_idle_right01, ANI_FPS }, 			// 2// << Idle Right
	{ G_heroR_idle_right02, ANI_FPS },  		// 3// |
	{ G_heroR_run_left01, ANI_FPS_RUN },  		// 4// << Run Left
	{ G_heroR_run_left02, ANI_FPS_RUN },  		// 5// |
	{ G_heroR_run_left03, ANI_FPS_RUN },  		// 6// |
	{ G_heroR_run_left04, ANI_FPS_RUN },  		// 7// |
	{ G_heroR_run_right01, ANI_FPS_RUN },  		// 8// << Run Right
	{ G_heroR_run_right02, ANI_FPS_RUN },  		// 9// |
	{ G_heroR_run_right03, ANI_FPS_RUN },  		//10// |
	{ G_heroR_run_right04, ANI_FPS_RUN },  		//11// |
	{ G_heroR_jump_left01, ANI_FPS },  			//12// << Jump Left
	{ G_heroR_jump_right01, ANI_FPS },  		//13// << Jump Right
	{ G_heroR_fall_left01, ANI_FPS },  			//14// << Fall Left
	{ G_heroR_fall_right01, ANI_FPS }	  		//15// << Fall Right
};

#define A_HR G_allAniHeroR

TAnimFrame*  const G_aniHeroR_idle_left[3]    = { &A_HR[0], &A_HR[1], 0 };
TAnimFrame*  const G_aniHeroR_idle_right[3]   = { &A_HR[2], &A_HR[3], 0 };
TAnimFrame*  const G_aniHeroR_run_left[5]     = { &A_HR[4], &A_HR[5], &A_HR[6], &A_HR[7], 0 };
TAnimFrame*  const G_aniHeroR_run_right[5]    = { &A_HR[8], &A_HR[9], &A_HR[10], &A_HR[11], 0 };
TAnimFrame*  const G_aniHeroR_jump_left[2]    = { &A_HR[12], 0 };
TAnimFrame*  const G_aniHeroR_jump_right[2]   = { &A_HR[13], 0 };
TAnimFrame*  const G_aniHeroR_fall_left[2]    = { &A_HR[14], 0 };
TAnimFrame*  const G_aniHeroR_fall_right[2]   = { &A_HR[15], 0 };

TAnimFrame** const g_aniHeroR[4][2] = {
   {  G_aniHeroR_idle_left, G_aniHeroR_idle_right  }, 		// STATE 0 = IDLE
   {  G_aniHeroR_run_left,  G_aniHeroR_run_right   },  		// STATE 1 = RUN
   {  G_aniHeroR_jump_left,  G_aniHeroR_jump_right },  		// STATE 2 = JUMP
   {  G_aniHeroR_fall_left,  G_aniHeroR_fall_right } 		// STATE 3 = FALL
};

#undef A_HR

// Animaciones Chico
const TAnimFrame G_allAniHeroB[16] = {
    { G_heroB_idle_left01,  ANI_FPS }, 			// 0// << Idle Left
    { G_heroB_idle_left02,  ANI_FPS }, 			// 1// |
    { G_heroB_idle_right01, ANI_FPS }, 			// 2// << Idle Right
    { G_heroB_idle_right02, ANI_FPS },  		// 3// |
    { G_heroB_run_left01, ANI_FPS_RUN },  		// 4// << Run Left
	{ G_heroB_run_left02, ANI_FPS_RUN },  		// 5// |
	{ G_heroB_run_left03, ANI_FPS_RUN },  		// 6// |
	{ G_heroB_run_left04, ANI_FPS_RUN },  		// 7// |
	{ G_heroB_run_right01, ANI_FPS_RUN },  		// 8// << Run Right
	{ G_heroB_run_right02, ANI_FPS_RUN },  		// 9// |
	{ G_heroB_run_right03, ANI_FPS_RUN },  		//10// |
	{ G_heroB_run_right04, ANI_FPS_RUN },  		//11// |
	{ G_heroB_jump_left01, ANI_FPS },  			//12// << Jump Left
	{ G_heroB_jump_right01, ANI_FPS },  		//13// << Jump Right
	{ G_heroB_fall_left01, ANI_FPS },  			//14// << Fall Left
	{ G_heroB_fall_right01, ANI_FPS }  			//15// << Fall Right
};

#define A_HB G_allAniHeroB

TAnimFrame*  const G_aniHeroB_idle_left[3]    = { &A_HB[0], &A_HB[1], 0 };
TAnimFrame*  const G_aniHeroB_idle_right[3]   = { &A_HB[2], &A_HB[3], 0 };
TAnimFrame*  const G_aniHeroB_run_left[5]     = { &A_HB[4], &A_HB[5], &A_HB[6], &A_HB[7], 0 };
TAnimFrame*  const G_aniHeroB_run_right[5]    = { &A_HB[8], &A_HB[9], &A_HB[10], &A_HB[11], 0 };
TAnimFrame*  const G_aniHeroB_jump_left[2]    = { &A_HB[12], 0 };
TAnimFrame*  const G_aniHeroB_jump_right[2]   = { &A_HB[13], 0 };
TAnimFrame*  const G_aniHeroB_fall_left[2]    = { &A_HB[14], 0 };
TAnimFrame*  const G_aniHeroB_fall_right[2]   = { &A_HB[15], 0 };

TAnimFrame** const g_aniHeroB[4][2] = {
   {  G_aniHeroB_idle_left, G_aniHeroB_idle_right  }, 		// STATE 0 = IDLE
   {  G_aniHeroB_run_left,  G_aniHeroB_run_right   },  		// STATE 1 = RUN
   {  G_aniHeroB_jump_left,  G_aniHeroB_jump_right },  		// STATE 2 = JUMP
   {  G_aniHeroB_fall_left,  G_aniHeroB_fall_right }		// STATE 3 = FALL
};

#undef A_HB

i8 updateAnimation(TAnimation* anim, TAnimFrame** newAnim, TAnimStatus newStatus) {
	i8 newframe = 0;

	// If new animation, set it!
	if(newAnim) {
		anim->frames = newAnim;    // Sets the new animation to the entity
		anim->frame_id = 0;        // First frame of the animation

		// Set time on non void animations
		if(newAnim[0])
			anim->time = newAnim[0]->time; // Animation is at its initial timestep

      newframe = 1; // We have changed animation, an that makes this a new frame
    }

	// If new animation status, set it!
	if (newStatus)
		anim->status = newStatus;  // Set the initial status for the animation    

	// Update only if animation is not paused or finished
	if (anim->status != as_pause && anim->status != as_end) {

		// Update time and, If time has finished for this frame, get next
		if (!--anim->time) {
			TAnimFrame* frame;

			// Next frame
			newframe = 1;
			frame = anim->frames[ ++anim->frame_id ];

			// If frame is not null, we have a new frame, else animation may have ended or may recycle
			if (frame) {
				// New frame values
				anim->time = frame->time;
			} else if ( anim->status == as_cycle ) {
				// Recycle to first frame
				anim->frame_id = 0;
				anim->time     = anim->frames[0]->time;
			} else {
				// End animation (leaving last frame_id visible)
				--anim->frame_id;
				anim->status = as_end;
			}
		}
	}

	// Report if a new frame has started
	return newframe;
}