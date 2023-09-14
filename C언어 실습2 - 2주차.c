#include <stdio.h>
int scanf_int(){
	int a;
	scanf("%d",&a);
	return a;
}
int main(){
	int number = scanf_int();
	printf(number%2==0? "입력한 정수 %d는 짝수 입니다 ": "입력한 정수 %d는 홀수 입니다",number);
}
