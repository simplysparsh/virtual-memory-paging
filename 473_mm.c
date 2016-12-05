////////////////////////////////////////////////////////////////////////////
//
// File             : 473_mm.c
// Description      : Construct and compare two page replacement algorithms to manage the limited physical memory
//
// Author           : Sparsh Saxena and Shawn Varughese
// Last Modified    : 12/08/2016
//

// Headers
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/mman.h>
#include "473_mm.h"

// Macros
#define FIFO    1
#define CLOCK   2

// Structures
typedef struct {
	int flag; //to check if it is empty or not
	void *start_mem;
	void *end_mem;
	struct myNode *next;
	struct myNode *previous;
} myNode;
myNode nodee;

// sigaction struct in 'signal.h'
/*struct sigaction{
	void (*sa_handler)(int);
	void (*sa_sigaction)(int, siginfo_t *, void *);
	sigset_t *sa_mask;
	int       sa_flags;
};*/
struct sigaction sa; // using struct from signal.h

// Global Variables
int myType;
int pageSize; // bytes in a page

void mm_init(void* vm, int vm_size, int n_frames, int page_size , int policy)
{
	sigset_t *set = &sa.sa_mask;
	myType = policy;
	//int mprotect(void *addr, size_t len, int prot);
	mprotect(vm, vm_size, PROT_NONE); // PROT_NONE for right
	
	//int sigemptyset(sigset_t *set);
	sigemptyset(set);

	//now to connect it with mySigHandlerFunct()
	sa.sa_handler = mySigHandler(sa);

	//int sigaction(int signum, const struct sigaction *act, struct sigaction *oldact);
	//sigaction( , , mySigHandler());
	sigaction(SIGSEGV, &sa, NULL);
}

// Functions to Implement
void mySigHandler(sa)
{
	// sa.sa_addr == addr_1;
	pageSize = getpagesize(); // returns # of bytes in a page
	int pageNumber = ( (int)sa.sa_addr - (int)vm_start_addr )/pageSize;

	
	// now have to check if its already in mem
	  // if so, set PROT to Write
	// if not in memory, set PROT to READ
          // then gonna have to add memory
	     // if memory is full then evict based on policy
	     // if memory empty then add
}

void FifoAlg (int index, int found)
{
	
}

void ClockAlg (int index, int found)
{
	
}

unsigned long mm_nsigsegvs()
{
	int i;

	return 0l;
}

int mm_report_npage_evicts(int i)
{
/**
 * Fill Your Code Here
 *
 */
	return -1;
}

int mm_report_nframe_evicts(int i)
{
/**
 * Fill Your Code Here
 *
 */
	return -1;
}

unsigned long mm_report_npage_faults()
{
/**
 * Fill Your Code Here
 *
 */
	return 0l;
}

unsigned long mm_report_nwrite_backs()
{
/**
 * Fill Your Code Here
 *
 */
	return 0l;
}

