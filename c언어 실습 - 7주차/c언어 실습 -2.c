#include <stdio.h>
#include <stdlib.h>

typedef struct _information{
	int number;
	char name[100];
	int grade;
}information;
int scanf_int(){
	int a;
	scanf("%d",&a);
	return a;
}
int main(){
	int n = scanf_int();
	information* array = (information*)malloc(n*sizeof(information));
	
	for(int a=0; a<n;a++){
		printf("학생 학번:");
		scanf("%d",&array[a].number);
		printf("학생 이름:");
		scanf("%s",array[a].name);
		printf("학생 성적:");
		scanf("%d",&array[a].grade);
	}
	
	for(int a=0; a<n;a++){
		printf("%d\n",array[a].number);
		printf("%s\n",array[a].name);
		printf("%d\n",array[a].grade);
	}
	
	printf("%d",sizeof(information));
}
