#include <stdio.h>
int scanf_int(){
	int a;
	scanf("%d",&a);
	return a;
}
int main(){
	int number = scanf_int();
	if(number%4==0 && number%100!=0|| number%400==0){
		printf("¿±≥‚¿‘¥œ¥Ÿ");
	}
	else{
		printf("¿±≥‚¿Ã æ∆¥’¥œ¥Ÿ");
	}
}
