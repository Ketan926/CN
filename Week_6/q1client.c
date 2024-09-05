#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>

#define PORTNO 10200
#define BUFSIZE 256

int main() {
    int sd, result;
    struct sockaddr_in address;
    char buf[BUFSIZE];
    sd = socket(AF_INET, SOCK_STREAM, 0);
    if (sd < 0) 
    {
        perror("Error opening socket");
        exit(1);
    }
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = inet_addr("127.0.0.1"); // Use localhost for testing
    address.sin_port = htons(PORTNO);
    if (connect(sd, (struct sockaddr *)&address, sizeof(address)) < 0) 
    {
        perror("Error connecting");
        close(sd);
        exit(1);
    }
    printf("Enter expression (e.g., 12 + 7): ");
    fgets(buf, BUFSIZE, stdin);
    buf[strcspn(buf, "\n")] = 0; // Remove newline character
    write(sd, buf, strlen(buf));
    memset(buf, 0, BUFSIZE);
    result = read(sd, buf, BUFSIZE-1);
    if (result < 0) 
    {
        perror("Error reading from socket");
        close(sd);
        exit(1);
    }
    buf[result] = '\0';
    printf("Server response: %s\n", buf);
    close(sd);
    return 0;
}

