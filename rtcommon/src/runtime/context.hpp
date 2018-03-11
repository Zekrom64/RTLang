/*
 * context.hpp
 *
 *  Created on: Jan 20, 2018
 *      Author: Zekrom_64
 */

#ifndef RUNTIME_CONTEXT_HPP_
#define RUNTIME_CONTEXT_HPP_


#include "rtruntime.hpp"
#include "execution.hpp"

class RuntimeContext : public rt::rt_context { // @suppress("Class has a virtual method and non-virtual destructor")
public:
	rt::rt_runtime* const runtime;
	IExecutionContext* const execution;

	RuntimeContext(rt::rt_runtime* run, IExecutionContext* exe) : runtime(run), execution(exe) {
		execution->clear();
	}
	~RuntimeContext() {}

	virtual rt::rt_runtime* getRuntime() {
		return runtime;
	}

	virtual rt::rt_context_status getStatus() {
		execution->statusMutex.lock();
		rt::rt_context_status status = execution->status;
		execution->statusMutex.unlock();
		return status;
	}

	virtual void loadRegister(uint8_t index, rt::rt_value val) {
		execution->statusMutex.lock();
		if (execution->status == rt::RT_CONTEXT_STATUS_STOPPED) {
			execution->registers[index] = val;
		}
		execution->statusMutex.unlock();
	}

	virtual rt::rt_value getRegister(uint8_t index) {
		rt::rt_value val = RT_VALUE_NULL;
		execution->statusMutex.lock();
		if (execution->status == rt::RT_CONTEXT_STATUS_STOPPED) {
			val = execution->registers[index];
		}
		execution->statusMutex.unlock();
		return val;
	}

	virtual rt::rt_bool pushValue(rt::rt_value val) {
		rt::rt_bool overflow;
		execution->statusMutex.lock();
		if (execution->status == rt::RT_CONTEXT_STATUS_STOPPED) {
			overflow = execution->stack.push(val);
		}
		execution->statusMutex.unlock();
		return overflow;
	}

	virtual rt::rt_value popValue(bool* underflow) {
		rt::rt_value val = RT_VALUE_NULL;
		execution->statusMutex.lock();
		if (execution->status == rt::RT_CONTEXT_STATUS_STOPPED) {
			ValueStack& stack = execution->stack;
			val = stack.pop(underflow);
		}
		execution->statusMutex.unlock();
		return val;
	}

	virtual void invoke(rt::rt_method* method, bool isInstance, uint8_t instIndex) {

	}

	virtual void doNativeTry(rt::rt_type* catchType, rt::rt_native_catch catcher, rt::rt_native_finally finally) {

	}

	virtual void throwException(rt::rt_value err) {

	}
};


#endif /* RUNTIME_CONTEXT_HPP_ */
