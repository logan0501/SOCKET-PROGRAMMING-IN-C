#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#define SIZE 1024
#define PORT 8000
#define SERVER_IP "127.0.0.1"
#define MAXSZ 100



int main()
{
 int sockfd;

 struct sockaddr_in serverAddress;

 int n;
 char msg1[MAXSZ];
 
char data[SIZE] = {0};
  char *filename = "sample.txt";
  FILE *fp;
 sockfd=socket(AF_INET,SOCK_STREAM,0);
 
 memset(&serverAddress,0,sizeof(serverAddress));
 serverAddress.sin_family=AF_INET;
 serverAddress.sin_addr.s_addr=inet_addr(SERVER_IP);
 serverAddress.sin_port=htons(PORT);

 
 connect(sockfd,(struct sockaddr *)&serverAddress,sizeof(serverAddress));
 

  int words,characters,an,the;
fp = fopen(filename, "r");
  if (fp == NULL) {
    perror("[-]Error in reading file.");
    exit(1);
  }
  


  while(fgets(data, SIZE, fp) != NULL) {

    if (send(sockfd, data, sizeof(data), 0) == -1) {
      perror("[-]Error in sending file.");
      exit(1);
    }
    bzero(data, SIZE);
  }


  n=recv(sockfd,&words,MAXSZ,0);
  words = ntohl(words);
   n=recv(sockfd,&characters,MAXSZ,0);
  characters = ntohl(characters);
   n=recv(sockfd,&an,MAXSZ,0);
  an = ntohl(an);
   n=recv(sockfd,&the,MAXSZ,0);
  the = ntohl(the);
  printf("File information received from server \nReceive message from  server:%d\n",words);
  printf("Total number of Characters%d\n", characters);
  printf("preposition: \n Count of AN:%d Count of THE:%d", an,the);


 return 0;
}
