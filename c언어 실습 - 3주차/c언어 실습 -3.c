#include <stdio.h>
int scanf_int(){
	int a;
	printf("����� ���丮�� �� �Է�: ");
	scanf("%d",&a);
	return a;
}

int pack(int number,int stack){
	stack = stack*number;
	number = number-1;
	if(number==0){
		return stack;
	}
	else{
		pack(number, stack);
	}
	 
}
int main(){
	int number = scanf_int();
	int pack1 = pack(number,1);
	printf("%d! = %d",number,pack1);
}
