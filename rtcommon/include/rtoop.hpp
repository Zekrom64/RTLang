/*
 * rtoop.hpp
 *
 *  Created on: Mar 15, 2017
 *      Author: Zekrom_64
 */

#ifndef RTOOP_HPP_
#define RTOOP_HPP_

#include "rtcommon.hpp"
#include "rttype.hpp"
#include "rtutil.hpp"

namespace rt {
/*

enum rt_access {
	RT_ACCESS_PUBLIC = 0,
	RT_ACCESS_PROTECTED,
	RT_ACCESS_PRIVATE,
	RT_ACCESS_PACKAGE,
	RT_ACCESS_INTERNAL
};

enum rt_methodflags {
	
};

struct rt_methodsig {
	const rt_type* returnType;
	const rt_constarray<rt_type*> argumentTypes;
};

class rt_method {
protected:
	rt_method(){}
	~rt_method(){}
public:
	virtual rt_type* getContainingType()=0;
	virtual bool isBuiltIn()=0;
	virtual const rt_methodsig* getSignature()=0;
	virtual rt_cstring getName()=0;
	virtual bool isStatic()=0;
	virtual rt_uint getFlags()=0;
	virtual rt_access getAccess()=0;
};

class rt_field {
protected:
	rt_field(){}
	~rt_field(){}
public:
	virtual rt_type* getContainingType()=0;
	virtual bool isBuiltIn()=0;
	virtual rt_type* getType()=0;
	virtual uint32_t getOffset()=0;
	virtual rt_cstring getName()=0;
	virtual bool isStatic()=0;
	virtual rt_uint getFlags()=0;
	virtual rt_access getReadAccess()=0;
	virtual rt_access getWriteAccess()=0;
};
*/

}


#endif /* RTOOP_HPP_ */
