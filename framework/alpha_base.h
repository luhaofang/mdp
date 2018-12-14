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


#ifndef FRAMEWORK_ALPHA_BASE_H_
#define FRAMEWORK_ALPHA_BASE_H_


namespace cacu_mdp{

class alpha_base{

public:

	alpha_base(state_base *&init_state_, tuple *&strategy_){
		_current_state = init_state_;
		_strategy = strategy_;
	}

	virtual ~alpha_base(){
		delete _strategy;
	}

	virtual void update_states() = 0;

	virtual void update_transfer_prob(action_base *action_) = 0;

	virtual void update_reward(action_base *action_) = 0;

	virtual void Do(action_base *action_) = 0;

	virtual void solve() = 0;

	virtual void recursive_solve(state_base *current_state_, state_base *end_point, dsize_t deep_, dsize_t current_deep_, dsize_t step) = 0;

	virtual void compute_trans_prob(state_base *&current_state_) = 0;

	inline void update_transfer_prob_(chars_t action_name_){
		update_transfer_prob(_strategy->get_action(action_name_));
	}

	inline void update_reward_(chars_t action_name_){
		update_reward(_strategy->get_action(action_name_));
	}

	inline void Do_(chars_t action_name_){
		LOG_INFO("execute action: %s", action_name_.c_str());
		Do(_strategy->get_action(action_name_));
	}

	inline actions *&get_actions(){
		return _strategy->get_actions();
	}

	inline transfer_prob *&get_transfer_prob(){
		return _strategy->get_transfer_prob();
	}

	inline state_base *&get_current_state(){
		return _current_state;
	}


protected:

	state_base *_current_state = NULL;

	tuple *_strategy = NULL;

};

}




#endif /* FRAMEWORK_ACTION_BASE_H_ */
