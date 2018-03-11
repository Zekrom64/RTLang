/*
 * valstack.hpp
 *
 *  Created on: Jan 20, 2018
 *      Author: Zekrom_64
 */

#ifndef RUNTIME_VALSTACK_HPP_
#define RUNTIME_VALSTACK_HPP_

#include "rtruntime.hpp"
#include "../util/memmgt.hpp"

/** Class implementing a dynamic rt_value stack. */
class ValueStack {
public:
	struct StackFrame {
		rt::rt_value* base;
		rt::rt_value* sp;
		rt::rt_value* head;
		uint64_t frameUse;
	};

	StackFrame* stackFrames;
	uint32_t nStackFrames;
	StackFrame* currentFrame;

	rt::rt_value* stackValues;
	rt::rt_value* currentValue;
	uint64_t nStackValues;


	MemoryManager* const memMgr;
	ValueStack(MemoryManager* mgr) : memMgr(mgr) {
		nStackFrames = 10;
		stackFrames = (StackFrame*)memMgr->Allocate(sizeof(StackFrame) * nStackFrames);
		currentFrame = stackFrames;
		nStackValues = 50;
		stackValues = (rt::rt_value*)memMgr->Allocate(sizeof(rt::rt_value) * nStackValues);
		currentValue = stackValues;
	}

	bool push(rt::rt_value val) {
		if (currentFrame->sp > currentFrame->head) return true;
		*(currentFrame->sp++) = val;
		return false;
	}

	/** Pushes a frame onto the stack, allocating the given number of local values.
	 *
	 * @param nLocalValues
	 */
	void pushFrame(uint32_t nLocalValues) {
		currentFrame++;
		if (currentFrame > stackFrames) {
			size_t offset = currentFrame - stackFrames;
			stackFrames = (StackFrame*)memMgr->Reallocate(stackFrames, nStackFrames += 10);
			currentFrame = stackFrames + offset;
		}
		currentFrame->frameUse++;
	}

	/** Pops a value from the current stack frame.
	 *
	 * @param underflow If stack underflow, set to true, unmodified otherwise
	 * @return The value poped from the current frame, RT_VALUE_NULL if underflow
	 */
	rt::rt_value pop(bool* underflow) {
		if (currentFrame->sp <= currentFrame->base) {
			*underflow = true;
			return RT_VALUE_NULL;
		}
		return *(--currentFrame->sp);
	}

	/** Pops a frame from the value stack. Returns true if the stack
	 * underflowed, false otherwise.
	 */
	bool popFrame() {
		if (currentFrame > stackFrames) {
			currentFrame--;
			return false;
		} else return true;
	}

	void doGarbageCollection() {
		// Find index where stack frames are called less often
		StackFrame* framePtr = stackFrames;
		size_t maxFrameCount = 0;
		size_t stackFrameThreshold = 0;
		for(size_t i = nStackFrames - 1; i >= 0; i++) {
			StackFrame* ptr = framePtr + i;
			size_t frameUse = ptr->frameUse;
			stackFrameThreshold = i;
			if (frameUse > maxFrameCount) maxFrameCount = frameUse;
			else break;
		}
		// Ensure we don't accidentally deallocate the current stack frame!
		size_t currentFrameIndex = currentFrame - stackFrames;
		if (currentFrameIndex > stackFrameThreshold) stackFrameThreshold = currentFrameIndex;
		// If we can free up some frames
		if (stackFrameThreshold != nStackFrames - 1) {
			// Reallocate frame stack
			nStackFrames = stackFrameThreshold + 1;
			stackFrames = (StackFrame*)memMgr->Reallocate(stackFrames, nStackFrames);
			currentFrame = stackFrames + stackFrameThreshold;
		}
		// Clear use counts for frames
		for(size_t i = 0; i < nStackFrames; i++) stackFrames[i].frameUse = 0;
	}

};


#endif /* RUNTIME_VALSTACK_HPP_ */
