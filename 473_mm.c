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
	int size;
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
void *myVMStart;
int myVMSize;
int myNumFrames;
int myPageSize; // bytes in a page
int myNumPages;
int numFaults = 0;

void mm_init(void *vm, int vm_size, int n_frames, int page_size , int policy)
{
	myVMStart = vm;
	myVMSize = vm_size;
	myNumFrames = n_frames;
	myPageSize = page_size;
	myType = policy;

	//int mprotect(void *addr, size_t len, int prot);
	mprotect(vm, vm_size, PROT_NONE); // PROT_NONE for right
	
	//int sigemptyset(sigset_t *set);
	sigset_t *set = &sa.sa_mask;
	sigemptyset(set);

	//now to connect it with 'mySigHandler(sa)'
	sa.sa_handler = mySigHandler(sa);

	//int sigaction(int signum, const struct sigaction *act, struct sigaction *oldact);
	//sigaction( , , mySigHandler());
	sigaction(SIGSEGV, &sa, NULL);
}

// Functions to Implement
void mySigHandler(sa)
{
	// sa.sa_addr == addr_1;
	myPageSize = getpagesize(); // returns # of bytes in a page
	int pageNumber = ( (int)sa.sa_addr - (int)myVMStart )/myPageSize;

	// now have to check if its already in mem
	  // if so, set PROT to Write
	// if not in memory, set PROT to READ
          // then gonna have to add memory
	     // if memory is full then evict based on policy
	     // if memory empty then add
	if (pageNumber != NULL) // page is already in queue/memory
	{
		mprotect(myVMStart, myVMSize, PROT_READ|PROT_WRITE);
	}
	else // not in queue/memory
	{
		// So then add to queue/memory
		numFaults = numFaults + 1;
		mprotect(myVMStart, myVMSize, PROT_READ); // After its in queue, set privelage to READ.
	}
}

void FifoAlg (int index, int found)
{
	int i;

	for (i = 0; i < myNumPages; i++)
	{
		
	}
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
	/* Do Not Have to Implement */
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

