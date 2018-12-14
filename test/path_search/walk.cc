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


#include "walk.h"
#include "position.h"

namespace cacu_mdp_walkman{


void walk::execute(state_base *&current_state_, states *&states_)
{
	current_state_ = states_->at(position::edge_detect(current_state_->set(), move(_direction)));
}


void walk::update_transfer_prob(state_base *&current_state_, transfer_prob *&trans_prob_){

	trans_prob_->add2prob(_offset_prob->prob(0), position::edge_detect(current_state_->set(), _direction));
	vector<arrow> _directions;
	if(_direction != up)
		_directions.push_back(up);
	if(_direction != down)
		_directions.push_back(down);
	if(_direction != left)
		_directions.push_back(left);
	if(_direction != right)
		_directions.push_back(right);
	if(_direction != stop)
		_directions.push_back(stop);

	for(int i = 0; i < _directions.size(); ++i)
		trans_prob_->add2prob(_offset_prob->prob(i + 1) - _offset_prob->prob(i), position::edge_detect(current_state_->set(), _directions[i]));
}

arrow walk::move(arrow direction_)
{
	int p_ = randint(20);
	float_t p = float_t(p_) / 20;
	if (p < _offset_prob->prob(0))
		return direction_;
	else
	{
		LOG_DEBUG("shoot! walk to wrong way!");
		vector<arrow> _directions;
		if(direction_ != up)
			_directions.push_back(up);
		if(direction_ != down)
			_directions.push_back(down);
		if(direction_ != left)
			_directions.push_back(left);
		if(direction_ != right)
			_directions.push_back(right);
		if(direction_ != stop)
			_directions.push_back(stop);

		if(p >= _offset_prob->prob(0) && p < _offset_prob->prob(1))
			return _directions[0];
		else if(p >= _offset_prob->prob(1) && p < _offset_prob->prob(2))
			return _directions[1];
		else if(p >= _offset_prob->prob(2) && p < _offset_prob->prob(3))
			return _directions[2];
		else if(p >= _offset_prob->prob(3) && p < _offset_prob->prob(4))
			return _directions[3];
	}
	return direction_;
}




}
