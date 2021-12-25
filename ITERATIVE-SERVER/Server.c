#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<string.h>
#include<stdlib.h>
#include<netinet/in.h>

#define PORT 8000
#define MAXSZ 100
#define SIZE 1024


int main()
{
 int sockfd;
 int newsockfd;

 struct sockaddr_in serverAddress;
 struct sockaddr_in clientAddress;

 int n;
 char msg[MAXSZ];
 int clientAddressLength;
  char arr[SIZE];
 
 sockfd=socket(AF_INET,SOCK_STREAM,0);
 
 memset(&serverAddress,0,sizeof(serverAddress));
 serverAddress.sin_family=AF_INET;
 serverAddress.sin_addr.s_addr=htonl(INADDR_ANY);
 serverAddress.sin_port=htons(PORT);

 
 bind(sockfd,(struct sockaddr *)&serverAddress, sizeof(serverAddress));

 
 listen(sockfd,5);

 
 while(1)
 {
  printf("\n*****server waiting for new client connection:*****\n");
  clientAddressLength=sizeof(clientAddress);
  newsockfd=accept(sockfd,(struct sockaddr*)&clientAddress,&clientAddressLength);

  int words =0,characters=0,an=0,the=0;
 
   
    n = recv(newsockfd, arr, SIZE, 0);
    if (n <= 0){
      break;
      return;
    }
   
 
  for(int i=0;arr[i]!='\0';i++){
    characters++;

    if(arr[i]==' ')words++;
    if(arr[i]=='t' && arr[i+1]=='h' && arr[i+2]=='e')the++;
    if(arr[i]=='a' && arr[i+1]=='n' && arr[i+2]==' ')an++;
  }
    bzero(arr, SIZE);
    printf("File information received from server \nReceive message from  server:%d\n",words);
  printf("Total number of Characters%d\n", characters);
  printf("preposition:\n Count of AN: %d Count of THE: %d",an,the);
  
  words=ntohl(words);

sendto(newsockfd, &words, sizeof(words), 0, (struct sockaddr*)&serverAddress, sizeof(serverAddress));
  characters = ntohl(characters);
sendto(newsockfd, &characters, sizeof(characters), 0, (struct sockaddr*)&serverAddress, sizeof(serverAddress));
 an=ntohl(an);
sendto(newsockfd, &an, sizeof(an), 0, (struct sockaddr*)&serverAddress, sizeof(serverAddress));
 the=ntohl(the);
sendto(newsockfd, &the, sizeof(the), 0, (struct sockaddr*)&serverAddress, sizeof(serverAddress));
  }

 return 0;
}
