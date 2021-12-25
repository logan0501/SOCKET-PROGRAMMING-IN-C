#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<unistd.h>
#include<netdb.h>
#include<stdio.h>
#include<string.h>
#include<arpa/inet.h>
#define MAXLINE 1024

int main(int argc,char **argv) {
int sockfd; 
int n;
int count=0; 

socklen_t len;
char surname[1024],name[1024];
struct sockaddr_in servaddr,cliaddr;
sockfd=socket(AF_INET,SOCK_DGRAM,0);
if(sockfd<0) 
printf("\n error opening the socket"); 
bzero(&servaddr,sizeof(servaddr)); 
servaddr.sin_family=AF_INET; 
servaddr.sin_addr.s_addr=INADDR_ANY;
servaddr.sin_port=htons(5042);
printf("\n\n Binded"); 
bind(sockfd, (struct sockaddr*)&servaddr,sizeof(servaddr));
printf("\n\n Listening..."); 
printf("\n"); 
len=sizeof(cliaddr); 

n=recvfrom(sockfd, surname,MAXLINE,0,(struct sockaddr*)&cliaddr,&len); 
printf("\n Client's Message : %s\n", surname); 
n=recvfrom(sockfd, name,MAXLINE,0,(struct sockaddr*)&cliaddr,&len); 
printf("\n Client's Message : %s\n", name); 
	char pan[10];
	memset(pan,0,10*sizeof(char));
	int k=0;
	srand(time(0));
	 memset(pan, '0', 10*sizeof(pan[0]));
	for(int i=0;i<3;i++)
		pan[k++]=rand()%27+'0'+17;
	pan[k++]='P';
	pan[k++]=surname[0];
	for(int i=0;i<4;i++)
		pan[k++]=rand()%10+48;
pan[k++]=name[0];
pan[k]='\0';
	printf("%s",pan);
sendto(sockfd, pan,sizeof(pan),0,(struct sockaddr*)&cliaddr,len); 
return 0; 
}
