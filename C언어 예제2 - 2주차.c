#include <stdio.h>

char scanf_char();
int main(){
	char ch;
	char str[10];
	
	printf("1.문자입력:");
	scanf("%c",&ch,sizeof(ch));
	
	printf("2.문자입력: ");
	scanf("%s",&str,sizeof(str));
	
	printf("입력한 문자 출력:%c\n",ch);
	printf("입력한 문자열 출력: %s\n",str);
	return 0;
}
