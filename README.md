Pointer Wars 2025: Linked List Edition Week 1

The task for this week is to implement all of the functions declared 
in linked_list.h and have them pass all of the functional tests 
in the provided functional test suite. Once that is complete send us
an email (pointerwars2025@gmail.com).
  For participants in the free tier: we'll let you know about next steps
  for week 2.

  For paying participants: Either attach your code to the email or point
  us at your Github. Assuming your code passes valgrind and functional tests
  we will send you your code feedback and performance results.

In terms of memory allocation and deallocation, your library depends 
on user-specified malloc() and free() functions, registered 
via the linked_list_register_malloc() and linked_list_register_free() 
functions. See the malloc_fptr and free_fptr function pointer variables 
in linked_list.c, which you can use in your implementation of your linked 
list. One of the reasons for this is code like instrumented_malloc() 
in linked_list_test_program.cc. Another reason is to allow you 
to specify to me whether you'd like to use a memory allocation 
library other than libc's implementation of malloc()/free().
