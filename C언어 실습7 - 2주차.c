#include <stdio.h>

int main(){
	int a= 2;
		while(a<=9){
			if(a!=5){
				printf("%d´Ü\n",a);
				for(int b=1; b<=9; b++){
				printf("%d\n", b*a);	
			}
			}
			a++;
		}
}
