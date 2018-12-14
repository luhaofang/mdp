/*
 * utils.h
 *
 *  Created on: 2018年9月21日
 *      Author: seallhf
 */

#ifndef TEST_PATH_SEARCH_UTILS_H_
#define TEST_PATH_SEARCH_UTILS_H_

#include "definition.h"
#include "position.h"

namespace cacu_mdp_walkman{

chars_t get_action_name(arrow direction_) {
		switch(direction_)
		{
		case up:
			return "up";
			break;
		case down:
			return "down";
			break;
		case left:
			return "left";
			break;
		case right:
			return "right";
			break;
		case stop:
			return "stop";
			break;
		default:
			return "";
		}
	}

	arrow get_direction(state_base *&s1, state_base *&s2) {
		dsize_t res = s2->set() - s1->set();
		if(res == -_width)
			return up;
		else if(res == _width)
			return down;
		else if(res == -1)
			return left;
		else if(res == 1)
			return right;
		else
			return stop;
	}

}

#endif /* TEST_PATH_SEARCH_UTILS_H_ */
