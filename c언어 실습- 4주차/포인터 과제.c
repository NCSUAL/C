#include <stdio.h>
#include <stdlib.h>
int scanf_int(){
	int a;
	scanf("%d",&a);
	return a;
}
void swap(int *a, int *b){
	int temp = *a;
	*a = *b;
	*b = temp;
}
void sort(number){
	//배열 받기 -변수 선언 
	int* array = (int*)malloc(number * sizeof(int));
	//배열 받기 -반복문
	printf("배열: "); 
	for(int a=0; a<number; a++){
		scanf("%d",&array[a]);
	} 
	
	//정렬
	int stack= 0;
	int index = 0;
	//탐욕법
	while(1){
		if(index==number){
			stack ++;
			index= stack;
		}
		else if(stack==number){
			break;
		}
		if(array[stack]>array[index]){
			swap(&array[stack],&array[index]);
			index++;
		}
		else{
			index++;
		}
	}
	printf("정렬된 배열: ");
	for(int b=0; b<number; b++){
		printf("%d ",array[b]);
	} 
	free(array);
}
int main(){
	//배열크기 받기
	printf("배열크기:");
	int number = scanf_int();
	sort(number);
}
