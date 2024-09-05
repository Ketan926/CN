#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

int main() {
    int sd;
    char buf[25];
    struct sockaddr_in sadd, cadd;
    
    sd = socket(AF_INET, SOCK_DGRAM, 0);
    
    sadd.sin_family = AF_INET;
    sadd.sin_addr.s_addr = INADDR_ANY; // Bind to all available interfaces
    sadd.sin_port = htons(9704);
    
    bind(sd, (struct sockaddr *)&sadd, sizeof(sadd));
    
    int len = sizeof(cadd);
    
    // Receive initial message
    int m = recvfrom(sd, buf, sizeof(buf), 0, (struct sockaddr *)&cadd, &len);
    printf("Received initial message: %s\n", buf);
    
    // Send back the initial message
    sendto(sd, buf, strlen(buf) + 1, 0, (struct sockaddr *)&cadd, len);
    
    // Receive rows and columns
    char row_col[8];
    m = recvfrom(sd, row_col, sizeof(row_col), 0, (struct sockaddr *)&cadd, &len);
    int rows, cols;
    sscanf(row_col, "%d %d", &rows, &cols);
    
    printf("Number of rows: %d\n", rows);
    printf("Number of columns: %d\n", cols);

    // Prepare matrix
    int matrix[rows][cols];
    
    // Receive matrix rows
    for (int i = 0; i < rows; i++) {
        m = recvfrom(sd, buf, sizeof(buf), 0, (struct sockaddr *)&cadd, &len);
        for (int j = 0; j < cols; j++) {
            matrix[i][j] = buf[j] - '0'; // Convert char to int
        }
    }

    // Print the matrix
    printf("Matrix received:\n");
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }

    close(sd);
    return 0;
}

