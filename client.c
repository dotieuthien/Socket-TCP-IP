
/********************************************************************************************
* INCLUDE LIRARY
********************************************************************************************/
#include<stdio.h>
#include <cstdlib>
#include<sys/types.h>
#include<sys/socket.h>
#include<sys/un.h>
#include<unistd.h>

/********************************************************************************************
* MAIN FUNCTION
********************************************************************************************/
int main(){
	int sockfd; //socket file decriptor 
	int len;
	struct sockaddr_un address;
	int result;
	char ch ='A';

	// Create socket for client
	sockfd = socket(AF_UNIX, SOCK_STREAM, 0);
	address.sun_family = AF_UNIX;

	// name of server socket for connecting
	strcpy (address.sun_path, "server_socket");
	len = sizeof(address);

	// Connecting 
	result = connect(sockfd, (struct sockaddr *) & address, len);
	if(result == -1){
		perror("Sorry: client problem");
		exit(1);
	}
	// If have a connetc
	write(sockfd, &ch, 1);
	read(sockfd, &ch, 1);
	printf("char form server = %c\n", ch);
	exit(0);
}