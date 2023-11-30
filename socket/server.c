#include <sqlite3.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <time.h>


//버퍼 사이즈 정의 
#define Buffer 128
int main(int argc, char *argv[]){
	printf("%s\n",sqlite3_libversion());
	
	//인자 2개 인지 확인
	if(argc!=2){
		fprintf(stderr,"inja need 2\n");
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
	printf("error_socket\n");
	}
	//소켓 생성 실패
	else{
	printf("socket create\n");
	}

	//네트워크 정보 입력 - 서버
	struct sockaddr_in addr_server;
	
	//초기화
	memset(&addr_server,0,sizeof(addr_server));

	//string -> integer
	int port = atoi(argv[1]);
	
	//정보 입력
	addr_server.sin_family = AF_INET;
	addr_server.sin_addr.s_addr =htonl(INADDR_ANY);
	addr_server.sin_port = htons(port);

	//바인드, 유효성 검사 -> 서버에 이 네트워크 구조를 사용한다고 장치에 알림
	//sockaddr로 형변환 시켜줘야함
	if(bind(Sock, (struct sockaddr*) &addr_server,sizeof(addr_server)) == -1){
	printf("bind error\n");
	}
	else{
	printf("bind complete\n");
	}

	//리슨 -> 클라이언트 요청을 받음
	if(listen(Sock,43)==-1){
	printf("listen function error\n");
	}
	else{
	printf("server Open!\n"); 
	}

	//클라이언트 ipv4주소
	struct sockaddr_in client_server;
	
	//sockaddr_in 사이즈전달 -> socklen_t가 주소길이를 나타내는 데 특화됨
	socklen_t client_server_size = sizeof(client_server);

	//클라이언트 소켓 & 요청 허락
	//sockaddr로 형변환 시켜줘야함
	for(;;){
		
	int client_socket = accept(Sock,(struct sockaddr*) &client_server , &client_server_size);

	//클라이언트 소켓 유효성 검사
	if(client_socket == -1){
	printf("accept_error\n");
	}
	
	else{
	printf("connect complete\n");
	}
	
//클라이언트 연결 성공
	
	//방입장 -> 1 방생성 -> 0 
	char number[2];
	int Recv = recv(client_socket,number,sizeof(number),0);
	number[Recv] = '\0';
	if(number[1]=='0'){
		//password
		int Rand = (rand()%10000)+1;
		
		char Char_Rand[5];
		
		//integer to ascii
		snprintf(Char_Rand,strlen(Char_Rand),"%d",Rand);
		
		send(client_socket,Char_Rand,sizeof(Char_Rand),0);
		
	}
	else{
		
	} 
	
	}
}

