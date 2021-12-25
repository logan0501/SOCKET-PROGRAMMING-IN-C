#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<string.h>
#include<arpa/inet.h>
#include<string.h>
#include<arpa/inet.h>
#include<stdio.h>
#define MAXLINE 1024
int main(int argc,char* argv[]) {
int sockfd; 
int n;
char op[10];
socklen_t len;
char surname[1024],name[1024],recvline[1024]; 
struct sockaddr_in servaddr;

strcpy(surname, "");
strcpy(name, "");
printf("\n Enter the surname : ");
scanf("%s", surname);
sockfd=socket(AF_INET,SOCK_DGRAM,0);
if(sockfd<0)
printf("\n error in creating the socket");
bzero(&servaddr,sizeof(servaddr));

servaddr.sin_family=AF_INET;
servaddr.sin_addr.s_addr=inet_addr("127.0.0.1");
servaddr.sin_port=htons(5042); 

connect(sockfd,(struct sockaddr*)&servaddr,sizeof(servaddr));
len=sizeof(servaddr);

n=sendto(sockfd, surname,MAXLINE,0,(struct sockaddr*)&servaddr,len);
if(n<0) printf("\n error in sendto");
//n=recvfrom(sockfd, recvline, MAXLINE,O,NULL,NULL);

printf("\n Enter the name : ");
scanf("%s", name);
n=sendto(sockfd, name,MAXLINE,0,(struct sockaddr*)&servaddr,len);
memset(op,0,10*sizeof(char));
n=recvfrom(sockfd,op,sizeof(op),0,NULL,NULL);
op[n]='\0';
if(n<0) printf("\n error in reception");
printf("\n PANCARD NUMBER IS %s",op);

return 0; 
}
