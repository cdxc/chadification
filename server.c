#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <unistd.h>
#include <netdb.h>
#include <netinet/in.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>

#define MAX 80
#define PORT 8080
#define SA struct sockaddr

void doChat(int sockfd){
	char buff[MAX];
	int n;
	for(;;){
		bzero(buff, MAX) ;

		/* read message, copy to buff */
		read(sockfd, buff, sizeof(buff));
		/*  */
		printf("From client: %s\t To client: ", buff);
		bzero(buff, MAX);
		n = 0;
		while((buff[n++] = getchar()) != '\n');
		
		write(sockfd, buff, sizeof(buff));

		if(strncmp("exit", buff, 4) == 0){
			printf("exit \n");
			break;
		}
	}
}


int main(){
	int sockfd, connfd, len;
	struct sockaddr_in serveraddr, cli;

	/* socket creater */
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if(sockfd == -1){
		printf("socket creater failed\n");
		exit(0);
	}else{
		bzero(&serveraddr, sizeof(serveraddr));

		serveraddr.sin_family = AF_INET;
		serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);
		serveraddr.sin_port = htons(PORT);

		if((bind(sockfd, (SA*)&serveraddr, sizeof(serveraddr))) != 0 ){
			printf("Socket bind failure;\n");
			exit(0);
		}else{
			printf("Socket bind success!\n ");
			if((listen(sockfd, 5)) != 0){
				printf("listen failure\n");
				exit(0);
			}else{
				printf("Listening on port:");
				len = sizeof(cli);
				connfd = accept(sockfd, (SA*)&cli, &len); 
				if(connfd < 0){
					printf("accept failed,\n");
					exit(0);
				}else{
					printf("accepted the client\n");
					doChat(connfd);
					close(sockfd);
				}
			}
		}
	}
}
