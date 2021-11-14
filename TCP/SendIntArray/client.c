// Client code in C to sort the array
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
  

// Driver code
int main(int argc, char *argv[])
{
    int sock;
    struct sockaddr_in server;
    int server_reply[10];
    int arr1[5] = {8, 6, 4, 2, 0}, i, temp;
    int arr2[5] = {9, 7, 5, 3, 1};

    // Create socket
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == -1)
    {
        printf("Could not create socket");
    }
    puts("Socket created");

    server.sin_addr.s_addr = inet_addr("127.0.0.1");
    server.sin_family = AF_INET;
    server.sin_port = htons(8880);

    // Connect to remote server
    if (connect(sock, (struct sockaddr *)&server, sizeof(server)) < 0)
    {
        perror("connect failed. Error");
        return 1;
    }

    puts("Connected\n");

    if (send(sock, &arr1, 5 * sizeof(int), 0) < 0)
    {
        puts("Send failed array1");
        return 1;
    }

    if (send(sock, &arr2, 5 * sizeof(int), 0) < 0)
    {
        puts("Send failed array2");
        return 1;
    }

    // Receive a reply from the server
    if (recv(sock, &server_reply, 10 * sizeof(int), 0) < 0)
    {
        puts("recv failed");
        return 0;
    }

    puts("Server reply :\n");
    for (i = 0; i < 10; i++)
    {
        printf("%d\n", server_reply[i]);
    }

    // close the socket
    close(sock);
    return 0;
}
