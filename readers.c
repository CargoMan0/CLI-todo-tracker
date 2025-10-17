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

int read_task_name(char *task_name) {
    int bytes_read;

    if (task_name == NULL) {
        fprintf(stderr, "task_name is NULL\n");
        return -1;
    }

    bytes_read = scanf("%49s", task_name);
    if (bytes_read != 1) {
        fprintf(stderr, "Invalid task_name input\n");

        int c;
        while ((c = getchar()) != '\n' && c != EOF) {
        }

        return -1;
    }

    return 0;
}
