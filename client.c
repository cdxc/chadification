#include <netdb.h> 
#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include <strings.h>
#include <unistd.h>
#include <sys/socket.h> 

#define MAX 80 
#define PORT 8080 
#define SA struct sockaddr 

void doChat(int sockfd){
int n;
char buff[MAX];
for(;;){
	bzero(buff, sizeof(buff));
	printf("> ", buff);
	n=0;
	while((buff[n++] = getchar()) != '\n'){;}

	write(sockfd, buff, sizeof(buff));
	bzero(buff, sizeof(buff));
	if(sizeof(buff) == 0){
		read(sockfd, buff, sizeof(buff));
		printf(">> %s ", buff);
	}
	if(strncmp("exit", buff, 4) == 0){
		printf("exit \n");
		break;
		}
	}
}


int main(){ 
    int sockfd, connfd; 
    struct sockaddr_in servaddr, cli; 
  
    sockfd = socket(AF_INET, SOCK_STREAM, 0); 
    if(sockfd == -1){ 
        printf("socket create failed...\n"); 
        exit(0); 
    }else{
        printf("Socket create successfull..\n"); 
    	bzero(&servaddr, sizeof(servaddr)); 
  
    	servaddr.sin_family = AF_INET; 
    	servaddr.sin_addr.s_addr = inet_addr("192.168.1.24"); 
    	servaddr.sin_port = htons(PORT); 
  
    	if(connect(sockfd, (SA*)&servaddr, sizeof(servaddr)) != 0){ 
    	    printf("connection with the server failed...\n"); 
    	    exit(0); 
    	}else{
    	    printf("connected to the server..\n"); 
  			doChat(sockfd);
    		close(sockfd); 
		}
	}
}
