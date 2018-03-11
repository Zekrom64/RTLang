/*
 * rttype.hpp
 *
 *  Created on: Mar 14, 2017
 *      Author: Zekrom_64
 */

#ifndef RTTYPE_HPP_
#define RTTYPE_HPP_

#include "rtutil.hpp"

namespace rt {

class rt_type_system;
class rt_type;
struct rt_method;
struct rt_field;

enum rt_primitive_type {
	RT_PRIMITIVE_BOOL = 0,
	RT_PRIMITIVE_BYTE,
	RT_PRIMITIVE_UBYTE,
	RT_PRIMITIVE_SHORT,
	RT_PRIMITIVE_USHORT,
	RT_PRIMITIVE_INT,
	RT_PRIMITIVE_UINT,
	RT_PRIMITIVE_LONG,
	RT_PRIMITIVE_ULONG,
	RT_PRIMITIVE_FLOAT,
	RT_PRIMITIVE_DOUBLE
};

enum rt_base_type {
	RT_BASETYPE_PRIMITIVE = 0,
	RT_BASETYPE_ARRAY,
	RT_BASETYPE_POINTER,
	RT_BASETYPE_OBJECT,
	RT_BASETYPE_FUNCTION,
	RT_BASETYPE_INTERNAL
};

enum rt_generic_modifier_type {
	RT_GENERICMOD_IMPLEMENTED_CTOR = 0,
	RT_GENERICMOD_IMPLEMENTED_DTOR,
	RT_GENERICMOD_SUPERCLASS,
	RT_GENERICMOD_SUPERIMPLEMENTOR,
	RT_GENERICMOD_THISCLASS
};

RT_PACKED_STRUCT_BEGIN
struct rt_generic_modifier {
	rt_generic_modifier_type modType;
	void* param;
} RT_PACKED_STRUCT_ATTR;
RT_PACKED_STRUCT_END

class rt_type_system {
protected:
	rt_type_system(){}
	~rt_type_system(){}
public:
	virtual rt_type* getType(rt_cstring name)=0;
	virtual rt_type* getPrimitiveType(rt_primitive_type t)=0;
	virtual rt_type* getNullVoidType()=0;
	virtual rt_type* getAnyType()=0;
	virtual rt_type* defineType(rt_byte* bytecode, size_t offset, size_t length)=0;
	virtual rt_type* getGenericType(rt_type* superClass, rt_constarray<rt_type*>* interfaces, rt_constarray<rt_generic_modifier>* modifiers)=0;
};

class rt_type {
protected:
	rt_type() {}
	~rt_type(){}
public:
	virtual rt_type_system* getTypeSystem()=0;
	virtual const char* getName()=0;
	virtual rt_type* getParent()=0;
	virtual size_t getSizeOf()=0;
	virtual bool isFullyDefined()=0;
	virtual bool isPrimitive(rt_primitive_type t)=0;
	virtual bool isInteger()=0;
	virtual bool isDecimal()=0;
	virtual rt_base_type getBaseType()=0;
	virtual rt_constarray<rt_method*>* getMethods()=0;
	virtual rt_constarray<rt_field*>* getFields()=0;
	virtual rt_constarray<rt_method*>* getConstructors()=0;
	virtual rt_constarray<rt_method*>* getDestuctors()=0;
	virtual rt_type* getElementType()=0;
	virtual rt_constarray<rt_type*>* getDefinedGenerics()=0;
	virtual rt_constarray<rt_type*>* getInstanceGenerics(rt_value val)=0;
};

RT_PACKED_STRUCT_BEGIN
struct rt_method {
		const rt_type* returnType;
		const rt_constarray<rt_type*> argumentTypes;
		const rt_constarray<rt_type*> genericTypes;
} RT_PACKED_STRUCT_ATTR;
RT_PACKED_STRUCT_END

RT_PACKED_STRUCT_BEGIN
struct rt_field {
	const rt_type* fieldType;
} RT_PACKED_STRUCT_ATTR;
RT_PACKED_STRUCT_END

}


#endif /* RTTYPE_HPP_ */
