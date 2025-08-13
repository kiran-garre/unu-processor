#ifndef INSTRUCTIONS
#define INSTRUCTIONS

#include <stdint.h>
#include <stdlib.h>

// Constants:
#define word_t 			uint64_t
// #define WORD_SIZE		sizeof(word_t)
// #define INSTR_SIZE		12
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
	word_t imm;
};

#define INSTR(OPCODE, DEST, SRC1, SRC2) (struct instr){OPCODE, DEST, SRC1, SRC2}

// Default instructions
// #define source 		0x5
// #define dest		0x6
// #define size		8

// struct instr default_set[] = {
// 	INSTR(MOVI, R0, UNU, source),
// 	INSTR(MOVI, R1, UNU, dest),
// 	INSTR(MOVI, R2, UNU, size),
// 	INSTR(MOVI, R3, UNU, 0),
// 	INSTR(MOVI, R6, UNU, WORD_SIZE),

// 	INSTR(MOVR, R4, UNU, PC),
// 	INSTR(LOAD, R5, R0, R3),
// 	INSTR(STORE, R5, R1, R3),
// 	INSTR(ADD, R3, R3, R6),
// 	INSTR(SUB, EQ, R2, R3),
// 	INSTR(BNE, EQ, R4, UNU),
// };

#endif // INSTRUCTIONS

