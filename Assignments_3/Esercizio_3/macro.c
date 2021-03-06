#include <stdio.h>
#include <stdlib.h>

#define CHECK_PTR_EXIT(pointer, string)\
			if (pointer == NULL){ perror(string); exit(EXIT_FAILURE);}

#define ELEM(M, i, j)\
			M[(i*dimM) + j]


#define PRINTMAT(M, n, m)\
			for (int i = 0; i < n; i++){\
				for(int j = 0; j < m; j++){\
					printf("%ld\t", ELEM(M,i,j));\
				}\
				puts("");\
			}

			

#define dimN 16
#define dimM  8
int main() {
    long *M = malloc(dimN*dimM*sizeof(long));
	// long *M = NULL;
    CHECK_PTR_EXIT(M, "malloc"); 
    for(size_t i=0;i<dimN;++i)
	for(size_t j=0;j<dimM;++j)			
	    ELEM(M,i,j) = i+j;    
    
    PRINTMAT(M, dimN, dimM);
    free(M);
    return 0;
}