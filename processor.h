#ifndef PROCESSOR
#define PROCESSOR

#include "instructions.h"
#include "ememory.h"

// Errors
#define INVALID_OPCODE_ERR		-1000
#define INVALID_REG_ERR			-1001

struct processor {
	uint64_t regs[NUM_REGS];
	struct ememory* memory;
};

/**
 * Returns a new processor with uninitialized ememory
 */
struct processor new_processor();

#endif // PROCESSOR