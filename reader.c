//
// Created by Wilhelm Reich on 17.10.2025.
//

#import <stdio.h>

int read_number(int *number_ptr) {
    int bytes_read;

    if (number_ptr == NULL) {
        fprintf(stderr, "number_ptr is NULL\n");
        return -1;
    }

    bytes_read = scanf("%d", number_ptr);
    if (bytes_read != 1) {
        fprintf(stderr, "Error reading number: Wrong amount of bytes written from stdin\n");

        int c;
        while ((c = getchar()) != '\n' && c != EOF) {
        }

        return -2;
    }

    return 0;
}
