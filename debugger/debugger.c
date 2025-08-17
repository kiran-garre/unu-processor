#include "debugger.h"

#define CONTEXT_RELATIVE_START 		-1
#define CONTEXT_LEN					4	

static word_t adjusted_pc(word_t offset) {
	return offset - sizeof(struct instr);
}

char (*gather_context(struct processor* proc))[32] {
	word_t initial_offset = adjusted_pc(proc->regs[PC]);
	char (*bufs)[32] = malloc(sizeof(char[CONTEXT_LEN][32]));

	for (int i = 0; i < CONTEXT_LEN; i++) {
		int offset = initial_offset + (i + CONTEXT_RELATIVE_START) * sizeof(struct instr);
		struct instr in = get_instr(proc->memory->data, offset);
		instr_to_str(&in, bufs[i]);
	}
	return bufs;
}

void display_context(struct processor* proc) {
	char (*bufs)[32] = gather_context(proc);
	for (int i = 0; i < CONTEXT_LEN; i++) {
		printf("%s\n", bufs[i]);
	}
}

void pretty_context(struct processor* proc) {
	char (*bufs)[32] = gather_context(proc);
	word_t initial_offset = adjusted_pc(proc->regs[PC]);

	printf("CONTEXT: ----------------------------\n");
	for (int i = 0; i < CONTEXT_LEN; i++) {
		int offset = initial_offset + (i + CONTEXT_RELATIVE_START) * sizeof(struct instr);
		if (offset == initial_offset) {
			printf("->  ");
		} else {
			printf("    ");
		}
		printf("0x%08x:\t%s\n", offset, bufs[i]);
	}
	printf("-------------------------------------\n");
}