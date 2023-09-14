#include <stdio.h>

int main(){
	int count, hap =0;
	for(count = 1; count<=10;count++){
		hap +=count;
		if(hap%2!=0){
			printf("합이 홀수 입니다 %d\n",hap);
		}
	}
	return 0;
}
