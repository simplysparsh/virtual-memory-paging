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
	int region;
} virtMem;

typedef struct {
	int flag; //to check if it is empty or not
	void *start_mem;
	void *end_mem;
	struct myNode *next;
	struct myNode *previous;
} myNode;
myNode nodee;

// Global Variables
int myType;
int pageSize; // bytes in a page
//// if not in mem then page fault


void mySigHandler()
{
	int *ptr;
	
	pageSize = getpagesize(); // returns # of bytes in a page
	//pageNumber = (si_addr - ptr)/pageSize
	int pageNumber = (si_addr - ptr)/pageSize;
}

// Functions to Implement
unsigned long mm_nsigsegvs()
{
	int i;

	return 0l;
}

void mm_init(void* vm, int vm_size, int n_frames, int page_size , int policy)
{
	myType = policy;
	//int mprotect(void *addr, size_t len, int prot);
	mprotect(vm, page_size, 0); // PROT_NONE for right
	// now do sigaction
	//int sigaction(int signum, const struct sigaction *act, struct sigaction *oldact);
	sigaction( , , mySigHandler());

	if (myType == 1) // FIFO
	{
		
	}
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

