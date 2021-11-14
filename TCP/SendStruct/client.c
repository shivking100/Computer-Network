#include <sys/types.h>     
#include <sys/socket.h>
#include<stdio.h>
#include <arpa/inet.h>
#include<unistd.h>
#include<string.h>

int main(int argc, char* argv[])
{
	int sock;
	struct sockaddr_in server;
	char server_reply[20];
	int number, temp;

       

	sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock == -1) {
		printf("Could not create socket");
	}
	puts("Socket created");

	server.sin_addr.s_addr = inet_addr("127.0.0.1");
	server.sin_family = AF_INET;
	server.sin_port = htons(8880);

	if (connect(sock, (struct sockaddr*)&server, sizeof(server)) < 0) {
		perror("connect failed. Error");
		return 1;
	}

    printf("Enter User id : ");
    scanf("%d",&number);
	if (send(sock, &number, sizeof(int), 0) < 0) {
		printf("Send failed");
		return 1;
	}
	

	printf("Enter password : ");
    scanf("%d",&number);   
    if (send(sock, &number, sizeof(int), 0) < 0) {
		printf("Send failed");
		return 1;
	}
	
	if (recv(sock, &server_reply, sizeof(server_reply), 0) < 0) {
		printf("recv failed");}

    printf("%s",server_reply);
	
	return 0;
}