#include "../includes/tokenizer.h"

int main(int argc, char* argv[]){
	for(int i = 1; i < argc; i++){
		tokenizer_r(argv[i]);
	}
	return 1;
}