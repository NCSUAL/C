#include <stdio.h>
static int scanf_int(){
	int a;
	scanf("%d",&a);
	return a;
};

int main(){
	int output = scanf_int();
	int count =1;
	printf("%d층 피라미드\n",output);
	for(int a=0; a<output; a++){
		for(int b= output-a; b>0; b--){
			printf(" ");
		}
		for(int c = 1; c<=count; c++){
			printf("*");
		}
		count+=2;
		printf("\n");
	}
}
