#include <sqlite3.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <time.h>
#define BW 10
#define BH 20
#define random(n) (rand() % (n))

//버퍼 사이즈 정의
#define Buffer 128

typedef struct client_recv_data{
	int recv_board[BW+2][BH+2];
	int send_nx;
	int send_ny;
	int send_brick;
	int send_rot;
	int recv_gameover;
	int recv_score;
} Client_recv_data;

typedef struct enter_client_recv_data{
	int recv_board[BW+2][BH+2];
	int send_nx;
	int send_ny;
	int send_brick;
	int send_rot;
	int recv_gameover;
	int recv_score;
} Enter_client_recv_data;

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
	
	
	
	//소켓 설정 -> 포트 재사용 -> 개발 중에만 사용할 예정 
	int option =12*22;
	if(setsockopt(Sock, SOL_SOCKET, SO_REUSEADDR, &option, sizeof(option))==-1){
		printf("setting error\n");
	}
	else{
		printf("setting complete\n");
	}



	//네트워크 정보 입력 - 서버
	struct sockaddr_in addr_server;
	
	//초기화
	memset(&addr_server,0,sizeof(addr_server));

	//ASCII to integer
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

	//리슨, 유효성 검사 -> 클라이언트 요청을 받음
	if(listen(Sock,43)==-1){
	printf("listen error\n");
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
	
	
		//클라이언트 연결 성공
	
		//방입장 -> 1
		//방생성 -> 0 
		char number[2];
		int Recv = recv(client_socket,number,sizeof(number),0);
		number[1] = '\0';
		if(number[0] =='0'){
		
			//password
			int Rand = (rand()%10000)+1;
		
			char Char_Rand[6];
		
			//integer to ascii
			snprintf(Char_Rand,sizeof(Char_Rand),"%d",Rand);
		
			send(client_socket,Char_Rand,strlen(Char_Rand),0);
		
			//클라이언트2 입장
			struct sockaddr_in enter_client;
			socklen_t enter_client_size = sizeof(enter_client);
		
		/**
			//시간 제한
			fd_set file_descriptor;
		
			//memset 파일 디스크립터 버전 
			FD_ZERO(&file_descriptor);
		
			//fds에 소켓 넣기 
			FD_SET(Sock,&file_descriptor); 
		
			//타임벨류 구조체
			struct timeval timeout;
			timeout.tv_sec = 10; //끝 10 
			timeout.tv_usec = 0; //시작 0
		
			int result = select(Sock+1,&file_descriptor,NULL,NULL,&timeout);
			*/
		 
		 	//select 유효성 
			if(1){
				//입장 클라이언트 소켓 받기 
				int enter_client_socket = accept(Sock,(struct sockaddr*) &enter_client,&enter_client_size);
		
				//유효성 검사
				if(enter_client_socket==-1){
					printf("socket error");
				} 
				else{
					printf("enter OK\n");
				}
		
				//접속 성공할시 
				send(client_socket,"1",1,0);
				
				//방 입장 클라이언트 
				send(enter_client_socket,"OK",2,0);
				
				//게임
				
				//인스턴스 생성
				Client_recv_data client_recv_data; 
				//클라이언트 받을 구조체 초기화
				memset(&client_recv_data,0,sizeof(client_recv_data)); 
				
				//인스턴스 생성
				Enter_client_recv_data enter_client_recv_data; 
				//enter 클라이언트 받을 구조체 초기화 
				memset(&enter_client_recv_data,0,sizeof(enter_client_recv_data)); 
				
				while(1){
				
				int client_socket_data_result = recv(client_socket,&client_recv_data,sizeof(client_recv_data),0);
				sleep(1);
				
				int enter_client_socket_data_result = recv(enter_client_socket,&enter_client_recv_data,sizeof(enter_client_recv_data),0);
				
				for(int a=0; a<12;a++){
					for(int b=0; b<22;b++){
						printf("%d",ntohl(client_recv_data.recv_board[a][b]));
					}
					printf("\n");
				}
				
				for(int a=0; a<12;a++){
					for(int b=0; b<22;b++){
						printf("%d",ntohl(enter_client_recv_data.recv_board[a][b]);
					}
					printf("\n");
				}
				//
				break;
				//
				
				send(enter_client_socket,&client_recv_data,sizeof(client_recv_data),0);
				send(client_socket,&enter_client_recv_data,sizeof(enter_client_recv_data),0);
				
				
				}
			
		}
			
		else{
			printf("select error");
		}
		
		
	}
	
	//방입장 
	else{
		
	} 

	}
	
}

}
