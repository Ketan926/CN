#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <fcntl.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <unistd.h>

#define PORTNO 10200
#define BUFSIZE 256

int main() {
    int sockfd, newsockfd, clilen;
    char buf[BUFSIZE];
    struct sockaddr_in seraddr, cliaddr;
    int n;
    int n1, n2, res;
    char op;
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) 
    {
        perror("Error opening socket");
        exit(1);
    }
    seraddr.sin_family = AF_INET;
    seraddr.sin_addr.s_addr = INADDR_ANY;
    seraddr.sin_port = htons(PORTNO);

    if (bind(sockfd, (struct sockaddr *)&seraddr, sizeof(seraddr)) < 0) 
    {
        perror("Error on binding");
        exit(1);
    }
    listen(sockfd, 5);
    clilen = sizeof(cliaddr);
    while (1) 
    {
        newsockfd = accept(sockfd, (struct sockaddr *)&cliaddr, &clilen);
        if (newsockfd < 0) 
        {
            perror("Error on accept");
            continue;
        }
        if (fork() == 0) 
        {
            close(sockfd);
            memset(buf, 0, BUFSIZE);
            n = read(newsockfd, buf, BUFSIZE-1);
            if (n < 0) 
            {
                perror("Error reading from socket");
                close(newsockfd);
                exit(1);
            }
            buf[n] = '\0';
            sscanf(buf, "%d %c %d", &n1, &op, &n2);
            switch(op) {
                case '+': res = n1 + n2; break;
                case '-': res = n1 - n2; break;
                case '*': res = n1 * n2; break;
                case '/':
                    if (n2 == 0) 
                    {
                        strcpy(buf, "Error: Division by zero");
                        write(newsockfd, buf, strlen(buf));
                        close(newsockfd);
                        exit(1);
                    }
                    res = n1 / n2;
                    break;
                default:
                    strcpy(buf, "Error: Invalid operator");
                    write(newsockfd, buf, strlen(buf));
                    close(newsockfd);
                    exit(1);
            }

            snprintf(buf, BUFSIZE, "%d", res);
            write(newsockfd, buf, strlen(buf));
            close(newsockfd);
            exit(0);
        } 
        else 
        {
            close(newsockfd);
        }
    }
    return 0;
}

