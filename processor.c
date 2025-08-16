#include "processor.h"

// Forward declarations
int dispatch(struct processor* proc, struct instr in);
struct instr fetch(struct processor* proc);

struct processor new_processor() {
	return (struct processor) {};
}

int execute_instr(struct processor* proc) {
	struct instr in = fetch(proc);
	int res = dispatch(proc, in);
	proc->regs[PC] += sizeof(struct instr);
	return res;
}

struct instr fetch(struct processor* proc) {
	struct instr res;
	memcpy(&res, proc->memory->data + proc->regs[PC], sizeof(struct instr));
	return res;
}

#define VERIFY_REG(VALUE) do { 								\
	if ((VALUE < 0 || VALUE > NUM_REGS) && (VALUE != EQ)) 	\
		return INVALID_REG_ERR; 							\
	} while (0)			

int load(struct processor* proc, struct instr in) {
	VERIFY_REG(in.dest);
	VERIFY_REG(in.src1);
	VERIFY_REG(in.imm);

	word_t base = proc->regs[in.src1];
	word_t offset = proc->regs[in.imm];
	proc->regs[in.dest] = *(word_t*) (base + offset);
	return 0;
}

int store(struct processor* proc, struct instr in) {
	VERIFY_REG(in.dest);
	VERIFY_REG(in.src1);
	VERIFY_REG(in.imm);

	word_t base = proc->regs[in.src1];
	word_t offset = proc->regs[in.imm];
	word_t* addr = (word_t*) (base + offset);

	*addr = proc->regs[in.dest];
	return 0;
}

int add(struct processor* proc, struct instr in) {
	VERIFY_REG(in.dest);
	VERIFY_REG(in.src1);
	VERIFY_REG(in.imm);

	proc->regs[in.dest] = proc->regs[in.src1] + proc->regs[in.imm];
	return 0;
}

int sub(struct processor* proc, struct instr in) {
	VERIFY_REG(in.dest);
	VERIFY_REG(in.src1);
	VERIFY_REG(in.imm);

	proc->regs[in.dest] = proc->regs[in.src1] - proc->regs[in.imm];
	return 0;
} 

int and(struct processor* proc, struct instr in) {
	VERIFY_REG(in.dest);
	VERIFY_REG(in.src1);
	VERIFY_REG(in.imm);

	proc->regs[in.dest] = proc->regs[in.src1] & proc->regs[in.imm];
	return 0;
}

int or(struct processor* proc, struct instr in) {
	VERIFY_REG(in.dest);
	VERIFY_REG(in.src1);
	VERIFY_REG(in.imm);

	proc->regs[in.dest] = proc->regs[in.src1] | proc->regs[in.imm];
	return 0;
}

int xor(struct processor* proc, struct instr in) {
	VERIFY_REG(in.dest);
	VERIFY_REG(in.src1);
	VERIFY_REG(in.imm);

	proc->regs[in.dest] = proc->regs[in.src1] ^ proc->regs[in.imm];
	return 0;
} 

int movi(struct processor* proc, struct instr in) {
	VERIFY_REG(in.dest);

	proc->regs[in.dest] = in.imm;
	return 0;
} 

int movr(struct processor* proc, struct instr in) {
	VERIFY_REG(in.dest);
	VERIFY_REG(in.imm);

	proc->regs[in.dest] = proc->regs[in.imm];
	return 0;
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
		default:
			return INVALID_OPCODE_ERR;
	}
}