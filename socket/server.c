#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

//버퍼 사이즈 정의 
#define Buffer 128
int main(int argc, char *argv[]){
	//인자 2개 인지 확인
	if(argc!=2){
		fprintf(stderr,"inja need 2");
		exit(1);
	} 
	
	//소켓 생성 
	//PF_INET (protocol family internet) -> ipv4 프로토콜 사용한다는 뜻
	//SOCK_STREAM -> 소켓을 스트림형식으로 사용한다는 뜻
	//0 -> 기본 TCP로 설정한다는 뜻 
	int Sock = socket(PF_INET,SOCK_STREAM,0);
	
	printf("server_port_open: %s\n",argv[1]);

	//소켓 유효성 검사
	if(Sock == -1){
	printf("error_socket");
	}
	else{
	printf("socket create");
	}
}
