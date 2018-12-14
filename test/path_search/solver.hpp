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


#ifndef TEST_PATH_SEARCH_SOLVER_HPP_
#define TEST_PATH_SEARCH_SOLVER_HPP_


#include "position.h"
#include "walk.h"
#include "agent.hpp"

using namespace cacu_mdp;

namespace cacu_mdp_walkman{

void model()
{
	set_rand_seed();

	cacu_mdp::tuple *_tuple = new cacu_mdp::tuple();
	for (int i = 0 ; i < _width * _height; ++i)
		_tuple->add_state(new position(i));

	vec_t prob(5);
	prob[0] = 0.8;
	prob[1] = 0.85;
	prob[2] = 0.9;
	prob[3] = 0.95;
	prob[4] = 1;

	_tuple->add_action("left", new walk(left, prob));
	_tuple->add_action("right", new walk(right, prob));
	_tuple->add_action("up", new walk(up, prob));
	_tuple->add_action("down", new walk(down, prob));
	_tuple->add_action("stop", new walk(stop, prob));

	_tuple->initial();

	agent *alpha = new agent(_tuple->get_state(4), _tuple);
	alpha->solve();


}

}



#endif /* TEST_PATH_SEARCH_SOLVER_HPP_ */
