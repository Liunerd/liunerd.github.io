#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char *argv[]){
	if(argc != 3){
		printf("Error: wrong number of arguments, please input 2 arguments!\n");
		return 0;
	}
	int r = atoi(argv[1]), k = atoi(argv[2]), i, m = 0, c = 0;
	int r_square = r*r;
	srand((unsigned int)time(NULL));
	for(i = 0; i < k; ++i){
		int x = rand()%r, y = rand()%r;
		int dist = x*x + y*y;
		if(x == 0){--i; continue;}
		if(dist < r_square) ++m;
		if(dist == 0) ++c;
	}
	printf("Choose R = %d, K = %d, Pi is: %1.7f\n", r, k, (((float)m)*4+c)/k);
	return 0;
}
