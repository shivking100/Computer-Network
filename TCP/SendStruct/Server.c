#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

struct client
{
char name[20];
int user_id;
int pswd;
}c1,c2,c3,c4,c5;

int main(int argc, char* argv[])
{
     
       strcpy(c1.name,"Paddy");
       c1.user_id=1;
       c1.pswd=1;
     
 strcpy(c2.name,"suki");
       c2.user_id=2;
       c2.pswd=2;
     
 strcpy(c3.name,"shinigami");
       c3.user_id=3;
       c3.pswd=3;
      
 strcpy(c4.name,"abhishek");
       c4.user_id=4;
       c4.pswd=4;
     
 strcpy(c5.name,"tuhin");
       c5.user_id=5;
       c5.pswd=5; 
       
	int socket_desc, client_sock, c, read_size;
	struct sockaddr_in server, client;
	int id ,password, i;
	char str[5]="Done", pass[]= "User Found give PASSWORD:", error[]= "Wrong pass word!";

	socket_desc = socket(AF_INET, SOCK_STREAM, 0);
	if (socket_desc == -1) {
		printf("Could not create socket");
	}
	puts("Socket created");

	server.sin_family = AF_INET;
	server.sin_addr.s_addr = INADDR_ANY;
	server.sin_port = htons(8880);

	if (bind(socket_desc, (struct sockaddr*)&server, sizeof(server)) < 0) {

		perror("bind failed. Error");
		return 1;
	}

	listen(socket_desc, 3);

	puts("Waiting for incoming connections...");
	c = sizeof(struct sockaddr_in);

	client_sock = accept(socket_desc, (struct sockaddr*)&client, (socklen_t*)&c);

    if ((read_size = recv(client_sock, &id, sizeof(int), 0)) > 0) {
        puts("Id Received");

	}

    if ((read_size = recv(client_sock, &password, sizeof(int), 0)) > 0) {
        puts("Password Received");

	}

    if(id==c1.user_id && password==c1.pswd){
        char message[30]="Login Successful";
        send(client_sock,&message,sizeof(message),0);
    }
    else if(id==c2.user_id && password==c2.pswd){
        char message[30]="Login Successful";
        send(client_sock,&message,sizeof(message),0);
    }
    else if(id==c3.user_id && password==c3.pswd){
        char message[30]="Login Successful";
        send(client_sock,&message,sizeof(message),0);
    }
    else if(id==c4.user_id && password==c4.pswd){
        char message[30]="Login Successful";
        send(client_sock,&message,sizeof(message),0);
    }
    else if(id==c5.user_id && password==c5.pswd){
        char message[30]="Login Successful";
        send(client_sock,&message,sizeof(message),0);
    }
    else{
        char message[30]="Login Failed";
        send(client_sock,&message,sizeof(message),0);
    }
	
    close(socket_desc);

	return 0;
}