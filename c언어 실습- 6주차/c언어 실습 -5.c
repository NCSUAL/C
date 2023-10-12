#include <stdio.h>
#include <stdlib.h>
void swap(int *a,int *b){
	int temp = *a;
	*a = *b;
	*b = temp;
}
int scanf_int(){
	int a;
	scanf("%d",&a);
	return a;
}
int main(){
	int a = scanf_int();
	int b=  scanf_int();
	printf("a: %d, b: %d\n",a,b);
	swap(&a,&b);
	printf("a: %d, b: %d",a,b);
}
