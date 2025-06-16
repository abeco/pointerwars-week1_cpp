#ifndef LINKED_LIST_H_
#define LINKED_LIST_H_

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

// Some rules for Pointer Wars 2025:
// 0. Implement all functions in linked_list.cc
// 1. Feel free to add members to the structures, but please do not remove 
//    any or rename any. Doing so will cause test infrastructure to fail
//    to link against your shared library.
// 2. Same goes for the function declarations.
// 3. The malloc_fptr and free_fptr functions are used to allocate
//    memory. Make use of these in your new and delete operators.

// Declaration of the linked_list class.
// Feel free to add additional members as needed, but do not
// remove or delete any.
//
//
class linked_list{
  public:
    // New and delete operators.
    //
    void * operator new();
    void operator delete(void *);

    // Methods to implement.
    //
    bool insert(size_t index, unsigned int data);
    bool insert_front(unsigned int data);
    bool insert_end(unsigned int data);

    size_t find(unsigned int data) const;

    bool remove(size_t index);

    size_t size() const;

    iterator * create_iterator(size_t index);
    iterator * iterate(iterator *);

    // Inner classes.
    //
    struct node {
      void * operator new();
      void operator delete(void*);
      node * next = nullptr;
      unsigned int data;
    };

    struct iterator {
      void * operator new(size_t)
      node * current_node;
      size_t current_index;
      unsigned int data;
    };
  private:
    // The C version always returns a pointer, so no 
    // default constructor that can be called.
    //
    linked_list() {};

    // Private members.
    //
    node * head = nullptr;
};

// Registers malloc() function.
// \param malloc : Function pointer to malloc()-like function.
// Returns TRUE on success, FALSE otherwise.
//
bool linked_list_register_malloc(void * (*malloc)(size_t));
    
// Registers free() function.
// \param free : Function pointer to free()-like function.
// Returns TRUE on success, FALSE otherwise.
//
bool linked_list_register_free(void (*free)(void*));

#endif
