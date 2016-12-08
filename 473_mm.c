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
	int pageNumber; // in memory or not
	void *startOfMem;
	int dirtyBit;
	int listLength; // to check if full or not ; Also to increase/dec size
	int permissionFlag; // PROT_NONE, READ, WRITE
	struct pageNode *next;
	struct pageNode *previous;
} pageNode;
pageNode nodee;
pageNode *pagesPtr;
//pageNode *walkList; // pointer to traverse through phys. list

typedef struct {
	int listLengthQ;
	pageNode *head;
	pageNode *tail;
} myQueue;
myQueue *fifoQueue;

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
	pagesPtr = NULL;
	fifoQueue = malloc(sizeof(myQueue));
	fifoQueue->head = NULL;
	fifoQueue->tail = NULL;
	fifoQueue->listLengthQ = 0;

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
	//myPageSize = getpagesize(); // returns # of bytes in a page
	nodee.pageNumber = ( ((int)st.si_addr - (int)myVMStart)/myPageSize ) + 1; // +1 to get to PAGE 1

	//pageNode *walkList; // pointer to traverse through phys. list
	pageNode *walkList = pagesPtr;

	if (myType == FIFO)
	{
		while (walkList != NULL) // page is already in queue/memory
		{
			if (walkList->pageNumber == nodee.pageNumber) // SEG_FAULTS HERE!!
			{//walkList->pageNumber == nodee.pageNumber
				walkList->permissionFlag == 1;
				mprotect(myVMStart, myVMSize, PROT_READ|PROT_WRITE);
				break;
			}
			walkList = walkList->next;
		}
		if (walkList == NULL) // its not in memory
		{
			numFaults++; // if not in mem, then page fault
			// now I have to add to memory....

			//pageNode *newPage = newPageFunc(nodee.pageNumber, myVMStart);
			//enqueue(fifoQueue, newPage);

			if (fifoQueue->listLengthQ >= myNumFrames) // list full so evict
			{
				// now I have to evict....
				
				//pageNode *temp = fifoQueue->head;
				if (fifoQueue->head->next != NULL)
				{
					fifoQueue->head = fifoQueue->head->next;
					fifoQueue->head->previous = NULL;
				}
				else
				{
					fifoQueue->head = NULL;
				}
				fifoQueue->listLengthQ--; // We eject, so minus

				if (pagesPtr->permissionFlag == 1) // its been referenced
				{
					numWriteBacks++;
				}
				// ** after insert plus one to list; eject minus one. **
			}
			else // list not full
			{
				// now I have to add....

				
			}
			mprotect(myVMStart, myVMSize, PROT_READ);
		}
	}
}
/*
pageNode *newPageFunc(int number, void *myVMStart)
{
    pageNode *newPage = malloc(sizeof(pageNode));

    newPage->start = start_addr;
    newPage->size = PAGE_SIZE;
    newPage->number = number;
    newPage->referenced = referenced;
    newPage->modified = modified;

    return newPage;
}*/
/*
void enqueue(virtual_page_queue *queue, virtual_page *page)
{
    // Check if we need to evict any pages first.
    if (queue->size >= NUMBER_OF_FRAMES) {
        virtual_page *evicted_page = dequeue(PAGE_QUEUE);
        // If the page was modified, increment the write back count.
        if (evicted_page->modified == 1) {
            WRITE_BACK_COUNT++;
        }
    }

    if (queue->head == NULL) {
        queue->head = page;
        queue->tail = page;
        page->next = NULL;
    } else {
        page->prev = queue->tail;
        queue->tail->next = page;
        queue->tail = page;
    }
    queue->size++;
}*/

unsigned long mm_nsigsegvs()
{
	
	return 0l;
}

int mm_report_npage_evicts(int i)
{
	
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

