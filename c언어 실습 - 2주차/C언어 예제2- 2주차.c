#include <stdio.h>

struct Value{
	int val_1, val_2,a,b;
};
int main(){
	//�ʱ�ȭ
	struct Value value;
	 
	printf("a=10, b=15 �ϋ�\n");
	
	value.a = 10;
	value.b = 15;
	value.val_1 = ++value.a + value.b--;
	
	printf("1.value_1 = ++a + b-- = %d, a= %d, b=%d\n",value.val_1,value.a,value.b);
	return 0;
}
