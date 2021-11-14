#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdio.h>
#include <unistd.h>
#include <netdb.h>
#include<string.h>
#include<stdlib.h>
int main()
{
    int fd, sb;
    int client_size,cs;
    char b[25],ch;
    fd = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in servaddr,client_addr;
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(6012);
    servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");

    bind(fd, (struct sockaddr *)&servaddr, sizeof(servaddr));
    printf("\nServer ready,waiting for client....\n");
    int a=listen(fd,1);
   
     
    client_size=sizeof(client_addr);
    cs=accept(fd,(struct sockaddr*)&client_addr,&client_size);
    printf("Connected to client at IP: %s and port: %i\n",inet_ntoa(client_addr.sin_addr),ntohs(client_addr.sin_port));
     

    recv(cs,&b, sizeof(b), 0);
    
    printf("FileName received\n");
    int num1,num2,sum;
    FILE *file;
    file=fopen(b,"r");
    if(file==NULL){
        printf("File Not opned\n");

    }
    else{
        printf("File opned\n");
	ch=fgetc(file);
    printf("%c\n",ch);
	num1=ch-'0';
    printf("%d\n",num1);
	ch=fgetc(file);
	ch=fgetc(file);
	num2=ch-'0';
	sum=num1+num2;
    fclose(file);
    printf("File Closed\n");
    send(cs,&sum,sizeof(int),0);
    printf("Data Send\n");
    }
    send(cs,&sum,sizeof(int),0);
    printf("Data Send\n");

    
return 0;
}
