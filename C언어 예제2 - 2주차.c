#include <stdio.h>

char scanf_char();
int main(){
	char ch;
	char str[10];
	
	printf("1.�����Է�:");
	scanf("%c",&ch,sizeof(ch));
	
	printf("2.�����Է�: ");
	scanf("%s",&str,sizeof(str));
	
	printf("�Է��� ���� ���:%c\n",ch);
	printf("�Է��� ���ڿ� ���: %s\n",str);
	return 0;
}
