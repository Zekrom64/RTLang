/*
 * memmgt.hpp
 *
 *  Created on: Jan 21, 2018
 *      Author: Zekrom_64
 */

#ifndef UTIL_MEMMGT_HPP_
#define UTIL_MEMMGT_HPP_

#include <cstdlib>

struct MemoryManager {
	typedef void* (*MAllocate)(size_t size);
	typedef void* (*MReallocate)(void* ptr, size_t size);
	typedef void (*MFree)(void* ptr);

	MAllocate Allocate;
	MReallocate Reallocate;
	MFree Free;
};


#endif /* UTIL_MEMMGT_HPP_ */
