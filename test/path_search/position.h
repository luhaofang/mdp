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


#ifndef TEST_PATH_SEARCH_POSITION_H_
#define TEST_PATH_SEARCH_POSITION_H_

#include "../../framework/framework.h"
#include "definition.h"

using namespace cacu_mdp;

namespace cacu_mdp_walkman{


class position : public state_base{

public:

	position(dsize_t set_) :
		state_base(set_){
		set_attribute();
	}

	~position(){
		release();
	}

	void set_attribute() override;

	void release() override {
		LOG_INFO("position release!");
	}

	static dsize_t edge_detect(dsize_t set_, arrow direction_);

	static vector<chars_t> get_avaible_directions(state_base *current_state);

	static bool determine(state_base *current_state);

	void set_trap(dsize_t step);

private:


};

}

#endif /* TEST_PATH_SEARCH_WALK_H_ */
