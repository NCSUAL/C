#include <stdio.h>
#include <stdlib.h>

int scanf_int(){
	int a;
	scanf("%d",&a);
	return a;
}
int main(){
	printf("�л��� �Է�:");
	int n = scanf_int();
	
	int* array = (int*)malloc(n*sizeof(int));
	for(int a=0; a<n;a++){
		printf("�л� # %d-%d �����Է�: ",n,a+1);
		scanf("%d",&array[a]);
	}
	
	int answer = 0;
	for(int a=0; a<n;a++){
		answer+=array[a];
	}
	printf("����: %d\n",answer);
	
	for(int a=0; a<n;a++){
		printf("�л� # %d-%d �������: %d\n",n,a+1,array[a]);
	}
	
	printf("�������: %.1f",(float)answer/n);
	free(array);
	array = NULL;
}
