#include <stdio.h>

static int scanf_int(){
	int a;
	scanf("%d", &a);
	return a;
}
int main(){
	int number = scanf_int();
	if(number>=90){
		printf("A\n");
	}
	else if(number>=80){
		printf("B\n");
	}
	else if(number>=70){
		printf("C\n");
	}
	else if(number>=60){
		printf("D\n");
	}
	else{
		printf("F\n");
	}
}
