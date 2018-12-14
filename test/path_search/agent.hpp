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

#ifndef TEST_PATH_SEARCH_AGENT_HPP_
#define TEST_PATH_SEARCH_AGENT_HPP_

#include "../../framework/framework.h"

#include "utils.h"

using namespace cacu_mdp;

namespace cacu_mdp_walkman{


class agent : public alpha_base{


public:


	agent(state_base *&init_state_, cacu_mdp::tuple *&strategy_)
		: alpha_base(init_state_, strategy_){

	}
	~agent(){}

	void update_states() override {

	}

	void update_transfer_prob(action_base *action_) override {

	}

	void compute_trans_prob(state_base *&current_state_) override {
		_strategy->get_transfer_prob()->_RESET_DATA();
		vector<chars_t> directions = position::get_avaible_directions(current_state_);
		for(int i = 0 ; i < directions.size(); ++i)
		{
			_strategy->get_action(directions[i])->update_transfer_prob(current_state_, _strategy->get_transfer_prob());
		}
		cacu_scalex(_strategy->get_transfer_prob()->s_data(), _strategy->get_transfer_prob()->count(), 1.0 / directions.size());
	}

	void update_reward(action_base *action_) override {

	}


	void Do(action_base *action_) override {
		action_->execute(_current_state,_strategy->get_states());
		LOG_INFO("current position : (%d, %d)", _current_state->set() / _width, _current_state->set()% _width);
	}

	void recursive_solve(state_base *current_state_, state_base *end_point, dsize_t deep_, dsize_t current_deep_, dsize_t step) override {
		if(deep_ == current_deep_)
			return ;
		if(current_state_->set() == end_point->set())
			return ;
		else
		{

			_strategy->get_states()->create_matrix();
			compute_trans_prob(current_state_);

			cacu_ssx(_strategy->environment()->s_data(), _strategy->get_transfer_prob()->count(), _strategy->get_transfer_prob()->s_data());

			cacu_scalex(_strategy->get_transfer_prob()->s_data(), _strategy->get_transfer_prob()->count(), pow(_strategy->get_omiga(), current_deep_));
			cacu_saxpby(_strategy->get_transfer_prob()->s_data(), 1, _strategy->get_reward()->s_data(), 1, _strategy->get_transfer_prob()->count());
			for(int i = 0 ; i < _strategy->get_transfer_prob()->count(); ++i)
			{
				if(_strategy->get_transfer_prob()->prob(i) != 0)
					recursive_solve(_strategy->get_state(i), end_point, deep_, current_deep_ + 1, step);
			}
		}
	}

	void solve() override {

		int i = 0;
		chars_t direction_;
		while(true)
		{
			_strategy->get_states()->create_matrix();
			recursive_solve(_current_state, _strategy->get_state(3), 7, 0, i);
			//cacu_print(_reward->s_data(),_reward->count());
			compute_trans_prob(_current_state);
			mask_vector(_strategy->get_transfer_prob()->s_data(), _strategy->get_transfer_prob()->count(), _strategy->get_transfer_prob()->s_data());
			//_transfer_prob->s_data()[_current_state->set()] *= 0.1;
			cacu_ssx(_strategy->get_transfer_prob()->s_data(), _strategy->get_transfer_prob()->count(), _strategy->get_reward()->s_data());

			direction_ = get_action_name(get_direction(_current_state, _strategy->get_state(argmax(_strategy->get_reward()->s_data(),
					_strategy->get_reward()->count()))));
			cacu_print_matrix(_strategy->get_reward()->s_data(), _width, _height);
			LOG_DEBUG("I'm standing at (%d, %d) now, should go %s way!", _current_state->set()/ _width,
					_current_state->set()% _width, direction_.c_str());
			Do_(direction_);
			_strategy->get_reward()->_RESET_DATA();

			i++;
			if(_current_state->set() == 3)
				break;
		}
		LOG_DEBUG("I'm a sb, walking out of the trap, after %d steps!", i);
	}



};





}


#endif /* TEST_PATH_SEARCH_AGANT_HPP_ */
