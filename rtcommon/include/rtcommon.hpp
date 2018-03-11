/*
 * rtcommon.hpp
 *
 *  Created on: Mar 14, 2017
 *      Author: Zekrom_64
 */

#ifndef RTCOMMON_HPP_
#define RTCOMMON_HPP_

#include <cstdint>

// ------------------------
// | Preprocessor defines |
// ------------------------
#ifdef _WIN32
#define RT_EXPORT __declspec(dllexport)
#define RT_IMPORT __declspec(dllimport)
#else
#define RT_EXPORT extern
#define RT_IMPORT extern
#endif
#ifdef __RT_BUILD__
#define RT_API RT_EXPORT __cdecl
#else
#define RT_API RT_IMPORT __cdecl
#endif

#ifdef _WIN32
#define RT_OS_WINDOWS
#elif defined(__linux__)
#define RT_OS_LINUX
#elif defined(__APPLE__)
#define RT_OS_MACOSX
#else
#error "Unsupported platform detected"
#endif

#if defined(__amd64__) || defined(__x86_64__) || defined(_M_X64)
#define RT_ARCH_AMD64
#elif defined(__i386__) || defined(__i386) || defined(_M_IX86) || defined(_X86_)
#define RT_ARCH_IA32
#elif defined(__aarch64__)
#define RT_ARCH_ARM64
#elif defined(__arm__) || defined(_M_ARM)
#define RT_ARCH_ARM
#else
#error "Unsupported architecture detected"
#endif

#if defined(__clang__)
#define RT_COMPILER_CLANG
#elif defined(__MINGW32__)
#define RT_COMPILER_MINGW
#elif defined(__GNUC__)
#define RT_COMPILER_GCC
#elif defined(_MSC_VER)
#define RT_COMPILER_MSVC
#elif defined(__BORLANDC__)
#define RT_COMPILER_BORLAND
#elif defined(__IBMC__)
#define RT_COMPILER_IBM
#elif defined(__INTEL_COMPILER)
#define RT_COMPILER_INTEL
#else
#define RT_COMPILER_OTHER
#endif

#if defined(RT_COMPILER_CLANG) || defined(RT_COMPILER_MINGW) || defined(RT_COMPILER_GCC)
#define RT_COMPILER_FAMILY_GNU
#elif defined(RT_COMPILER_MSVC)
#define RT_COMPILER_FAMILY_MSVC
#else
#define RT_COMPILER_FAMILY_OTHER
#endif

#if !defined(RT_COMPILER_FAMILY_GNU)
RT_WARN("Non-GNU compiler detected, things may not work!")
#endif

#include "rtcppcompat.hpp"

namespace rt {

// ------------
// | Typedefs |
// ------------
/** An unsigned 8-bit integer */
typedef uint8_t rt_ubyte;
/** A Signed 8-bit integer */
typedef int8_t rt_byte;
/** An unsigned 8-bit integer */
typedef uint16_t rt_ushort;
typedef int16_t rt_short;
/** An unsigned 8-bit integer */
typedef uint32_t rt_uint;
typedef int32_t rt_int;
/** An unsigned 8-bit integer */
typedef uint64_t rt_ulong;
typedef int64_t rt_long;
/** A 32-bit IEEE 754 single precision floating-point number */
typedef float rt_float;
/** A 64-bit IEEE 754 double precision floating-point number */
typedef double rt_double;
/** A boolean value of implementation-defined size */
typedef bool rt_bool;
/** Verbose form of rt_bool */
typedef rt_bool rt_boolean;

/** A null-terminated string of 8-bit UTF-8 characters */
typedef const char* rt_cstring;
/** A null-terminated string of 16-bit UTF-8 characters */
typedef const char16_t* rt_cstring16;
/** A null-terminated string of 32-bit UTF-8 characters */
typedef const char32_t* rt_cstring32;

/** Native memory allocation callback */
typedef void* rt_malloc(size_t size);

// -----------
// | Predefs |
// -----------
// rtruntime.hpp
struct rt_runtime_args;
class rt_runtime;
struct rt_value;
class rt_context;
struct rt_context_state;

// rttype.hpp
class rt_type;
class rt_type_system;

// rtoop.hpp
class rt_field;
class rt_method;
struct rt_methodsig;

// rtutil.hpp
template<typename T>
struct rt_constarray;
struct rt_memmgr;

// rtinterop.hpp
class rt_callingconv;
class rt_nativelib;
class rt_marshal;

extern "C" {

RT_API rt_runtime* rtCreateRuntime(rt_runtime_args* args);
RT_API rt_constarray<rt_runtime*>* rtEnumerateRuntimes(rt_memmgr* mem);
RT_API bool rtDestroyRuntime(rt_runtime* runtime);

}

}


#endif /* RTCOMMON_HPP_ */
