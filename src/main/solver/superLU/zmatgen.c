#ifdef MIC_TARGET
	#pragma offload_attribute(push, target(mic))
#endif


/*
 * -- SuperLU MT routine (version 2.0) --
 * Lawrence Berkeley National Lab, Univ. of California Berkeley,
 * and Xerox Palo Alto Research Center.
 * September 10, 2007
 *
 */
#include <stdlib.h>
#include "pzsp_defs.h"


/*
 * Generate a banded square matrix A, with dimension n and semi-bandwidth b.
 */
void
zband(int n, int b, int nonz, doublecomplex **nzval, int **rowind, int **colptr)
{
    int iseed[] = {1992,1993,1994,1995};    
    register int i, j, ub, lb, ilow, ihigh, lasta = 0;
    doublecomplex *a;
    int    *asub, *xa;
    doublecomplex *val;
    int    *row;
    extern double dlaran_();
    
    printf("A banded matrix.");
    zallocateA(n, nonz, nzval, rowind, colptr); /* Allocate storage */
    a    = *nzval;
    asub = *rowind;
    xa   = *colptr;
    ub = lb = b;
    
    for (i = 0; i < 4; ++i) iseed[i] = abs( iseed[i] ) % 4096;
    if ( iseed[3] % 2 != 1 ) ++iseed[3];

    for (j = 0; j < n; ++j) {
	xa[j] = lasta;
	val = &a[lasta];
	row = &asub[lasta];
	ilow = SUPERLU_MAX(0, j - ub);
	ihigh = SUPERLU_MIN(n-1, j + lb);
	for (i = ilow; i <= ihigh; ++i) {
	    val[i-ilow].r = dlaran_(iseed);
	    row[i-ilow] = i;
	}
	lasta += ihigh - ilow + 1;
    } /* for j ... */
    xa[n] = lasta;
}

/*
 * Generate a block diagonal matrix A.
 */
void
zblockdiag(int nb, /* number of blocks */
	   int bs, /* block size */
	   int nonz, doublecomplex **nzval, int **rowind, int **colptr)
{
    int iseed[] = {1992,1993,1994,1995};    
    register int i, j, b, n, lasta = 0, cstart, rstart;
    doublecomplex *a;
    int    *asub, *xa;
    doublecomplex *val;
    int    *row;
    extern double dlaran_();
    
    n = bs * nb;
    printf("A block diagonal matrix: nb %d, bs %d, n %d\n", nb, bs, n);
    zallocateA(n, nonz, nzval, rowind, colptr); /* Allocate storage */
    a    = *nzval;
    asub = *rowind;
    xa   = *colptr;
    
    for (i = 0; i < 4; ++i) iseed[i] = abs( iseed[i] ) % 4096;
    if ( iseed[3] % 2 != 1 ) ++iseed[3];

    for (b = 0; b < nb; ++b) {
	cstart = b * bs; /* start of the col # of the current block */
	rstart = b * bs; /* start of the row # of the current block */
	for (j = cstart; j < cstart + bs; ++j) {
	    xa[j] = lasta;
	    val = &a[lasta];
	    row = &asub[lasta];
	    for (i = 0; i < bs; ++i) {
            	val[i].r = dlaran_(iseed);
		row[i] = i + rstart;
	    }
	    lasta += bs;
	} /* for j ... */
    } /* for b ... */
    
    xa[n] = lasta;
}

#ifdef MIC_TARGET
	#pragma offload_attribute(pop)
#endif
