#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <netdb.h>
#include<string.h>
#include <netinet/in.h>
#include<stdlib.h>
int main()
{
    int cs, bs,res;
    cs = socket(AF_INET, SOCK_STREAM, 0);
    char c[25];

    struct sockaddr_in server;
    server.sin_family = AF_INET;
    server.sin_port = htons(6012);
    server.sin_addr.s_addr = inet_addr("127.0.0.1");
    connect(cs,(struct sockaddr *)&server,sizeof(struct sockaddr));
    printf("Enter the name of the file to send\n");
    scanf("%s",c);
    send(cs,(void *)c, sizeof(c), 0);
    printf("FileName sent to server\n");
    int n = recv(cs,(void *)&res,sizeof(res),0);
    printf("Addition Result: %d",res);

    close(cs);
}
