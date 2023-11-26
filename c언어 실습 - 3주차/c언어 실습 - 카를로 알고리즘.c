#include <stdio.h>
#include <stdlib.h>

int scanf_int(){
	int a;
	scanf("%d",&a);
	return a;
}

void swap(int *a,int *b){
	int temp = *a;
	*a = *b;
	*b = temp;
}

int main(){
	printf("배열크기:");
	int length = scanf_int();
	int* array = (int*)malloc(length*sizeof(int));
	
	for(int a=0; a<length; a++){
		scanf("%d",&array[a]);
	}
	
	int index =0;
	int stack = 0;
	while(stack<length-1){
		index = stack;
		for(index; index<length; index++){
			if(array[stack]>array[index]){
				swap(&array[stack],&array[index]);
				printf("1\n");
			}
		}
		stack++;
	}
	
	for(int b=0; b<length;b++){
		printf("%d",array[b]);
	}
	free(array);
}
