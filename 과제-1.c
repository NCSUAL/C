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
		if(a%2==0){
			count+=2;
			for(int c=0; c<count; c++){
				printf(" ");
			}
			for(int b=0; b<count; b++){
				printf("*");
			}
		}
		else{
			
		}
	}
}
