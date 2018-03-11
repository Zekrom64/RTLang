/*
 * interop.cpp
 *
 *  Created on: Mar 19, 2017
 *      Author: Zekrom_64
 */

#include "interop.hpp"

#include "../util/cpputil.hpp"

#ifdef RT_OS_WINDOWS
#include <windows.h>
#include <winnt.h>
#elif defined(RT_OS_LINUX)
#include <dlfcn.h>
#elif defined(RT_OS_APPLE)

#endif

// [ rt_callingconv ]

// [ rt_nativelib ]

 void* NativeLib::getSymbol(rt::rt_cstring name) {
#ifdef RT_OS_WINDOWS
	return (void*)GetProcAddress((HMODULE)__handle, name);
#elif defined(RT_OS_LINUX) || defined(RT_OS_APPLE)
	return dlsym(__handle, name);
#endif
}

rt::rt_uint NativeLib::getNumSymbols() {
#ifdef RT_OS_WINDOWS
	/*
	PIMAGE_NT_HEADERS header = (PIMAGE_NT_HEADERS)((BYTE*)__handle + ((PIMAGE_DOS_HEADER)__handle)->e_lfanew);
	if (header->Signature != IMAGE_NT_SIGNATURE) return 0;
	if (header->OptionalHeader.NumberOfRvaAndSizes > 0) {
		PIMAGE_EXPORT_DIRECTORY exports = (PIMAGE_EXPORT_DIRECTORY)((BYTE*)__handle +
				header->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_EXPORT].VirtualAddress);
		DWORD addressOfNames = exports->AddressOfNames;
		if (addressOfNames == 0) return 0;
		return exports->NumberOfNames;
	}
	return 0;
	*/
	// TODO: Complete symbol enumeration for windows
#elif defined(RT_OS_LINUX) || defined(RT_OS_APPLE)
	/*
	link_map* linkMap;
	int success = dlinfo(__handle, RTLD_DI_LINKMAP, &linkMap);
	if (success != 0) return 0;
	*/
	// TODO: Complete symbol enumeration for linux/apple
#endif
	return 0;
}

rt::rt_bool NativeLib::getSymbolInfo(rt::rt_uint index, rt::rt_nativelib::symbol_info* info) {
#ifdef RT_OS_WINDOWS
	/*
	PIMAGE_NT_HEADERS header = (PIMAGE_NT_HEADERS)((BYTE*)__handle + ((PIMAGE_DOS_HEADER)__handle)->e_lfanew);
	if (header->Signature != IMAGE_NT_SIGNATURE) return false;
	if (header->OptionalHeader.NumberOfRvaAndSizes > 0) {
		PIMAGE_EXPORT_DIRECTORY exports = (PIMAGE_EXPORT_DIRECTORY)((BYTE*)__handle +
				header->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_EXPORT].VirtualAddress);
		DWORD addressOfNames = exports->AddressOfNames;
		if (addressOfNames == 0) return false;
		BYTE** names = ((BYTE**)__handle + addressOfNames);
		if (index >= exports->NumberOfNames) return false;
		info->name = (rt::rt_cstring)names[index];
		return true;
	} else return false;
	*/
	// TODO: Complete symbol enumeration for windows
#elif defined(RT_OS_LINUX) || defined(RT_OS_APPLE)
	// TODO: Complete symbol enumeration for linux/apple
#endif
	return false;
}

NativeLib::~NativeLib() {
#ifdef RT_OS_WINDOWS
	FreeLibrary((HMODULE)__handle);
#elif defined(RT_OS_LINUX) || defined(RT_OS_APPLE)
	dlclose(__handle);
#endif
	CPPutil::removeFrom(this->__the_interop->loadedLibs, this);
}

#ifdef RT_ARCH_AMD64

#elif defined(RT_ARCH_IA32)

#else
#error "Architecture not yet supported by ASMJIT! Aborting compile"
#endif

// [ rt_interop ]

rt::rt_callingconv Conventions[rt::rt_callingconv::ENUM_COUNT_STDCONV];

std::map<rt::rt_callingconv::stdconv,rt::rt_callingconv*> CallingConventionObjects {
	{ rt::rt_callingconv::STDCONV_CDECL_MS, &Conventions[rt::rt_callingconv::STDCONV_CDECL_MS] },
	{ rt::rt_callingconv::STDCONV_CDECL_GNU, &Conventions[rt::rt_callingconv::STDCONV_CDECL_GNU] },
	{ rt::rt_callingconv::STDCONV_STDCALL_MS, &Conventions[rt::rt_callingconv::STDCONV_STDCALL_MS] },
	{ rt::rt_callingconv::STDCONV_FASTCALL, &Conventions[rt::rt_callingconv::STDCONV_FASTCALL] },
	{ rt::rt_callingconv::STDCONV_PASCAL, &Conventions[rt::rt_callingconv::STDCONV_PASCAL] },
	{ rt::rt_callingconv::STDCONV_THISCALL_MS, &Conventions[rt::rt_callingconv::STDCONV_THISCALL_MS] },
	{ rt::rt_callingconv::STDCONV_THISCALL_GNU, &Conventions[rt::rt_callingconv::STDCONV_THISCALL_GNU] },
	{ rt::rt_callingconv::STDCONV_VECTORCALL_MS, &Conventions[rt::rt_callingconv::STDCONV_VECTORCALL_MS] },
};

#if defined(_WIN32)
#if defined(_WIN64) // 64-bit windows, cdecl
#define RT_DEFAULT_CALLINGCONV__ rt::rt_callingconv::STDCONV_CDECL_MS
#else
// 32-bit windows, stdconv
#define RT_DEFAULT_CALLINGCONV__ rt::rt_callingconv::STDCONV_STDCALL_MS
#endif
#else
// Everything else, cdecl
#define RT_DEFAULT_CALLINGCONV__ rt::rt_callingconv::STDCONV_CDECL_GNU
#endif

rt::rt_callingconv* DefaultCallingConventionObject = &Conventions[RT_DEFAULT_CALLINGCONV__];

rt::rt_callingconv* Interop::getStdConvention(rt::rt_callingconv::stdconv conv) {
	return &Conventions[conv];
}

rt::rt_callingconv* Interop::getDefaultConvention() {
	return DefaultCallingConventionObject;
}

rt::rt_nativelib* Interop::loadLibrary(rt::rt_cstring name) {
	void* handle = nullptr;
#ifdef RT_OS_WINDOWS
	handle = (void*)LoadLibraryA(name);
#elif defined(RT_OS_LINUX) || defined(RT_OS_MACOSX)
	handle = dlopen(name, RTLD_LAZY);
#endif
	if (handle == nullptr) return nullptr;
	NativeLib* lib = new NativeLib(handle, this);
	this->loadedLibs.push_back(lib);
	return lib;
}

rt::rt_nativelib* Interop::wrapLibrary(void* handle) {
	if (handle == nullptr) return nullptr;
	NativeLib* lib = new NativeLib(handle, this);
	this->loadedLibs.push_back(lib);
	return lib;
}

rt::rt_value Interop::createCCallback(void* funcptr, rt::rt_methodsig* signature, rt::rt_callingconv* conv) {
	rt::rt_value val = RT_VALUE_NULL;
#if defined(RT_ARCH_AMD64) || defined(RT_ARCH_IA32)
	asmjit::X86Assembler _asm;
#endif
	return val;
}

