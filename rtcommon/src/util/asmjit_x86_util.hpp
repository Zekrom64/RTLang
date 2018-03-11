/*
 * asmjit_x86_util.hpp
 *
 *  Created on: Mar 19, 2017
 *      Author: Zekrom_64
 */

#ifndef UTIL_ASMJIT_X86_UTIL_HPP_
#define UTIL_ASMJIT_X86_UTIL_HPP_

#include <rtcommon.hpp>
#include "asmjit/asmjit.h"

#if defined(RT_ARCH_AMD64) || defined(RT_ARCH_IA32)

struct asmjit_reg_or_memory {
	enum reg_or_mem_type {
		T_GPREG,
		T_XMMREG,
		T_YMMREG,
		T_ZMMREG,
		T_MEM,
		T_FPREG
	};
	reg_or_mem_type type;
	asmjit::X86Gp reg;
	asmjit::X86Xmm xmmreg;
	asmjit::X86Ymm ymmreg;
	asmjit::X86Zmm zmmreg;
	asmjit::X86Mem mem;
	asmjit::X86Fp fpreg;
};

struct asmjit_reg {
	enum reg_type {
		T_GPREG,
		T_XMMREG,
		T_YMMREG,
		T_ZMMREG,
		T_FPREG
	};
	reg_type type;
	asmjit::X86Gp reg;
	asmjit::X86Xmm xmmreg;
	asmjit::X86Ymm ymmreg;
	asmjit::X86Zmm zmmreg;
	asmjit::X86Fp fpreg;
	asmjit_reg(asmjit::X86Gp r) : type(T_GPREG), reg(r) {}
	asmjit_reg(asmjit::X86Xmm x) : type(T_XMMREG), xmmreg(x) {}
	asmjit_reg(asmjit::X86Ymm y) : type(T_YMMREG), ymmreg(y) {}
	asmjit_reg(asmjit::X86Zmm z) : type(T_ZMMREG), zmmreg(z) {}
	asmjit_reg(asmjit::X86Fp fp) : type(T_FPREG), fpreg(fp) {}
};

#endif


#endif /* UTIL_ASMJIT_X86_UTIL_HPP_ */
