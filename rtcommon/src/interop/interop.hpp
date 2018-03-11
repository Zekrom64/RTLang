/*
 * interop.hpp
 *
 *  Created on: Mar 19, 2017
 *      Author: Zekrom_64
 */

#ifndef INTEROP_INTEROP_HPP_
#define INTEROP_INTEROP_HPP_

#include <rtinterop.hpp>
#include <rtruntime.hpp>
#include "asmjit/asmjit.h"
#include <vector>
#include <map>

#if defined(RT_ARCH_AMD64) || defined(RT_ARCH_IA32)
#include "../util/asmjit_x86_util.hpp"
#endif


class CallingConv : public rt::rt_callingconv {
public:
	CallingConv(){}
	virtual ~CallingConv(){}
};

#if defined(RT_ARCH_AMD64) || defined(RT_ARCH_IA32)
class CallingConvX86 : public CallingConv {
public:
	rt::rt_constarray<asmjit_reg> callerSaved;
	rt::rt_constarray<asmjit_reg> calleeSaved;
	CallingConvX86(rt::rt_constarray<asmjit_reg> __caller, rt::rt_constarray<asmjit_reg> __callee) :
			callerSaved(__caller), calleeSaved(__callee) {}
	virtual void beginFrame(asmjit::X86Assembler* _asm)=0;
	virtual void endFrame(asmjit::X86Assembler* _asm)=0;
};
#endif


#if defined(RT_ARCH_AMD64) || defined(RT_ARCH_IA32)
#include "interop_x86_64.hpp"
#endif

class Interop;

class NativeLib : public rt::rt_nativelib {
public:
	void* __handle;
	Interop* __the_interop;
	NativeLib(void* handle, Interop* interop) : __handle(handle), __the_interop(interop) {}
	virtual ~NativeLib();
	virtual rt::rt_uint getNumSymbols();
	virtual rt::rt_bool getSymbolInfo(rt::rt_uint index, symbol_info* info);
	virtual void* getSymbol(rt::rt_cstring name);
};

class Interop : public rt::rt_interop {
public:
	std::vector<NativeLib*> loadedLibs;
	Interop() {}
	virtual ~Interop(){}
	virtual rt::rt_callingconv* getStdConvention(rt::rt_callingconv::stdconv c);
	virtual rt::rt_callingconv* getDefaultConvention();
	virtual void* getRTCallback(rt::rt_method* method, rt::rt_value objref, rt::rt_callingconv* conv);
	virtual rt::rt_value createCCallback(void* funcptr, rt::rt_methodsig* signature, rt::rt_callingconv* conv);
	virtual void bindNativeFunction(rt::rt_method* method, void* funcptr, rt::rt_callingconv* conv);
	virtual rt::rt_nativelib* loadLibrary(rt::rt_cstring name);
	virtual rt::rt_nativelib* wrapLibrary(void* handle);
};

std::map<rt::rt_callingconv::stdconv,rt::rt_callingconv*> CallingConventionObjects;
rt::rt_callingconv* DefaultCallingConventionObject;

#endif /* INTEROP_INTEROP_HPP_ */
