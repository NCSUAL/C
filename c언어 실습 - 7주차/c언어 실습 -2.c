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
		printf("�л� �й�:");
		scanf("%d",&array[a].number);
		printf("�л� �̸�:");
		scanf("%s",array[a].name);
		printf("�л� ����:");
		scanf("%d",&array[a].grade);
	}
	
	for(int a=0; a<n;a++){
		printf("%d\n",array[a].number);
		printf("%s\n",array[a].name);
		printf("%d\n",array[a].grade);
	}
	
	printf("%d",sizeof(information));
}
