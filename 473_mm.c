////////////////////////////////////////////////////////////////////////////
//
// File             : 473_mm.c
// Description      : Construct and compare two page replacement algorithms to manage the limited physical memory
//
// Author           : @author
// Last Modified    : @date
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
unsigned long mm_nsigsegvs()
{
/**
 * Fill Your Code Here
 *
 */
	return 0l;
}
void mm_init( void* vm, int vm_size, int n_frames, int page_size , int policy )
{
/**
 * Fill Your Code Here
 *
 */
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
