#include "instructions.h"
#include <stdio.h>

char* instr_to_str(struct instr* in) {
	char buf[32];
	switch (in->opcode) {
		case LOAD:
		case STORE:
		case ADD:
		case SUB:
		case AND:
		case OR:
		case XOR:
			sprintf(buf, "%s %s %s %s", 
				opcode_to_str(in->opcode), 
				reg_to_str(in->dest),
				reg_to_str(in->src1),
				reg_to_str(in->imm)
			);
		
		case MOVR:
		case BEQ:
		case BNE:
			sprintf(buf, "%s %s %s",
				opcode_to_str(in->opcode),
				reg_to_str(in->dest),
				reg_to_str(in->imm)
			);

		case MOVI:
			sprintf(buf, "%s %s %s",
				opcode_to_str(in->opcode),
				reg_to_str(in->dest),
				in->imm
			);

		case BRN:
			sprintf(buf, "%s %s",
				opcode_to_str(in->opcode),
				reg_to_str(in->imm)
			);
	}
	return buf;
}