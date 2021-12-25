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
}list,list1;

int main(){
	int sockfd, val, i;
	struct sockaddr_in serverAddr;
	int cSocket;
	struct sockaddr_in newAddr;
	list.item[0]=1;
	list.item[1]=3;
	list.item[2]=5;
	list.item[3]=10;
	list.item[4]=15;
	list.item[5]=25;
	list.item[6]=50;
	list.item[7]=100;
	list.item[8]=110;
	list.item[9]=150;
	for(i=0;i<10;i++)
		list.flag[i]=0;
	list1=list;
	socklen_t addr_size;
	char buffer[1024],buff[1024];
	pid_t childpid;
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if(sockfd < 0){
		printf("Error in connection...\n");
		exit(1);
	}
	printf("Socket created successfully...\n");
	memset(&serverAddr, '\0', sizeof(serverAddr));
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(PORT);
	serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	val = bind(sockfd, (struct sockaddr*)&serverAddr, sizeof(serverAddr));
	if(val < 0){
		printf("Binding error...\n");
		exit(1);
	}
	printf("Bind to port %d...\n", 4545);
	if(listen(sockfd, 10) == 0){
		printf("Listening...\n");
	}else{
		printf("Binding error...\n");}
	int iteration=0,client=0,client_port[5],value=0,reward[5]={0},max_reward[5]={0};
	while(1){
	cSocket = accept(sockfd, (struct sockaddr*)&newAddr, &addr_size);
	if(cSocket < 0)
	exit(1);
	client_port[client]=cSocket;
	client=client+1;
	printf("Connection accepted from %s:%d\n", inet_ntoa(newAddr.sin_addr) , ntohs(newAddr.sin_port));
	if((childpid = fork()) == 0){
	close(sockfd);
	if(client==5){
	while(iteration<5){
	int client_value[5]={0};
	printf("\n\nIteration%d:",iteration+1);
	printf("\n\nServer:");
	for(int i=0;i<10;i++)
	printf("%d ",list.item[i]);
	for(int j=0;j<5;j++){
	send(client_port[j], &list1, sizeof(list1), 0);
	recv(client_port[j],&list1,sizeof(list1),0);
	recv(client_port[j],&value,sizeof(value),0);
	client_value[j]=ntohl(value);		
	}
	int lucky_number=list.item[rand()%10];
	printf("\nLucky number: %d",lucky_number);
	int c=-1;
	for(int k=0;k<5;k++){
	printf("\nclient%d: %d\t",k+1,client_value[k]);
	if(lucky_number==client_value[k]){
	reward[k]=reward[k]+100;
	c=k;
	}
	}
	if(c==-1)
	printf("\nAll clients get $0 as reward points...");
	else
	printf("\nClient%d gets $100 as reward points...",c+1);
	for(int m=0;m<10;m++)
	list.flag[m]=0;			
	list1=list;
	iteration++;	
	}
	if(iteration==5){
	int max1=reward[0],c1=0;
	for(int p=1;p<5;p++){
	if(max1<reward[p]){
	max1=reward[p];
	c1=p;
	}
	}
	printf("\n\nThe winner is:");
	for(int i=0;i<5;i++){
	if(max1==reward[i])
	printf("\nClient%d: %d points",i+1,reward[i]);
	}}}}}
	close(cSocket);
	return 0;
}
