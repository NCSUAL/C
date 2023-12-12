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

//���� ������ ����
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
	
	//���� 2�� ���� Ȯ��
	if(argc!=2){
		fprintf(stderr,"inja need 2\n");
		exit(1);
	} 
	
	//���� ���� 
	//PF_INET (protocol family internet) -> ipv4 �������� ����Ѵٴ� ��
	//SOCK_STREAM -> ������ ��Ʈ���������� ����Ѵٴ� ��
	//0 -> �⺻ TCP�� �����Ѵٴ� �� 
	int Sock = socket(PF_INET,SOCK_STREAM,0);
	
	printf("server_port_open: %s\n",argv[1]);

	//���� ��ȿ�� �˻�
	if(Sock == -1){
	printf("error_socket\n");
	}
	//���� ���� ����
	else{
	printf("socket create\n");
	}
	
	
	
	//���� ���� -> ��Ʈ ���� -> ���� �߿��� ����� ���� 
	int option =12*22;
	if(setsockopt(Sock, SOL_SOCKET, SO_REUSEADDR, &option, sizeof(option))==-1){
		printf("setting error\n");
	}
	else{
		printf("setting complete\n");
	}



	//��Ʈ��ũ ���� �Է� - ����
	struct sockaddr_in addr_server;
	
	//�ʱ�ȭ
	memset(&addr_server,0,sizeof(addr_server));

	//ASCII to integer
	int port = atoi(argv[1]);
	
	//���� �Է�
	addr_server.sin_family = AF_INET;
	addr_server.sin_addr.s_addr =htonl(INADDR_ANY);
	addr_server.sin_port = htons(port);

	//���ε�, ��ȿ�� �˻� -> ������ �� ��Ʈ��ũ ������ ����Ѵٰ� ��ġ�� �˸�
	//sockaddr�� ����ȯ ���������
	if(bind(Sock, (struct sockaddr*) &addr_server,sizeof(addr_server)) == -1){
	printf("bind error\n");
	}
	else{
	printf("bind complete\n");
	}

	//����, ��ȿ�� �˻� -> Ŭ���̾�Ʈ ��û�� ����
	if(listen(Sock,43)==-1){
	printf("listen error\n");
	}
	else{
	printf("server Open!\n"); 
	}

	//Ŭ���̾�Ʈ ipv4�ּ�
	struct sockaddr_in client_server;
	
	//sockaddr_in ���������� -> socklen_t�� �ּұ��̸� ��Ÿ���� �� Ưȭ��
	socklen_t client_server_size = sizeof(client_server);

	//Ŭ���̾�Ʈ ���� & ��û ���
	//sockaddr�� ����ȯ ���������
for(;;){ 

	int client_socket = accept(Sock,(struct sockaddr*) &client_server , &client_server_size);

	//Ŭ���̾�Ʈ ���� ��ȿ�� �˻�
	if(client_socket == -1){
		printf("accept_error\n");
	}
	
	else{
		printf("connect complete\n");
	
	
		//Ŭ���̾�Ʈ ���� ����
	
		//������ -> 1
		//����� -> 0 
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
		
			//Ŭ���̾�Ʈ2 ����
			struct sockaddr_in enter_client;
			socklen_t enter_client_size = sizeof(enter_client);
		
		/**
			//�ð� ����
			fd_set file_descriptor;
		
			//memset ���� ��ũ���� ���� 
			FD_ZERO(&file_descriptor);
		
			//fds�� ���� �ֱ� 
			FD_SET(Sock,&file_descriptor); 
		
			//Ÿ�Ӻ��� ����ü
			struct timeval timeout;
			timeout.tv_sec = 10; //�� 10 
			timeout.tv_usec = 0; //���� 0
		
			int result = select(Sock+1,&file_descriptor,NULL,NULL,&timeout);
			*/
		 
		 	//select ��ȿ�� 
			if(1){
				//���� Ŭ���̾�Ʈ ���� �ޱ� 
				int enter_client_socket = accept(Sock,(struct sockaddr*) &enter_client,&enter_client_size);
		
				//��ȿ�� �˻�
				if(enter_client_socket==-1){
					printf("socket error");
				} 
				else{
					printf("enter OK\n");
				}
		
				//���� �����ҽ� 
				send(client_socket,"1",1,0);
				
				//�� ���� Ŭ���̾�Ʈ 
				send(enter_client_socket,"OK",2,0);
				
				//����
				
				//�ν��Ͻ� ����
				Client_recv_data client_recv_data; 
				//Ŭ���̾�Ʈ ���� ����ü �ʱ�ȭ
				memset(&client_recv_data,0,sizeof(client_recv_data)); 
				
				//�ν��Ͻ� ����
				Enter_client_recv_data enter_client_recv_data; 
				//enter Ŭ���̾�Ʈ ���� ����ü �ʱ�ȭ 
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
	
	//������ 
	else{
		
	} 

	}
	
}

}
