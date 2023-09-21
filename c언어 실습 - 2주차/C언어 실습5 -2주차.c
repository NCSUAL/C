#include <stdio.h>

int main(){
	int count, hap =0;
	for(count = 1; count<=10;count++){
		if(count%2!=0){
			hap +=count;
			printf("%d가 홀수 입니다 결과값: %d\n",count,hap);
		}
	}
	return 0;
}
