#include <stdio.h>

double sum(double a, double b){
	printf("%lf",a+b);
}

double sub(double a, double b){
	printf("%lf", a-b);
}

double mul(double a, double b){
	printf("%lf", a*b);
}

double div(double a, double b){
	printf("%lf", a/b);
}
void calculator(int selector){
	double num1,num2;
	
	printf("숫자 1을 입력하시오: ");
	scanf("%lf",&num1);
	
	printf("숫자 2를 입력하시오: ");
	scanf("%lf",&num2);
	
	if(selector==1){
		sum(num1,num2);
	}
	else if(selector ==2){
		sub(num1,num2);
	}
	else if(selector==3){
		mul(num1,num2);
	}
	else{
		div(num1,num2);
	}
}
int main(){
	int sel;
	printf("1.더하기 2.빼기 3.곱하기 4.나누기:");
	scanf("%d",&sel);
	
	calculator(sel);
	return 0;
}
