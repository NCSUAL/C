#include <stdio.h>

int main(){
	char season;
	printf("��: A �Ǵ� a\n");
	printf("����: S �Ǵ� s\n");
	printf("����: D �Ǵ� d\n");
	printf("�ܿ�: F �Ǵ� f\n");
	scanf("%c",&season, sizeof(season));
	
	switch(season){
		case 'A':
			printf("������ �һ��ϴ� ����");
			break;
		case 'B':
			printf("� ����1"); 
		case 'C':
			printf("� ����2"); 
		case 'D':
			printf("� ����3"); 
		case 'E':
			printf("� ����4"); 
		default:
			break;
	}
}
