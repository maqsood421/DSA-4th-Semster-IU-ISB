#include <stdio.h>
#include <unistd.h>   // For sbrk()
#include <stdint.h>   // For intptr_t

// Block header structure
typedef struct Block {
    size_t size;         // Size of the block
    int free;            // Free flag
    struct Block* next;  // Pointer to the next block in the free list
} Block;

#define BLOCK_SIZE sizeof(Block)

// Base pointer to the beginning of the heap
Block* free_list = NULL;

// Function to find a free block in the free list
Block* find_free_block(Block** last, size_t size) {
    Block* curr = free_list;
    while (curr && !(curr->free && curr->size >= size)) {
        *last = curr;
        curr = curr->next;
    }
    return curr;
}

// Function to request more memory from the operating system (using sbrk)
Block* request_space(Block* last, size_t size) {
    Block* block = (Block*)sbrk(0);
    void* request = sbrk(size + BLOCK_SIZE);
    if (request == (void*) -1) { // sbrk failed
        return NULL;
    }

    // Set up the new block
    block->size = size;
    block->free = 0;
    block->next = NULL;

    if (last) {  // If there was a last block, link it
        last->next = block;
    }
    return block;
}

// The simplified malloc function
void* my_malloc(size_t size) {
    Block* block;

    // If it's the first time, initialize the free list
    if (!free_list) {
        block = request_space(NULL, size);
        if (!block) return NULL;  // sbrk failed
        free_list = block;
    } else {
        Block* last = free_list;
        block = find_free_block(&last, size);
        if (!block) {  // No free block found, request more space
            block = request_space(last, size);
            if (!block) return NULL;  // sbrk failed
        } else {  // Free block found
            block->free = 0;
        }
    }

    return (block + 1);  // Return a pointer to the block's data (not the header)
}

// Function to merge adjacent free blocks
void merge_free_blocks() {
    Block* curr = free_list;
    while (curr && curr->next) {
        if (curr->free && curr->next->free) {
            curr->size += curr->next->size + BLOCK_SIZE;
            curr->next = curr->next->next;
        }
        curr = curr->next;
    }
}

// The simplified free function
void my_free(void* ptr) {
    if (!ptr) return;
    // Get the block header from the pointer
    Block* block = (Block*)ptr - 1;
    block->free = 1;
    // Merge adjacent free blocks
    merge_free_blocks();
}

// Example usage
int main() {
    int* a = (int*)my_malloc(10 * sizeof(int));
    for (int i = 0; i < 10; i++) {
        a[i] = i;
        printf("%d ", a[i]);
    }
    printf("\n");
    my_free(a);

    return 0;
}
