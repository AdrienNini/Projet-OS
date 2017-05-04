#include <stdio.h>
#include <unistd.h>

int main(){

	int pf[2];
	int fp;

	if (pipe(pf) == -1){
		printf("error\n");
	} else {
		printf("success !\n");
	}

	return 0;

}
