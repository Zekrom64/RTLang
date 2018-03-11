/*
 * interop_x86_64.hpp
 *
 *  Created on: Mar 19, 2017
 *      Author: Zekrom_64
 */

#ifndef INTEROP_INTEROP_X86_64_HPP_
#define INTEROP_INTEROP_X86_64_HPP_

#include <rtcommon.hpp>
#include "asmjit/asmjit.h"

#include "interop.hpp"

#ifdef RT_ARCH_AMD64

asmjit_reg regs_callerSaved_ms[] = {
		asmjit_reg(asmjit::x86::rax),
		asmjit_reg(asmjit::x86::rcx),
		asmjit_reg(asmjit::x86::rdx),
		asmjit_reg(asmjit::x86::r8),
		asmjit_reg(asmjit::x86::r9),
		asmjit_reg(asmjit::x86::r10),
		asmjit_reg(asmjit::x86::r11),
		asmjit_reg(asmjit::x86::xmm0),
		asmjit_reg(asmjit::x86::xmm1),
		asmjit_reg(asmjit::x86::xmm2),
		asmjit_reg(asmjit::x86::xmm3),
		asmjit_reg(asmjit::x86::xmm4),
		asmjit_reg(asmjit::x86::xmm5),
		asmjit_reg(asmjit::x86::ymm0),
		asmjit_reg(asmjit::x86::ymm1),
		asmjit_reg(asmjit::x86::ymm2),
		asmjit_reg(asmjit::x86::ymm3),
		asmjit_reg(asmjit::x86::ymm4),
		asmjit_reg(asmjit::x86::ymm5),
		asmjit_reg(asmjit::x86::ymm6),
		asmjit_reg(asmjit::x86::ymm7),
		asmjit_reg(asmjit::x86::ymm8),
		asmjit_reg(asmjit::x86::ymm9),
		asmjit_reg(asmjit::x86::ymm10),
		asmjit_reg(asmjit::x86::ymm11),
		asmjit_reg(asmjit::x86::ymm12),
		asmjit_reg(asmjit::x86::ymm13),
		asmjit_reg(asmjit::x86::ymm14),
		asmjit_reg(asmjit::x86::ymm15)
};

asmjit_reg regs_calleeSaved_ms[] = {
		asmjit_reg(asmjit::x86::rbx),
		asmjit_reg(asmjit::x86::rbp),
		asmjit_reg(asmjit::x86::rdi),
		asmjit_reg(asmjit::x86::rsi),
		asmjit_reg(asmjit::x86::rsp),
		asmjit_reg(asmjit::x86::r12),
		asmjit_reg(asmjit::x86::r13),
		asmjit_reg(asmjit::x86::r14),
		asmjit_reg(asmjit::x86::r15),
		asmjit_reg(asmjit::x86::xmm6),
		asmjit_reg(asmjit::x86::xmm7),
		asmjit_reg(asmjit::x86::xmm8),
		asmjit_reg(asmjit::x86::xmm9),
		asmjit_reg(asmjit::x86::xmm10),
		asmjit_reg(asmjit::x86::xmm11),
		asmjit_reg(asmjit::x86::xmm12),
		asmjit_reg(asmjit::x86::xmm13),
		asmjit_reg(asmjit::x86::xmm14),
		asmjit_reg(asmjit::x86::xmm15),
};

class CallingConvAMD64MS : public CallingConvX86 {
public:
	CallingConvAMD64MS() : CallingConvX86(
			rt::rt_constarray<asmjit_reg>(regs_callerSaved_ms, 29),
			rt::rt_constarray<asmjit_reg>(regs_calleeSaved_ms, 19)
	) {}

	virtual void beginFrame(asmjit::X86Assembler* _asm) {
		_asm->push(asmjit::x86::rbp);
		_asm->mov(asmjit::x86::rsp, asmjit::x86::rbp);
	}

	/*
	virtual asmjit_reg_or_memory getOperand(rt::rt_methodsig* sig, rt::rt_uint index) {
		if (index > 3) {

		} else {
			if (sig->argumentTypes.elements[index]->isDecimal()) {
				asmjit::X86Xmm xmmreg;
				switch(index) {
				case 0: xmmreg = asmjit::x86::xmm0; break;
				case 1: xmmreg = asmjit::x86::xmm1; break;
				case 2: xmmreg = asmjit::x86::xmm2; break;
				case 3: xmmreg = asmjit::x86::xmm3; break;
				}
				return asmjit_reg_or_memory(xmmreg);
			} else {
				asmjit::X86Gp reg;
				switch(index) {
				case 0: reg = asmjit::x86::rax; break;
				case 1: reg = asmjit::x86::rcx; break;
				case 2: reg = asmjit::x86::rdx; break;
				case 3: reg = asmjit::x86::r8; break;
				}
				return asmjit_reg_or_memory(reg);
			}
		}
	}
	*/

	virtual void endFrame(asmjit::X86Assembler* _asm) {
		_asm->pop(asmjit::x86::rbp);
	}
};

asmjit_reg regs_callerSaved_gnu[] = {
		asmjit_reg(asmjit::x86::rax)
};

#endif


#endif /* INTEROP_INTEROP_X86_64_HPP_ */
