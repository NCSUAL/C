#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h> 

int main(){
	int Round = pow(10,9);
	int count = 1;
	int p = pow(10,7);
	double x =0;
	double y=0, R =0;
	
	int circle = 0;
	double k,res;
	srand(time(NULL));
	
	for(int a=1; a<=Round; a++){
		x = (double)rand() / (double)RAND_MAX;
		y = (double)rand() / (double)RAND_MAX;
		R = x*x + y*y;
		if(R<=1){
			circle++;
		}
		if(a%p==0){
			k = (double)circle / a;
			res = (double)k * 4;
			printf("%d%% 진행, 현재 원주율: %f\n",count,res);
			count++;
		}
	}
	printf("최종 원주율: %f", res);
}
