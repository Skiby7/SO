#include <stdio.h>
#include <stdlib.h>
#ifndef INIT_VALUE
#define INIT_VALUE 0
#endif

int somma(int x){
	static int partial = INIT_VALUE; // Init only once
	partial += x;
	return partial;
}
int somma_r(int x, int *save){
	*save += x;
	return *save;
}

int main(int argc, char *argv[]){
	if(argc == 1){
		perror("Argument missing");
		exit(EXIT_FAILURE);
	}
	else if (argc > 2){
		perror("Too many arguments");
		exit(EXIT_FAILURE);
	}
	
	int toAdd = 0;
	for(int i = 0; i < atoi(argv[1]);i++){
		scanf(" %d", &toAdd);
		printf("Somma: %d\n", somma(toAdd));
	}
	int save = INIT_VALUE;
	toAdd = 0;
	for(int i = 0; i < atoi(argv[1]);i++){
		scanf(" %d", &toAdd);
		printf("Somma: %d\n", somma_r(toAdd, &save));
	}
		
	return 0;

}