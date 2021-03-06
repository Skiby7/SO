#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <getopt.h>
#define N 10000000
#define K1 100 
#define K2 180
int rand_r(unsigned int *seedp);
long isNumber(const char* s) {
   char* e = NULL;
   long val = strtol(s, &e, 0);
   if (e != NULL && *e == (char)0) return val; 
   return -1;
}

void rand_printer(long int k1, long int k2, long int n){
	int occ[k2-k1+1];
	for(int i = 0; i < (k2-k1)+1; i++)
		occ[i] = 0;
	unsigned int seed = time(NULL);
	for (int i = 0; i < n; i++) { 
    	long int num = (rand_r(&seed) % (k2 - k1 + 1))+k1; 
    	occ[num-k1]++;
	}
	double res = 0.0;
	double toDivide = 0.0;
	double divisor = 0.0;
	for(long int i = 0; i < (k2-k1)+1; i++){
		toDivide = (double)(occ[i]*100);
		divisor = (double) n;
		res = toDivide/divisor;
		printf("%ld\t:\t%.2f%c\n", i+k1, res, '%');
	}
	
}

int main(int argc, char* argv[]){
	long int k1, k2, n;
	k1 = k2 = n = 0;
	if (argc == 1){
		rand_printer(K1,K2,N);
    }
	if(argc == 7){
		int c;
		while((c = getopt(argc, argv, "n:m:s:h")) != -1){ // Char followed by : -> must have an argument, :: -> optional argument. I use s for consistency with the last exercise
			switch (c){
				case 'n':
					isNumber(optarg)>= 0 ? k1 = isNumber(optarg) : printf("Invalid %c", (char) c);
					break;
				case 'm':
					isNumber(optarg)>= 0 ? k2 = isNumber(optarg) : printf("Invalid %c", (char) c);
					break;
				case 's':
					isNumber(optarg)>= 0 ? n = isNumber(optarg) : printf("Invalid %c", (char) c);
					break;
				case 'h':
					printf("nome-programma -n <num. intero> -m <num. intero> -s <stringa> -h\n");
					break;
				case '?':
					printf("%c not defined", (char) c);
					break;
			}
			
		}
		rand_printer(k1,k2,n);
	}
	return 0;
		
}
