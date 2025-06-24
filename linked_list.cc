#include "linked_list.h"

// Initial declaration of the static member function
// pointers in the linked_list class.
//
void * (*linked_list::malloc_fptr)(size_t) = nullptr;
void (*linked_list::free_fptr)(void*)      = nullptr;

// These static member functions are provided for you. 
// You still need to implement the new() and delete()
// operators.
//
void
linked_list::register_malloc(void *(*malloc)(size_t)) {
    linked_list::malloc_fptr = malloc;
}

void
linked_list::register_free(void (*free)(void*)) {
    linked_list::free_fptr = free;
}
