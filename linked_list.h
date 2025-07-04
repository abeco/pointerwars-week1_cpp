#ifndef LINKED_LIST_H_
#define LINKED_LIST_H_

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

// Some rules for Pointer Wars 2025:
// 0. Implement all functions in linked_list.cc
// 1. Feel free to add members to the classes, but please do not remove 
//    any. Doing so will cause test infrastructure to fail to link against 
//    your shared library.
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
    // Constructor. Set head to null.
    //
    linked_list();
    
    // Destructor.
    // Frees all nodes that are present in the linked list.
    //
    virtual ~linked_list();

    // New and delete operators. Needed to support having a 
    // custom allocator, which the testing framework uses.
    //
    void * operator new(size_t size);
    void operator delete(void * ptr);

    // Methods to implement.
    // Returns TRUE on succcess, FALSE otherwise.
    //
    bool insert(size_t index, unsigned int data);
    bool insert_front(unsigned int data);
    bool insert_end(unsigned int data);

    // Returns the first index where data is found
    // in the list, SIZE_MAX otherwise.
    //
    size_t find(unsigned int data) const;

    // Returns TRUE if data at index index was able to be
    // removed, FALSE otherwise.
    //
    bool remove(size_t index);

    // Returns the size of the linked list.
    //
    size_t size() const;

    // Inner classes node and iterator.
    //
    struct node {
      void * operator new(size_t);
      void operator delete(void*);
      node * next;
      unsigned int data;
    };

    // Operator overloads for access to an individual
    // element in the list. They technically offer more
    // flexibility than level 1 of Pointer Wars in the C
    // language in that you can modify them.
    //
    // Like std::vector, bounds checking isn't performed
    // for operator[], and accessing an element out of
    // bounds is undefined behavior.
    //
    unsigned int& operator[](size_t idx);
    const unsigned int& operator[](size_t idx) const;

    // Static members for memory allocation and free
    // function pointers. Very C like.
    //
    static void register_malloc(void * (*malloc)(size_t));
    static void register_free(void (*free)(void*));
    static void * (*malloc_fptr)(size_t);
    static void (*free_fptr)(void*);

  private:
    // The head of the linked list.
    //
    node * head;

    // If you hate this name, feel free to change it.
    //
    size_t ll_size;
};

#endif
