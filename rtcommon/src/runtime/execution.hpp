/*
 * execution.hpp
 *
 *  Created on: Jan 20, 2018
 *      Author: Zekrom_64
 */

#ifndef RUNTIME_EXECUTION_HPP_
#define RUNTIME_EXECUTION_HPP_

#include "rtruntime.hpp"
#include "valstack.hpp"
#include <mutex>

class IExecutionContext {
public:
	rt::rt_context_status status;
	std::mutex statusMutex;

	ValueStack stack;
	rt::rt_value registers[256];

	void clear();
};


#endif /* RUNTIME_EXECUTION_HPP_ */
