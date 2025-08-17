#ifndef INSTRUCTIONS
#define INSTRUCTIONS

#include <stdint.h>
#include <stdlib.h>

// Constants:
#define word_t 			uint32_t
#define NUM_REGS		10

// Opcodes:
#define LOAD	0
#define STORE	1
#define ADD		2
#define SUB		3
#define AND		4
#define OR		5
#define XOR		6
#define MOVR	7
#define MOVI	8
#define BEQ		9
#define BNE		10

// Registers:
#define R0		0
#define R1		1
#define R2		2
#define R3		3
#define R4		4
#define R5		5
#define R6		6
#define R7		7

#define PC		8
#define EQ		9

struct instr {
	char opcode;
	char dest : 4;
	char src1 : 4;
	uint16_t imm;
};

#define INSTR(OPCODE, DEST, SRC1, SRC2) (struct instr){OPCODE, DEST, SRC1, SRC2}

#endif // INSTRUCTIONS

