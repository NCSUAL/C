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
		printf("1�� �Ҽ��Դϴ�",number);
	}
	else{
		for(a=2; a<number ;a++){
		if(number%a==0){
			printf("%d�� �Ҽ��� �ƴմϴ�",number);
			break;
		}
	}
	if(a==number){
		printf("%d���Ҽ��Դϴ�",number);
	}
	}
}
