/*
 Copyright (c) 2018, David lu
 All rights reserved.

 Redistribution and use in source and binary forms, with or without
 modification, are permitted provided that the following conditions are met:
 * Redistributions of source code must retain the above copyright
 notice, this list of conditions and the following disclaimer.
 * Redistributions in binary form must reproduce the above copyright
 notice, this list of conditions and the following disclaimer in the
 documentation and/or other materials provided with the distribution.
 * Neither the name of the <organization> nor the
 names of its contributors may be used to endorse or promote products
 derived from this software without specific prior written permission.

 THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY
 EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY
 DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */


#include "position.h"

namespace cacu_mdp_walkman{

void position::set_attribute() {
	if(set() == 0 || set() == 2)
		_weight = -1;
	else if(set() == 9)
		_weight = 1;
	else if(set() == 3)
		_weight = 10;
	else
		_weight = 1;
}


dsize_t position::edge_detect(dsize_t set_, arrow direction_){
	dsize_t h,w;
	h = set_ / _width;
	w = set_ % _width;
	switch(direction_){
		case up:
			if(h == 0)
				return set_;
			else
				return set_ - _width;
		case down:
			if(h == _height - 1)
				return set_;
			else
				return set_ + _width;
		case left:
			if(w == 0)
				return set_;
			else
				return set_ - 1;
		case right:
			if(w == _width - 1)
				return set_;
			else
				return set_ + 1;
		default:
			return set_;
	}

}

vector<chars_t> position::get_avaible_directions(state_base *current_state){
	dsize_t set_ = current_state->set();
	dsize_t h,w;
	h = set_ / _width;
	w = set_ % _width;
	vector<chars_t> directions;
	if(h != 0)
		directions.push_back("up");
	if(h != _height - 1)
		directions.push_back("down");
	if(w != 0)
		directions.push_back("left");
	if(w != _width - 1)
		directions.push_back("right");
	directions.push_back("stop");
	return directions;
}

bool position::determine(state_base *current_state){
	if(current_state->get_weight() < 0)
		return true;
	return false;
}


void position::set_trap(dsize_t step){

	if(step % 2 == 0)
		_weight = -1;
	else
		_weight = 1;
}



}
