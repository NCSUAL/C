//�����(GCC) ȯ�濡�� �����ؾ� �մϴ�. 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <pthread.h>
#include <time.h>
#define BW 10
#define BH 20
#define random(n) (rand() % (n))

//���� ������ ����
#define Buffer 128

//Ŭ���̾�Ʈ1 ������
typedef struct client_recv_data{
	//���� ���� ����
	int send_board[BW+2][BH+2];

	// NEXT ��� -> ������ �� brick
	int send_nextBrick;

	// HOLD ��� -> Ȧ�� ��� ����
	int send_One_chance;

	//HOLD ��� -> ������ brick
   	int send_REMOVE_BRICK;

	//HOLD ��� -> ������ Rot
   	int send_REMOVE_ROT;

	//HOLD ��� -> Ȧ�� �� ���� �ٽ� �ҷ����� �� ����
   	int send_PREESED_HOLD;

	//Speed ��� -> ���� speed
   	int send_speed;

	//���� ��� nx
	int send_nx;

	//���� ��� ny
	int send_ny;

	//���� ��� brick
	int send_brick;

	//���� ��� rot
	int send_rot;

	//������ �������� ����
	int send_gameover;

	//���� ����
	int send_score;
} Client_recv_data;

//Ŭ���̾�Ʈ2(������ Ŭ���̾�Ʈ) ������ -> ���� �Ȱ���
typedef struct enter_client_recv_data{
	int send_board[BW+2][BH+2];
	int send_nextBrick;
	int send_One_chance;
	int send_REMOVE_BRICK;
   	int send_REMOVE_ROT;
   	int send_PREESED_HOLD;
   	int send_speed;
	int send_nx;
	int send_ny;
	int send_brick;
	int send_rot;
	int send_gameover;
	int send_score;
} Enter_client_recv_data;


int main(int argc, char *argv[]){
	
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
	
		
			//Ŭ���̾�Ʈ2 ����
			struct sockaddr_in enter_client;
			socklen_t enter_client_size = sizeof(enter_client);
		

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
		 
		 	//select ��ȿ�� 
			if(result!=0){
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
				send(enter_client_socket,"1",2,0);


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
				
				//������ ��ȯ 
				int client_socket_data_result = recv(client_socket,&client_recv_data,sizeof(client_recv_data),0);
				
				int enter_client_socket_data_result = recv(enter_client_socket,&enter_client_recv_data,sizeof(enter_client_recv_data),0);
				
				// Ŭ���̾�Ʈ �� �ϳ��� ������ ������ ���
				if (client_socket_data_result <= 0 || enter_client_socket_data_result <= 0) {
        			printf("Client disconnected\n");
        			close(client_socket);
        			close(enter_client_socket);
       				 break; // ���� ���� ����
    			}
					
				int clinet_socket_data_send_result = send(enter_client_socket,&client_recv_data,sizeof(client_recv_data),0);
				int enter_clinet_socket_data_send_result = send(client_socket,&enter_client_recv_data,sizeof(enter_client_recv_data),0);
				
				//������ ��ȯ
				if(clinet_socket_data_send_result<=0 || enter_clinet_socket_data_send_result<=0){
					printf("Client disconnected\n");
        			close(client_socket);
        			close(enter_client_socket);
       				 break; // ���� ���� ����
				}

				if(ntohl(client_recv_data.send_gameover)==1 && ntohl(enter_client_recv_data.send_gameover)==1){
					//���� �� 
					//���� ���� 
					close(enter_client_socket);
					close(client_socket);
					break;
				}
				}
				
				
			
		}
			
		else{
			//�ð��ʰ� 
			send(client_socket,"0",1,0);
			printf("select error\n");
		}
		
		 

	}
	
}

}
