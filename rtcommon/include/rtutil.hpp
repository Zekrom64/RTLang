/*
 * rtutil.hpp
 *
 *  Created on: Mar 18, 2017
 *      Author: Zekrom_64
 */

#ifndef RTUTIL_HPP_
#define RTUTIL_HPP_

#include "rtcommon.hpp"

namespace rt {

RT_PACKED_STRUCT_BEGIN
template<typename T>
struct rt_constarray {
	T* const elements;
	const rt_ulong size;

	rt_constarray(T* const elems, rt_ulong sz) : elements(elems), size(sz) {}

	inline T& operator[](rt_ulong idx) {
		return elements[idx];
	}
} RT_PACKED_STRUCT_ATTR;
RT_PACKED_STRUCT_END

RT_PACKED_STRUCT_BEGIN
struct rt_memmgr {
	void* (*memalloc)(size_t size);
	void* (*memrealloc)(void* ptr, size_t size);
	void (*memfree)(void* ptr);
} RT_PACKED_STRUCT_ATTR;
RT_PACKED_STRUCT_END

}


#endif /* RTUTIL_HPP_ */
