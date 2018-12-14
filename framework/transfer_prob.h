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

#ifndef FRAMEWORK_TRANSFER_PROB_H_
#define FRAMEWORK_TRANSFER_PROB_H_

#include "../3rdparty/cacu/framework/blob.h"

using namespace cacu;

namespace cacu_mdp{

class transfer_prob{


public:

	transfer_prob(dsize_t states_count_){
		_prob_data = new blob(states_count_,1,1,1,0,test);
	}

	~transfer_prob(){
		delete _prob_data;
	}

	inline float_t *prob_p(dsize_t i)
	{
		CHECK_LT_OP(i, _prob_data->count(),"size must < %d vs %d!", _prob_data->count(), i);
		return (_prob_data->p_data(i));
	}

	inline float_t prob(dsize_t i)
	{
		CHECK_LT_OP(i, _prob_data->count(),"size must < %d vs %d!", _prob_data->count(), i);
		return *(_prob_data->p_data(i));
	}


	inline void set_probs(vec_t &data_){
		_prob_data->copy2data(data_);
	}

	inline void add2prob(float_t prob_, dsize_t i)
	{
		*(_prob_data->p_data(i)) += prob_;
	}

	inline float_t *s_data(){
		return _prob_data->s_data();
	}

	inline dsize_t count(){
		return _prob_data->count();
	}

	inline void _RESET_DATA(){
		_prob_data->_RESET_DATA();
	}

protected:

	blob *_prob_data = NULL;


};

}



#endif /* FRAMEWORK_TRANSFER_PROB_H_ */
