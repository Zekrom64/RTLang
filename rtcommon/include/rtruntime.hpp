/*
 * rtruntime.hpp
 *
 *  Created on: Mar 14, 2017
 *      Author: Zekrom_64
 */

#ifndef RTRUNTIME_HPP_
#define RTRUNTIME_HPP_


#include "rtcommon.hpp"
#include "rttype.hpp"

namespace rt {

/** Base constant info structure for runtime values. This
 * will contain at minimum the value's type and can be
 * reinterpreted as more specific constant info for
 * more information.
 */
RT_PACKED_STRUCT_BEGIN
struct rt_constinfo {
	rt_type* const type;
	rt_constinfo(rt_type* _type) : type(_type) { }
} RT_PACKED_STRUCT_ATTR;
RT_PACKED_STRUCT_END

/** Struct containing a generic value used in the runtime. The value contains
 * a pointer to constant information describing the value, and an
 * implementation-dependent sized field that can interpret the value in
 * different ways. The value field is always at least 64-bits large, but
 * may be larger depending on pointer size. A null value will have a null
 * pointer in place of constant info.
 */
RT_PACKED_STRUCT_BEGIN
struct rt_value {
private:
	rt_constinfo* constinfo;
public:
	union {
		uintptr_t asUIntPtr;
		rt_bool asBool;
		rt_byte asByte;
		rt_ubyte asUByte;
		rt_short asShort;
		rt_ushort asUShort;
		rt_int asInt;
		rt_uint asUInt;
		rt_long asLong;
		rt_ulong asULong;
		rt_float asFloat;
		rt_double asDouble;
		rt_cstring asCString;
		rt_cstring16 asCString16;
		rt_cstring32 asCString32;
		void* asPointer;
		rt_byte* asBytePointer;
	} value ;
	inline bool isNull() {
		return constinfo == nullptr;
	}
	rt_value(const rt_value& val) : constinfo(val.constinfo), value(val.value) { }
	rt_value(rt_constinfo* _constinfo) : constinfo(_constinfo) { }
	inline rt_constinfo* getConstInfo() { return constinfo; }
	inline rt_value& operator=(rt_value val) {
		constinfo = val.constinfo;
		value = val.value;
		return *this;
	}
} RT_PACKED_STRUCT_ATTR;
RT_PACKED_STRUCT_END

#define RT_VALUE_NULL (rt::rt_value(nullptr))

/** Constant info for a pointer value. Adds info for the
 * type of element being pointed to, a function value to call
 * to free the memory (may be null if unmanaged), and constant
 * pointers to the base and limit of memory this pointer can
 * access.
 */
RT_PACKED_STRUCT_BEGIN
struct rt_constinfo_pointer : public rt_constinfo {
	rt_type* const elementType;
	const rt_value releaser;
	void* const base;
	void* const limit;
	rt_constinfo_pointer(rt_type* _type, rt_type* _elemType, rt_value _releaser, void* _base, void* _limit) : rt_constinfo(_type),
		elementType(_elemType), releaser(_releaser), base(_base), limit(_limit) { }
} RT_PACKED_STRUCT_ATTR;
RT_PACKED_STRUCT_END

/** Constant info for an array. Adds info for the
 * type of element the array may hold and the length
 * of the array.
 */
RT_PACKED_STRUCT_BEGIN
struct rt_constinfo_array : public rt_constinfo {
	rt_type* const elementType;
	const rt_ulong length;
	rt_constinfo_array(rt_type* _type, rt_type* _elemType, rt_ulong _length) : rt_constinfo(_type), elementType(_elemType), length(_length) { }
} RT_PACKED_STRUCT_ATTR;
RT_PACKED_STRUCT_END

/** Constant info for a function. Adds info for the
 * signature of the function and an optional value
 * for the instance if the function is a method
 * of a value instance.
 */
RT_PACKED_STRUCT_BEGIN
struct rt_constinfo_function : public rt_constinfo {
	rt_methodsig* const signature;
	const rt_value instance;
	rt_constinfo_function(rt_type* _type, rt_methodsig* _signature, rt_value _instance) : rt_constinfo(_type), signature(_signature), instance(_instance) { }
} RT_PACKED_STRUCT_ATTR;
RT_PACKED_STRUCT_END

/** Constant info for an object. Adds info for
 * specific types of any generics specified in
 * the class.
 */
RT_PACKED_STRUCT_BEGIN
struct rt_constinfo_object : public rt_constinfo {
	const rt_constarray<rt_type*> genericValues;
	rt_constinfo_object(rt_type* _type, rt_constarray<rt_type*> _genericValues) : rt_constinfo(_type), genericValues(_genericValues) { }
} RT_PACKED_STRUCT_ATTR;
RT_PACKED_STRUCT_END

/** Constant info for a struct. Adds info for
 * specific types of any generics specified in
 * the struct.
 */
RT_PACKED_STRUCT_BEGIN
struct rt_constinfo_struct : public rt_constinfo {
	const rt_constarray<rt_type*> genericValues;
	rt_constinfo_struct(rt_type* _type, rt_constarray<rt_type*> _genericValues) : rt_constinfo(_type), genericValues(_genericValues) { }
} RT_PACKED_STRUCT_ATTR;
RT_PACKED_STRUCT_END

/** Struct containing arguments to pass to a
 * runtime during its creation.
 */
RT_PACKED_STRUCT_BEGIN
struct rt_runtime_args {
	const char** argv;
	uint32_t argc;
} RT_PACKED_STRUCT_ATTR;
RT_PACKED_STRUCT_END

class rt_runtime {
protected:
	rt_runtime() {}
	~rt_runtime(){}
public:
	virtual rt_context* createContext(rt_cstring threadName)=0;
	virtual rt_constarray<rt_context*> enumerateContexts(rt_malloc memAlloc)=0;
	virtual rt_type_system* getTypeSystem()=0;

};

/** Enumeration of status values for a runtime context. */
enum rt_context_status {
	RT_CONTEXT_STATUS_STOPPED = 0,    //!< RT_CONTEXT_STATUS_STOPPED The context is stopped
	RT_CONTEXT_STATUS_WAITING,        //!< RT_CONTEXT_STATUS_WAITING The context is in a waiting state
	RT_CONTEXT_STATUS_RUNNING_MANAGED,//!< RT_CONTEXT_STATUS_RUNNING_MANAGED The context is running managed code
	RT_CONTEXT_STATUS_RUNNING_NATIVE  //!< RT_CONTEXT_STATUS_RUNNING_NATIVE The context is running native code
};

/** Native callback for code executing in a finally block. */
typedef void (*rt_native_finally)();
/** Native callback for code executing in a catch block. */
typedef void (*rt_native_catch)(rt_value err);

class rt_context {
protected:
	rt_context(){}
	~rt_context(){}
public:
	virtual rt_runtime* getRuntime()=0;
	virtual rt_context_status getStatus()=0;
	virtual void loadRegister(uint8_t index, rt_value val)=0;
	virtual rt_value getRegister(uint8_t index)=0;
	virtual rt_bool pushValue(rt_value val)=0;
	virtual rt_value popValue(bool* underflow)=0;
	virtual void invoke(rt_method* method, bool isInstance, uint8_t instIndex)=0;
	virtual void doNativeTry(rt_type* catchType, rt_native_catch catcher, rt_native_finally finally)=0;
	virtual void throwException(rt_value err)=0;
};

}


#endif /* RTRUNTIME_HPP_ */
