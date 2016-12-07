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
	int pageNumber;
	void *startOfMem;
	int dirtyBit;
	int listLength; // to check if full or not
	struct pageNode *next;
} pageNode;
pageNode nodee;

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
void *myVMStart; // start of memory
int myVMSize;
int myNumFrames;
int myPageSize; // bytes in a page
int myNumPages;
int numFaults = 0;
int numWriteBacks = 0;

void mm_init(void *vm, int vm_size, int n_frames, int page_size , int policy)
{
	myVMStart = vm;
	myVMSize = vm_size;
	myNumFrames = n_frames;
	myPageSize = page_size;
	myType = policy;

	//int mprotect(void *addr, size_t len, int prot);
	mprotect(vm, vm_size, PROT_NONE); // PROT_NONE for right

	sa.sa_flags = SA_RESTART; // restart functions if interrupted by handler
	
	//int sigemptyset(sigset_t *set);
	sigset_t *set = &sa.sa_mask;
	sigemptyset(set);

	//now bind it with 'mySigHandler' function
	sa.sa_handler = mySigHandler(sa);

	//int sigaction(int signum, const struct sigaction *act, struct sigaction *oldact);
	sigaction(SIGSEGV, &sa, NULL); // register signals
}

// Functions to Implement
void mySigHandler(int sigNum, siginfo_t st, void *unused)
{
	// st.si_addr == addr_1;
	myPageSize = getpagesize(); // returns # of bytes in a page
	nodee.pageNumber = ( ((int)st.si_addr - (int)myVMStart)/myPageSize ) + 1; // +1 to get to PAGE 1

	// now have to check if its already in mem
	  // if so, set PROT to Write
	// if not in memory, set PROT to READ
          // then gonna have to add memory
	     // if memory is full then evict based on policy
	     // if memory empty then add
	pageNode *walkList; // pointer to traverse through list

	if (myType == FIFO)
	{
		while (walkList != NULL) // page is already in queue/memory
		{
			if (walkList > 0) // make sure its not empty
			{//walkList->pageNumber == nodee.pageNumber
				mprotect(myVMStart, myVMSize, PROT_READ|PROT_WRITE);
				break;
			}
			walkList = walkList->next;
		}
		if (walkList == NULL) // its not in memory
		{
			numFaults++; // if not in mem, then page fault
			mprotect(myVMStart, myVMSize, PROT_READ);
		}
	}
/*	else // not in queue/memory
	{
		// So then add to queue/memory
		numFaults = numFaults + 1;
		mprotect(myVMStart, myVMSize, PROT_READ); // After its in queue, set permission to READ.
	}*/
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
	return numFaults;

	return 0l;
}

unsigned long mm_report_nwrite_backs()
{
	return numWriteBacks;

	return 0l;
}

