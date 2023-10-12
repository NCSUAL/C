#include <stdio.h>
#include <stdlib.h>

int main() {
	int score[5] = {87,92,89,98,78};
	int cnt;
	int *arr = &score[0]; 
	printf("score[5] = {87,92,89,98,78} 배열 요소 출력\n");
	
	for(cnt =0; cnt<5; cnt++){
		printf("score[%d]= [%d]\n",cnt,*arr);
		arr+=1;
	}
	
	return 0;
}
