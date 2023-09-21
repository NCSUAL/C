#include <stdio.h>

int scanf_int(){
	int a;
	scanf("%d",&a);
	return a;
}
int main(){
	int number = scanf_int();
	int a; 
	if(number==1){
		printf("1은 소수입니다",number);
	}
	else{
		for(a=2; a<number ;a++){
		if(number%a==0){
			printf("%d은 소수가 아닙니다",number);
			break;
		}
	}
	if(a==number){
		printf("%d은소수입니다",number);
	}
	}
}
