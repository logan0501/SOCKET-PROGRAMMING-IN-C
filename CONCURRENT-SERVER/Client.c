  #include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <time.h>	
#define PORT 4545

struct LIST{
	int item[10];
	int flag[10];
}list1;	

int main(){
	int connfd, val, iteration=0;
	struct sockaddr_in serverAddr;
	char buffer[1024];
	connfd = socket(AF_INET, SOCK_STREAM, 0);
	if(connfd < 0){
		printf("Error in connection...\n");
		exit(1);}
	printf("Socket created successfully...\n");
	memset(&serverAddr, '\0', sizeof(serverAddr));
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(PORT);
	serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	val = connect(connfd, (struct sockaddr*)&serverAddr, sizeof(serverAddr));
	if(val < 0){
		printf("Error in connection...\n");
		exit(1);
	}
	printf("Connected to Server...\n");
	while(iteration<5){
		recv(connfd,&list1,sizeof(list1),0);
		int renum=0,s;
		while(1){
			srand(time(NULL));
			s=rand()%10;
			if(list1.flag[s]!=1){
				renum=list1.item[s];
				list1.flag[s]=1;
				break;
			}
			else
				continue;
		}
		renum=htonl(renum);
		send(connfd,&list1,sizeof(list1),0);
		send(connfd,&renum,sizeof(renum),0);
		iteration++;
	}
	return 0;
}
