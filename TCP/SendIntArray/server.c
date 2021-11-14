// Server code in C to sort the array
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
  

void bubble_sort(int[], int);

void mergeSorted(int src1[], int src2[], 
  int newArr[], int n1, int n2)
{
  int i = 0, j = 0, k = 0; 


  while (i < n1 && j < n2) 
  { 
    if (src1[i] <= src2[j]) 
    { 
      newArr[k++] = src1[i++]; 
    } 
    else 
    { 
      newArr[k++] = src2[j++]; 
    } 
  }     
  while (i < n1) 
  {
    newArr[k++] = src1[i++]; 
  }
  while (j < n2) 
  {   
    newArr[k++] = src2[j++]; 
  } 
}

// Driver code
int main(int argc, char* argv[])
{
	int socket_desc, client_sock, c, read_size;
	struct sockaddr_in server, client;
	int arr1[5], i,arr2[5];

	// Create socket
	socket_desc = socket(AF_INET, SOCK_STREAM, 0);
	if (socket_desc == -1) {
		printf("Could not create socket");
	}
	puts("Socket created");

	// Prepare the sockaddr_in structure
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = INADDR_ANY;
	server.sin_port = htons(8880);

	// Bind the socket
	if (bind(socket_desc, (struct sockaddr*)&server, sizeof(server)) < 0) {

		// print the error arr1
		perror("bind failed. Error");
		return 1;
	}
	puts("bind done");

	// lsiten to the socket
	if(listen(socket_desc, 5) < 0) printf("listen failed\n");
	else printf("listening\n");

	puts("Waiting for incoming connections...");
	c = sizeof(struct sockaddr_in);

	// accept connection from an incoming client
	client_sock = accept(socket_desc, (struct sockaddr*)&client, (socklen_t*)&c);

	if (client_sock < 0) {
		perror("accept failed");
		return 1;
	}

	puts("Connection accepted");

	// Receive a arr1 from client
	if ((read_size = recv(client_sock, &arr1, 5 * sizeof(int), 0)) > 0) {
        puts("array 1 rec");
		bubble_sort(arr1, 5);
        puts("array 1 sorted");

	}

   if ((read_size = recv(client_sock, &arr2, 5 * sizeof(int), 0)) > 0) {
        puts("array 2 rec");
		bubble_sort(arr2, 5);
        puts("array 2 sorted");

	}

    int arr3[10];
    mergeSorted(arr1,arr2,arr3,5,5);
	send(client_sock, &arr3, 10 * sizeof(int),0);



	if (read_size == 0) {
		puts("Client disconnected");
	}
	else if (read_size == -1) {
		perror("recv failed");
	}

	return 0;
}

// Function to sort the array
void bubble_sort(int list[], int n)
{
	int c, d, t;

	for (c = 0; c < (n - 1); c++) {
		for (d = 0; d < n - c - 1; d++) {
			if (list[d] > list[d + 1]) {

				/* Swapping */
				t = list[d];
				list[d] = list[d + 1];
				list[d + 1] = t;
			}
		}
	}
}
