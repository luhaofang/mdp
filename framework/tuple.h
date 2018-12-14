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

#ifndef FRAMEWORK_TUPLE_H_
#define FRAMEWORK_TUPLE_H_

#include "../3rdparty/cacu/cacu.h"

using namespace cacu;

namespace cacu_mdp{

class tuple {


public :
	tuple(){
		_states = new states();
		_actions = new actions();
	}

	virtual ~tuple(){
		delete _states;
		delete _actions;
		if(_trans_prob != NULL)
			delete _trans_prob;
		if(_reward != NULL)
			delete _reward;
	}

	inline void initial(){
		_trans_prob = new transfer_prob(_states->size());
		_reward = new reward(_states->size());
	}

	inline void add_state(state_base *state_){
		_states->push_back(state_);
	}

	inline void add_action(chars_t action_name_, action_base *action_){
		_actions->push(action_name_, action_);
	}

	inline state_base *& get_state(dsize_t i) const
	{
		return _states->at(i);
	}

	inline dsize_t state_count() const {
		return _states->size();
	}

	inline dsize_t action_count(){
		return _actions->size();
	}

	inline states *&get_states()
	{
		return _states;
	}

	inline action_base *get_action(chars_t action_name_) const
	{
		if(_actions->contains(action_name_))
			return _actions->at(action_name_);
		else
			LOG_FATAL("There is no action named %s!", action_name_.c_str());
		return NULL;
	}

	inline actions *&get_actions(){
		return _actions;
	}

	inline transfer_prob *&get_transfer_prob(){
		return _trans_prob;
	}

	inline reward *&get_reward(){
		return _reward;
	}

	inline float_t get_omiga(){
		return _omiga;
	}

	inline blob *&environment()
	{
		return _states->get_environment_matrix();
	}


private:

	states *_states = NULL;

	actions *_actions = NULL;

	transfer_prob *_trans_prob = NULL;

	reward *_reward = NULL;

	float_t _omiga = 0.9;

};

}



#endif /* FRAMEWORK_TUPLE_H_ */
