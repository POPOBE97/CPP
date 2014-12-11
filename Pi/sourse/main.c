#include "../header/header.h"

int main (int argc, char* argv[]) {
	int looptimes = 0;
	
	//get a number
	printf("Drop times:\t");
	scanf("%d",&looptimes);
	printf("\n");
	
	printf("result:\t%f\n", pi(looptimes));
	return 0;
}
