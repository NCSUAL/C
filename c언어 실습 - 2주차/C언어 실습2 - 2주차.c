#include <stdio.h>
int scanf_int(){
	int a;
	scanf("%d",&a);
	return a;
}
int main(){
	int number = scanf_int();
	printf(number%2==0? "�Է��� ���� %d�� ¦�� �Դϴ� ": "�Է��� ���� %d�� Ȧ�� �Դϴ�",number);
}
