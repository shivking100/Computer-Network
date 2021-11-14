#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
  
int main(){
	// create a socket
	int network_socket;
	network_socket = socket(AF_INET, SOCK_STREAM, 0);
	
	// specify and address for the socket
	struct sockaddr_in server_address;
	server_address.sin_family = AF_INET;
	server_address.sin_port = htons(8080);
	server_address.sin_addr.s_addr = INADDR_ANY;
	
	int connection_status = connect(network_socket, (struct sockaddr *) &server_address, sizeof(server_address));
	
	// check for error in connection
	if(connection_status == -1){
		printf("There was an error making a connection to the remote socket\n\n");
	}
	
	// receive data from the server
	char client_msg[256];
	while(1){
		// send message to server
		printf("Enter your message : ");
		scanf("%s",client_msg);
		send(network_socket, client_msg, sizeof(client_msg), 0);
		
		char server_response[256];
		recv(network_socket, &server_response, sizeof(server_response), 0);
		
		// print out the server's response
		printf("Server : %s\n", 	server_response);
		if(strcmp(server_response, "exit") == 0){
			send(network_socket, "exit", sizeof("exit"), 0);
			close(network_socket);
			return 0;
		}

	}
	
	// close the socket
	close(network_socket);
	
	return 0;
}

