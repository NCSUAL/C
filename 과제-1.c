#include <stdio.h>
static int scanf_int(){
	int a;
	scanf("%d",&a);
	return a;
};

int main(){
	int a1 = scanf_int();
	for(int a=0; a<a1; a++){
		//git ¿äÃ» 
		for(int b=0; b<=a;b++){
			printf(" *");
		}
		printf("\n");
	}
}
