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