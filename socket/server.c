#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

//���� ������ ���� 2232
//�׽�Ʈ 
#define Buffer 128
int main(int argc, char *argv[]){
	//���� 2�� ���� Ȯ��
	if(argc!=2){
		fprintf(stderr,"���� 2����");
		exit(1);
	} 
	
	//���� ���� 
	//PF_INET (protocol family internet) -> ipv4 �������� ����Ѵٴ� ��
	//SOCK_STREAM -> ������ ��Ʈ���������� ����Ѵٴ� ��
	//0 -> �⺻ TCP�� �����Ѵٴ� �� 
	int Sock = socket(PF_INET,SOCK_STREAM,0);
	
	printf("�����۵� ��Ʈ: %s\n",argv[1]);
}
