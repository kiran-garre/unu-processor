#include <stdint.h>
#include <string.h>
#include "processor.h"

#define MEM_SIZE 			65536
#define STARTING_OFFSET		0x10

struct ememory {
	char data[MEM_SIZE];
	uint16_t free_head;
	// struct eptr* free_tail;
	int num_free_ptrs;
};

struct eptr {
	uint16_t ptr;
	uint16_t size;
};

void write_header(char* data, uint16_t size, uint16_t next, uint16_t last, uint16_t offset) {
	memcpy(data + offset, size, sizeof(uint16_t));
	memcpy(data + offset + sizeof(uint16_t), next, sizeof(uint16_t));
	memcpy(data + offset + sizeof(uint16_t) + sizeof(uint16_t), last, sizeof(uint16_t));
}

void read_header(char* data, uint16_t* size, uint16_t* next, uint16_t* last, uint16_t offset) {
	memcpy(size, data + offset, sizeof(uint16_t));
	memcpy(next, data + offset + sizeof(uint16_t), sizeof(uint16_t));
	memcpy(last, data + offset + sizeof(uint16_t) + sizeof(uint16_t), sizeof(uint16_t));
}

void init_emalloc(struct ememory* memory) {
	write_header(memory->data, MEM_SIZE - STARTING_OFFSET, 0, 0, STARTING_OFFSET);
	memory->free_head = STARTING_OFFSET;
}

struct eptr emalloc(struct ememory* memory, uint16_t size) {
	struct eptr res;
	uint16_t block_size, next, last;
	uint16_t curr = memory->free_head;
	
	while (curr != 0) {
		read_header(memory->data, &block_size, &next, &last, curr);
		if (block_size >= size) {
			res.ptr = curr;
			res.size = size;

			// Shrink free block if space is leftover
			// Otherwise, update pointer of last block to point to next
			if (block_size > size) {
				curr += size;
				write_header(memory->data, block_size - size, next, last, curr);
			} else if (last != 0) {
				memcpy(memory->data + last + sizeof(uint16_t), next, sizeof(uint16_t));
			}
			return res;
		} 
		curr = next;
	}
}


int efree(struct ememory* memory, struct eptr ptr) {
	
} 

