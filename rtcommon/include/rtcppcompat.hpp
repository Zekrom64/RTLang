/*
 * rtcppcompat.hpp
 *
 *  Created on: Jan 20, 2018
 *      Author: Zekrom_64
 */

#ifndef RTCPPCOMPAT_HPP_
#define RTCPPCOMPAT_HPP_

#include "rtcommon.hpp"

/* Portable macros/values to work across C++ compilers:
 *
 * Constant values:
 *  RT_CPLUSPLUS_PRE98 - Value of __cplusplus for pre-C++98 versions
 *  RT_CPLUSPLUS_98 - Value of __cplusplus for C++98
 *  RT_CPLUSPLUS_11 - Value of __cplusplus for C++11
 *  RT_CPLUSPLUS_14 - Value of __cplusplus for C++14
 *  RT_CPLUSPLUS_17 - Value of __cplusplus for C++17
 *  RT_HAS_CPP98 - Boolean value if C++98 is supported
 *  RT_HAS_CPP11 - Boolean value if C++11 is supported
 *  RT_HAS_CPP14 - Boolean value if C++14 is supported
 *  RT_HAS_CPP17 - Boolean value if C++17 is supported
 *
 * Attributes:
 *  Packed structs:
 *  	RT_PACKED_STRUCT_BEGIN - Put before the struct definition
 *  	RT_PACKED_STRUCT_END - Put after the struct definition
 *  	RT_PACKED_STRUCT_ATTR - Put between closing brace and semicolon
 *  	Example:
 *  		RT_PACKED_STRUCT_BEGIN
 *  		struct foo {
 *
 *  		} RT_PACKED_STRUCT_ATTR;
 *  		RT_PACKED_STRUCT_END
 *
 * Macros:
 *  RT_STRINGIFY(X) - Converts 'X' to a string
 *  RT_WARN(X) - Prints a warning message when compiled
 *  RT_DEPRECATED(MSG) - Flags the next symbol as deprecated, with the given message as the reason
 *
 */

// C++ version defines
#define RT_CPLUSPLUS_PRE98 1
#define RT_CPLUSPLUS_98 199711L
#define RT_CPLUSPLUS_11 201103L
#define RT_CPLUSPLUS_14 201402L
#define RT_CPLUSPLUS_17 201703L

#if __cplusplus >= RT_CPLUSPLUS_17
#define RT_HAS_CPP17 true
#else
#define RT_HAS_CPP17 false
#endif

#if __cplusplus >= RT_CPLUSPLUS_14
#define RT_HAS_CPP14 true
#else
#define RT_HAS_CPP14 false
#endif

#if __cplusplus >= RT_CPLUSPLUS_11
#define RT_HAS_CPP11 true
#else
#define RT_HAS_CPP11 false
#endif

#if __cplusplus >= RT_CPLUSPLUS_98
#define RT_HAS_CPP98 true
#else
#define RT_HAS_CPP98 false
#endif

// Stringification macro
#define RT_STRINGIFY_HELPER(X) #X
#define RT_STRINGIFY(X) RT_STRINGIFY_HELPER(X)

// C++14 Deprecated macro
#if __cplusplus >= RT_CPLUSPLUS_14
#define RT_DEPRECATED(MSG) [[deprecated(MSG)]]
#endif

// MSVC++ specific macro versions
#ifdef RT_COMPILER_FAMILY_MSVC

#define RT_WARN(X) __Pragma(message (__FILE__ "(" RT_STRINGIFY(__LINE__) ") : Warning: " #X))
#define RT_PACKED_STRUCT_BEGIN __pragma(pack(push,1))
#define RT_PACKED_STRUCT_ATTR
#define RT_PACKED_STRUCT_END __pragma(pop())

#ifndef RT_DEPRECATED
#define RT_DEPRECATED(MSG) RT_WARN("Symbol marked as deprecated: " MSG) __declspec(deprecated)
#endif

// GNU C/C++ specific macro versions
#elif defined(RT_COMPILER_FAMILY_GNU)

#define __RT_GNUC_DO_PRAGMA(X) _Pragma(#X)
#define RT_WARN(X) __RT_GNUC_DO_PRAGMA(message (__FILE__ ":" RT_STRINGIFY(__LINE__) ": warning: " X))
#define RT_PACKED_STRUCT_BEGIN
#define RT_PACKED_STRUCT_ATTR __attribute__((packed))
#define RT_PACKED_STRUCT_END

#ifndef RT_DEPRECATED
#define RT_DEPRECATED(MSG) RT_WARN("Symbol marked as deprecated: " MSG) __attribute__((deprecated))
#endif

// Unknown compiler macros, define so things don't completely break during compilation
#else

#define RT_WARN(X)
#define RT_PACKED_STRUCT_BEGIN
#define RT_PACKED_STRUCT_ATTR
#define RT_PACKED_STRUCT_END

#ifndef RT_DEPRECATED
#define RT_DEPRECATED(MSG)
#endif

#endif


#endif /* RTCPPCOMPAT_HPP_ */
