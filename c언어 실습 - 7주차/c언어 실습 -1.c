#include <stdio.h>
#include <stdlib.h>

int scanf_int(){
	int a;
	scanf("%d",&a);
	return a;
}
int main(){
	printf("학생수 입력:");
	int n = scanf_int();
	
	int* array = (int*)malloc(n*sizeof(int));
	for(int a=0; a<n;a++){
		printf("학생 # %d-%d 성적입력: ",n,a+1);
		scanf("%d",&array[a]);
	}
	
	int answer = 0;
	for(int a=0; a<n;a++){
		answer+=array[a];
	}
	printf("총점: %d\n",answer);
	
	for(int a=0; a<n;a++){
		printf("학생 # %d-%d 성적출력: %d\n",n,a+1,array[a]);
	}
	
	printf("평균점수: %.1f",(float)answer/n);
	free(array);
	array = NULL;
}
