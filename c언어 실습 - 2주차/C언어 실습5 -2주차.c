#include <stdio.h>

int main(){
	int count, hap =0;
	for(count = 1; count<=10;count++){
		if(count%2!=0){
			hap +=count;
			printf("%d�� Ȧ�� �Դϴ� �����: %d\n",count,hap);
		}
	}
	return 0;
}
