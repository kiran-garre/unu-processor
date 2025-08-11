#include <stdint.h>
#include <string.h>
#include "processor.h"


// Constants
#define MEM_SIZE 			65536
#define STARTING_OFFSET		0x10

// Errors
#define DOUBLE_FREE

struct ememory {
	char data[MEM_SIZE];
	uint16_t free_head;
};

#define ENULL (struct eptr) {}

struct eptr {
	uint16_t ptr;
	uint16_t size;
};

/**
 * Header format:
 * 
 * +++++++++++++++ +++++++++++++++ +++++++++++++++
 * | size (word) | | next (word) | | prev (word) |
 * +++++++++++++++ +++++++++++++++ +++++++++++++++
 * 
 * where: 
 * 	- `size` contains the size of the free space (including the header)
 * 	- `next` contains the index of the start of the next free section 
 * 	- `prev` contains the index of the start of the previous free section
 */

void write_header(char* data, uint16_t size, uint16_t next, uint16_t prev, uint16_t offset) {
	memcpy(data + offset, size, sizeof(uint16_t));
	memcpy(data + offset + sizeof(uint16_t), next, sizeof(uint16_t));
	memcpy(data + offset + sizeof(uint16_t) + sizeof(uint16_t), prev, sizeof(uint16_t));
}

void read_header(char* data, uint16_t* size, uint16_t* next, uint16_t* prev, uint16_t offset) {
	memcpy(size, data + offset, sizeof(uint16_t));
	memcpy(next, data + offset + sizeof(uint16_t), sizeof(uint16_t));
	memcpy(prev, data + offset + sizeof(uint16_t) + sizeof(uint16_t), sizeof(uint16_t));
}

void init_emalloc(struct ememory* memory) {
	write_header(memory->data, MEM_SIZE - STARTING_OFFSET, 0, 0, STARTING_OFFSET);
	memory->free_head = STARTING_OFFSET;
}

struct eptr emalloc(struct ememory* memory, uint16_t size) {
	struct eptr res;
	char* data = memory->data;
	uint16_t block_size, next, prev;
	uint16_t curr = memory->free_head;
	
	while (curr != 0) {
		read_header(data, &block_size, &next, &prev, curr);
		if (block_size >= size) {
			res.ptr = curr;
			res.size = size;

			// Shrink free block if space is left over
			// Otherwise, update pointer of previous block to point to next
			if (block_size > size) {
				curr += size;
				write_header(data, block_size - size, next, prev, curr);
			} else if (prev != 0) {
				memcpy(data + prev + sizeof(uint16_t), next, sizeof(uint16_t));
			}
			return res;
		} 
		curr = next;
	}
	return ENULL;
}

/**
 * If ptr < free_head:
 * 		free_head = ptr
 * 		if ptr + size == free_head
 *			- write header at ptr with next = free_head.next, size = size + free_head.size
 *		else
 *			- write header at ptr with next = free_head, size = size
 *
 * As we're iterating through the list:
 * - curr == ptr && ptr + size == next
 * 		-> Merge everything into one big chunk
 * 		-> curr.next = next.next
 * 		-> curr.size += ptr.size + next.size
 * - curr < ptr && ptr + size == next
 * 		-> Merge this and next
 * 		-> curr.next = ptr
 * 		-> write header at ptr containing next = next.next, size = size + next.size
 * - curr == ptr && ptr + size < next
 * 		-> Merge prev and this
 * 		-> curr.size += size
 * - prev < ptr && ptr + size < next
 * 		-> Insert without merging
 * 		-> curr.next = ptr
 * 		-> write header at ptr containing next = next, size = size
 * 
 * If we've iterated through the list and haven't returned, we know that it must be a new node
 * at the end.
 * if ptr = last + last.size: 
 * 		last.size += ptr.size
 * else
 * 		last.next = ptr
 * 		write header at ptr with next = 0, size = size
 */
int efree(struct ememory* memory, struct eptr ptr) {
	char* data = memory->data;
	uint16_t block_size, next, prev;
	uint16_t curr = memory->free_head;

	while (curr != 0) {
		read_header(memory->data, &block_size, &next, &prev, curr);
		if (prev < ptr.ptr && ptr.ptr + ptr.size < next) {

		}
	}
} 

