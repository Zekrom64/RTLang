/*
 * rtinterop.hpp
 *
 *  Created on: Mar 18, 2017
 *      Author: Zekrom_64
 */

#ifndef RTINTEROP_HPP_
#define RTINTEROP_HPP_

#include "rtcommon.hpp"
#include "rtoop.hpp"
#include <functional>

namespace rt {

/** A calling convention describes how arguments and return values are passed in
 * native code, and other semantics about how calls and returns work.
 */
class rt_callingconv {
protected:
	rt_callingconv() {}
	~rt_callingconv() {}
public:
	/** Enumeration of standard calling convention formats. */
	enum stdconv {
		STDCONV_CDECL_MS = 0,	//!< STDCONV_CDECL_MS Microsoft variant of cdecl
		STDCONV_CDECL_GNU,   	//!< STDCONV_CDECL_GNU GNU/GCC variant of cdecl
		STDCONV_STDCALL_MS,  	//!< STDCONV_STDCALL Microsoft stdcall
		STDCONV_FASTCALL,    	//!< STDCONV_FASTCALL Microsoft and GNU/GCC fastcall (identical)
		STDCONV_PASCAL,      	//!< STDCONV_PASCAL Special Borland Pascal calling convention
		STDCONV_THISCALL_MS, 	//!< STDCONV_THISCALL_MS Microsoft version of C++ thiscall
		STDCONV_THISCALL_GNU,	//!< STDCONV_THISCALL_GNU GNU/GCC version of C++ thiscall
		STDCONV_VECTORCALL_MS,	//!< STDCONV_VECTORCALL_MS Microsoft vectorcall calling convention, special on x64
		ENUM_COUNT_STDCONV		//!< ENUM_COUNT_STDCONV Number of values in stdconv enumeration
	};
};

/** A native library contains platform-specific code with an index of "symbols"
 * that can be accessed by other applications.
 */
class rt_nativelib {
protected:
	rt_nativelib(){}
	~rt_nativelib(){}
public:
	/** Struct containing information about a single symbol. */
	struct symbol_info {
		rt_cstring name;
	};
	/** Gets the number of symbols in the native library.
	 *
	 * @return Number of symbols
	 */
	virtual rt_uint getNumSymbols()=0;
	/** Gets information about a symbol at the given index in the library.
	 *
	 * @param index Index of symbol info to get
	 * @param info Pointer to symbol_info structure
	 * @return true if successful, false otherwise
	 */
	virtual rt_bool getSymbolInfo(rt_uint index, symbol_info* info)=0;
	/** Gets a symbol from the library by its names, returns nullptr if none is found.
	 *
	 * @param name Name of the symbol
	 * @return Symbol pointer
	 */
	virtual void* getSymbol(rt_cstring name)=0;
};

/** Native inter-operability provider class.
 *
 */
class rt_interop {
protected:
	rt_interop(){}
	~rt_interop(){}
public:
	/** Gets a standard calling convention.
	 *
	 * @param c Standard calling convention type
	 * @return Calling convention object
	 */
	virtual rt_callingconv* getStdConvention(rt_callingconv::stdconv c)=0;
	/** Gets the platform's default calling convention. This is usually STDCONV_CDECL_GNU, but
	 * may be different depending on the platform.
	 *
	 * @return Platform's default calling convention
	 */
	virtual rt_callingconv* getDefaultConvention()=0;
	virtual void* getRTCallback(rt_method* method, rt_value objref, rt_callingconv* conv)=0;
	virtual rt_value createCCallback(void* funcptr, rt_methodsig* signature, rt_callingconv* conv)=0;
	/** Binds a native function to a native method. When called, the native method will marshal
	 * types to their native equivalents, then call the native function. When the native function
	 * returns, any return values will be marshalled to their managed equivalents, and the calling
	 * method will resume.
	 *
	 * @param method Method to bind to
	 * @param funcptr Pointer to native function
	 * @param conv Calling convention to use for native function
	 * @return If the bind was successful
	 */
	virtual bool bindNativeFunction(rt_method* method, void* funcptr, rt_callingconv* conv)=0;
	/** Binds a native function to an extern method. When called, the extern method will
	 * pass control of the virtual machine to the native function. When the native function
	 * returns, the virtual machine will resume its calling method.
	 *
	 * @param method Method to bind to
	 * @param funcptr Pointer to native function
	 * @param conv Calling convention to use for native function
	 * @return If the bind was successful
	 */
	virtual bool bindExternFunction(rt_method* method, void* funcptr, rt_callingconv* conv)=0;
	/** Loads a native library. The name may be a relative or absolute path.
	 *
	 * @param name Native library name/path
	 * @return The native library, or nullptr if an error occurred
	 */
	virtual rt_nativelib* loadLibrary(rt_cstring name)=0;
	/** Wraps a platform-specific library handle into a native library object.
	 *
	 * @param handle Platform-specific handle
	 * @return Native library object
	 */
	virtual rt_nativelib* wrapLibrary(void* handle)=0;
};

}


#endif /* RTINTEROP_HPP_ */
