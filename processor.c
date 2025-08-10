#include "processor.h"

struct processor new_processor() {
	return (struct processor) {};
}

int execute_instr(struct processor* proc) {
	struct instr in = fetch(proc);
	int res = dispatch(proc, in);
	proc->pc += sizeof(struct instr);
}

struct instr fetch(struct processor* proc) {
	return *(proc->pc);
}

int dispatch(struct processor* proc, struct instr in) {
	switch (in.opcode) {
		case LOAD:
			return load(proc, in);
		case STORE:
			return store(proc, in);
		case ADD:
			return add(proc, in);
		case SUB:
			return sub(proc, in);
		case AND:
			return and(proc, in);
		case OR:
			return or(proc, in);
		case XOR:
			return xor(proc, in);
		case MOVI:
			return movi(proc, in);
		case MOVR:
			return movr(proc, in);
	}
}

int load(struct processor* proc, struct instr in) {
	word_t base = proc->regs[in.src1];
	word_t offset = proc->regs[in.imm];
	proc->regs[in.dest] = *(word_t*) (base + offset);
}

int store(struct processor* proc, struct instr in) {
	word_t base = proc->regs[in.src1];
	word_t offset = proc->regs[in.imm];
	word_t* addr = (word_t*) (base + offset);

	*addr = proc->regs[in.dest];
}

int add(struct processor* proc, struct instr in) {
	proc->regs[in.dest] = proc->regs[in.src1] + proc->regs[in.imm];
}

int sub(struct processor* proc, struct instr in) {
	proc->regs[in.dest] = proc->regs[in.src1] - proc->regs[in.imm];
} 

int and(struct processor* proc, struct instr in) {
	proc->regs[in.dest] = proc->regs[in.src1] & proc->regs[in.imm];
}

int or(struct processor* proc, struct instr in) {
	proc->regs[in.dest] = proc->regs[in.src1] | proc->regs[in.imm];
}

int xor(struct processor* proc, struct instr in) {
	proc->regs[in.dest] = proc->regs[in.src1] ^ proc->regs[in.imm];
} 

int movi(struct processor* proc, struct instr in) {
	proc->regs[in.dest] = in.imm;
} 

int movr(struct processor* proc, struct instr in) {
	proc->regs[in.dest] = proc->regs[in.imm];
} 