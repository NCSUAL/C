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
void sort(int* array,int number){
	//�迭 �ޱ� -�ݺ���
	printf("�迭: "); 
	for(int a=0; a<number; a++){
		scanf("%d",&array[a]);
	} 
	
	//����
	int stack= 0;
	int index = 0;
	//Ž���
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
}
int main(){
	//�迭ũ�� �ޱ�
	printf("�迭ũ��:");
	int number = scanf_int();
	
	//�迭 �ޱ� -���� ���� 
	int* array = (int*)malloc(number * sizeof(int));
	
	//���� �Լ�
	sort(array,number);
	
	//���ĵ� �迭
	printf("���ĵ� �迭: ");
	for(int b=0; b<number; b++){
		printf("%d ",array[b]);
	} 
	free(array);
}
