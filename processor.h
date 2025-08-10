#ifndef PROCESSOR
#define PROCESSOR

#include "instructions.h"

struct processor {
	uint64_t regs[NUM_GP_REGS];
	uint64_t eq;
	struct instr* pc;
};

#endif