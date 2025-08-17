#ifndef DEBUGGER
#define DEBUGGER

#include "../instructions.h"
#include "../processor.h"
#include "disassembler.h"

/**
 * Prints the instructions surrounding and including the instrction at PC
 */
void display_context(struct processor* proc);

/**
 * context(), but prettier
 */
void pretty_context(struct processor* proc);

#endif // DEBUGGER