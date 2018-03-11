/*
 * runtime.cpp
 *
 *  Created on: Jan 21, 2018
 *      Author: Zekrom_64
 */

#include "runtime.hpp"

Runtime::Runtime() {

}

rt::rt_constarray<rt::rt_context*> Runtime::enumerateContexts(rt::rt_malloc memAlloc) {
	uint32_t nContexts = 0;
	rt::rt_context** contextsPtr = nullptr;
	contextsMutex.lock();
	nContexts = contexts.size();
	size_t dataSize = sizeof(rt::rt_context*) * nContexts;
	contextsPtr = (rt::rt_context**)memAlloc(sizeof(rt::rt_context*) * nContexts);
	if (contextsPtr == nullptr) return { nullptr, 0 };
	memcpy(contextsPtr, contexts.data(), dataSize);
	contextsMutex.unlock();
	return rt::rt_constarray<rt::rt_context*>(contextsPtr, nContexts);
}

rt::rt_context* Runtime::createContext(rt::rt_cstring threadName) {
	return nullptr; // TODO
}

rt::rt_type_system* Runtime::getTypeSystem() {
	return nullptr; // TODO
}
