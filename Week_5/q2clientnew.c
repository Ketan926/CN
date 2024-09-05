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
    struct sockaddr_in address;
    sd = socket(AF_INET, SOCK_DGRAM, 0);

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = inet_addr("172.16.57.142");
    address.sin_port = htons(9704);

    char buf[25];
    printf("Enter buf: ");
    fgets(buf, sizeof(buf), stdin);
    buf[strcspn(buf, "\n")] = '\0'; // Remove newline character

    int len = sizeof(address);
    sendto(sd, buf, strlen(buf) + 1, 0, (struct sockaddr *)&address, len);

    int m = recvfrom(sd, buf, sizeof(buf), 0, (struct sockaddr*)&address, &len);
    printf("The server echo is: %s\n", buf);

    int rows, cols;
    printf("Enter number of rows: ");
    scanf("%d", &rows);
    printf("Enter number of columns: ");
    scanf("%d", &cols);
    
    // Send row and column counts
    char row_col[8];
    snprintf(row_col, sizeof(row_col), "%d %d", rows, cols);
    sendto(sd, row_col, strlen(row_col) + 1, 0, (struct sockaddr *)&address, len);

    // Send matrix data
    char arr[cols + 1];
    for (int i = 0; i < rows; i++) {
        printf("Row %d\n", i + 1);
        for (int j = 0; j < cols; j++) {
            printf("Enter value for cell (%d,%d): ", i + 1, j + 1);
            scanf(" %c", &arr[j]);
        }
        arr[cols] = '\0'; // Null-terminate the string
        sendto(sd, arr, sizeof(arr), 0, (struct sockaddr *)&address, len);
    }

    close(sd);
    return 0;
}

