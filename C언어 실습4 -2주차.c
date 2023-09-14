#include <stdio.h>

int main(){
	char season;
	printf("봄: A 또는 a\n");
	printf("여름: S 또는 s\n");
	printf("가을: D 또는 d\n");
	printf("겨울: F 또는 f\n");
	scanf("%c",&season, sizeof(season));
	
	switch(season){
		case 'A':
			printf("만물이 소생하는 계절");
			break;
		case 'B':
			printf("어떤 계절1"); 
		case 'C':
			printf("어떤 계절2"); 
		case 'D':
			printf("어떤 계절3"); 
		case 'E':
			printf("어떤 계절4"); 
		default:
			break;
	}
}
