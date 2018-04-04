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
	int server_sockfd, client_sockfd;
	int server_len, client_len;

	struct sockaddr_un server_address;
	struct sockaddr_un client_address;

	// Remove connecting of socket before 
	// Create server socket
	unlink("server_socket");
	server_sockfd = socket(AF_UNIX, SOCK_STREAM, 0);

	// Name for server socket
	server_address.sun_family = AF_UNIX;
	strcpy(server_address.sun_path, "server_socket");
	server_len = sizeof(server_address);
	bind(server_sockfd, (struct sockaddr *)&server_address, server_len);

	// Wait for connecting
	listen(server_sockfd, 5);

	while(1){
		char ch;
		printf("server waiting\n");
		client_sockfd = accept(server_sockfd, (struct sockaddr *) &client_address, (socklen_t*) &client_len);
		read(client_sockfd, &ch, 1);
		ch =+2;
		write(client_sockfd, &ch, 1);
		close(client_sockfd);
	}

}