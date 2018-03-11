/*
 * runtime.hpp
 *
 *  Created on: Jan 21, 2018
 *      Author: Zekrom_64
 */

#ifndef RUNTIME_RUNTIME_HPP_
#define RUNTIME_RUNTIME_HPP_


#include "rtruntime.hpp"

#include "context.hpp"

#include <vector>
#include <mutex>

class Runtime : public rt::rt_runtime {
public:
	std::vector<RuntimeContext*> contexts;
	std::mutex contextsMutex;
	Runtime();
	~Runtime(); // @suppress("Class has a virtual method and non-virtual destructor")
	virtual rt::rt_context* createContext(rt::rt_cstring threadName);
	virtual rt::rt_constarray<rt::rt_context*> enumerateContexts(rt::rt_malloc memAlloc);
	virtual rt::rt_type_system* getTypeSystem();
};


#endif /* RUNTIME_RUNTIME_HPP_ */
