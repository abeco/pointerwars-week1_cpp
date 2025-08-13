#include "linked_list.h"
#include <new>

// Initial declaration of the static member function
// pointers in the linked_list class.
//
void * (*linked_list::malloc_fptr)(size_t) = nullptr;
void (*linked_list::free_fptr)(void*)      = nullptr;

// These static member functions are provided for you. 
// You still need to implement the new() and delete()
// operators.


// -------------- Node Allocation -----------------
void* linked_list::node::operator new(size_t n) {
    if(linked_list::malloc_fptr) {
        if(void* p = linked_list::malloc_fptr(n)) {
            return p;
        }
        return nullptr; // why would I throw a bad alloc? just return nullptr and handle it
    }
    return ::operator new(n);
}

void linked_list::node::operator delete(void* p) noexcept {
    if(!p) return; // if it already doesn't exist, you're good
    if(linked_list::free_fptr) {
        linked_list::free_fptr(p);
        return;
    }
    ::operator delete(p);
}

// ------------------ linked list allocation---------
void* linked_list::operator new(size_t n) {
    if(linked_list::malloc_fptr) {
        if(void* p = linked_list::malloc_fptr(n)) {
            return p;
        }
        return nullptr;
    }
    return ::operator new(n);
}

void linked_list::operator delete(void* p) noexcept {
    if(!p) return;
    if(linked_list::free_fptr) {
        linked_list::free_fptr(p);
        return;
    }
    ::operator delete(p);
}

// --------- Constructor and Destructor ----------
linked_list::linked_list() 
    : head(nullptr), tail(nullptr), ll_size(0)
{
    LOG_DEBUG("ll constructor");
}

linked_list::~linked_list() {
    node* cur = head;
    while(cur) {
        node* next = cur->next;
        delete cur;
        cur  = next;
    }
    head = nullptr;
    tail = nullptr;
    ll_size = 0;
    LOG_DEBUG("ll destructor, list cleared");
}

// ------------Malloc and free hooks---------------
void linked_list::register_malloc(void *(*malloc)(size_t)) {
    linked_list::malloc_fptr = malloc;
}

void linked_list::register_free(void (*free)(void*)) {
    linked_list::free_fptr = free;
}

// ----------------Helper Functions--------------
linked_list::node* linked_list::get_node(size_t index) {
    if(index < 0 || ll_size < index) return nullptr;
    linked_list::node* current = head;
    while(index--){
        current = current->next;
    }
    return current;
}

// returns const node*, and can't modify this (head, tail, ll_size)
// can't modify contents of node* but can change what it points to
const linked_list::node* linked_list::get_node(size_t index) const {
    if(index < 0 || ll_size < index) return nullptr;
    const linked_list::node* current = head;
    while(index--){
        current = current->next;
    }
    return current;
}

unsigned int& linked_list::operator[](size_t index) {
    node* current = get_node(index);
    return current->data;
}

const unsigned int& linked_list::operator[](size_t index) const {
    const node* current = get_node(index);
    return current->data;
}

// -------------Core Ops-------------------------
bool linked_list::insert_front(unsigned int data) {
    node* n = new node;
    if(!n) return false;
    n->data = data;
    n->next = head;
    head = n;
    // if list was previously empty, we'll be the head and tail
    if(tail == nullptr) {
        tail = n;
    }
    ll_size++;
    return true;
}

bool linked_list::insert_end(unsigned int data) {
    node* n = new node;
    if(!n) return false;
    n->data = data;
    n->next = nullptr; // may as well set it explicitly
    if(!head) {
        // similar to insert_front. If empty, need to also set head
        head = tail = n;
    } else {
        tail->next = n;
        tail = n;
    }
    ll_size++;
    return true;
}

bool linked_list::insert(size_t index, unsigned int data) {
    if(index > ll_size) return false;
    if(index == 0) return insert_front(data);
    if(index == ll_size) return insert_end(data);

    node* prev = get_node(index-1);
    node* newNode = new node();
    if(!newNode) return false;
    newNode->next = prev->next;
    prev->next = newNode;
    newNode->data = data;
    ll_size++;
    return true;
}

bool linked_list::remove(size_t index) {
    if(index > ll_size || ll_size == 0) return false;
    node* prev;
    if(index == 0) {
        // remove head, make head->next the new head, decrement list size
        prev = head;
        head = head->next;
        ll_size--;
        delete prev;
        return true;
    } else {
        prev = get_node(index - 1);
        node* toDelete = prev->next;
        if(toDelete == nullptr) {
            tail = prev;
        }
        prev->next = toDelete->next;
        ll_size--;
        delete toDelete;
        return true;
    }
}

size_t linked_list::find(unsigned int data) const {
    if(ll_size == 0) return SIZE_MAX;
    const node* current = head;
    while(current) {
        if(current->data == data) return current->data;
        current = current->next;
    }
    return SIZE_MAX;
}