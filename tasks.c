//
// Created by Wilhelm Reich on 17.10.2025.
//

#include "tasks.h"
#include "readers.h"
#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int add_task(struct Task **tasks, int *count) {
    int err_code, priority;
    char name[50];

    if (*tasks == NULL) {
        fprintf(stderr, "Critical bug: Tasks array is NULL\n");
        return -1;
    }

    struct Task *tmp = realloc(*tasks, sizeof(struct Task) * (*count + 1));
    if (tmp == NULL) {
        fprintf(stderr, "realloc() failed. Tasks is NULL\n");
        return -1;
    }
    *tasks = tmp;

    printf("Enter Task Name: ");
    err_code = read_task_name(name);
    if (err_code != 0) {
        return err_code;
    }

    printf("Enter Task Priority (0–3): ");
    err_code = read_number(&priority);
    if (err_code != 0) {
        return err_code;
    }

    if (priority < 0 || priority > 3) {
        fprintf(stderr, "Priority must be between 0 and 3\n");
        return -1;
    }

    strncpy((*tasks)[*count].name, name, sizeof((*tasks)[*count].name));
    (*tasks)[*count].name[sizeof((*tasks)[*count].name) - 1] = '\0';
    (*tasks)[*count].priority = priority;
    (*tasks)[*count].isDone = 0;

    (*count)++;

    return 0;
}

int delete_task(struct Task **tasks, int *count, const int id) {
    if (*tasks == NULL) {
        fprintf(stderr, "Critical bug: Tasks array is NULL\n");
        return -1;
    }

    if (id > *count) {
        fprintf(stderr, "Task with id: %d does not exist\n", id);
        return -2;
    }

    for (int i = id - 1; i < *count - 1; i++) {
        (*tasks)[i] = (*tasks)[i + 1];
    }

    struct Task *tmp = realloc(*tasks, sizeof(struct Task) * (*count - 1));
    if (tmp == NULL) {
        fprintf(stderr, "realloc() failed. Tasks is NULL\n");
        return -1;
    }

    *tasks = tmp;
    (*count)--;

    return 0;
}

int get_tasks(struct Task *tasks, const int count) {
    char *is_done_bool;

    if (count == 0) {
        printf("No tasks found\n");
        return 0;
    }

    printf("=========================\n");
    for (int i = 0; i < count; i++) {
        if (tasks[i].isDone) {
            is_done_bool = "true";
        } else {
            is_done_bool = "false";
        }

        printf("Task[%d]\n"
               "Task Name: %s \n"
               "Priority: %d\n"
               "Done: %s\n"
               "=========================\n"
               ,
               i + 1, tasks[i].name, tasks[i].priority, is_done_bool
        );
    }

    return 0;
}

int mark_task_done(struct Task **tasks, const int count, const int id) {
    if (*tasks == NULL) {
        fprintf(stderr, "Critical bug: Tasks array is NULL\n");
        return -1;
    }

    if (id > count) {
        fprintf(stderr, "Task with id: %d does not exist\n", id);
        return -2;
    }

    if ((*tasks)[id].isDone) {
        printf("Task[%d] is already marked as Done\n", id);
        return 0;
    }

    (*tasks)[id - 1].isDone = 1;

    printf("Task[%d] is now marked as Done\n", id);
    return 0;
}

int save_tasks_to_file(struct Task *tasks, const int count) {
    int err_code;
    FILE *file = fopen("tasks.txt", "w");

    if (file == NULL) {
        fprintf(stderr, "Critical bug: Could not open file %s\n", "tasks.txt");
        return -1;
    }

    char *is_done_bool;
    for (int i = 0; i < count; i++) {
        if (tasks[i].isDone) {
            is_done_bool = "true";
        } else {
            is_done_bool = "false";
        }
        fprintf(file,
                "%d.\n"
                "Name: %s\n"
                "Priority: %d\n"
                "Done: %s\n",
                i + 1, tasks[i].name, tasks[i].priority, is_done_bool
        );
    }

    err_code = fclose(file);
    if (err_code != 0) {
        fprintf(stderr, "Could not close file %s\n", "tasks.txt");
        return -1;
    }

    return 0;
}


int read_tasks_from_file(const char *filename, struct Task **tasks, int *count) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        fprintf(stderr, "Error: Could not open %s\n", filename);
        return -1;
    }

    struct Task tmp;
    char done_str[8];

    while (fscanf(file,
                  "%*d.\nName: %[^\n]\nPriority: %d\nDone: %7s\n",
                  tmp.name, &tmp.priority, done_str) == 3) {

        struct Task *new_tasks = realloc(*tasks, sizeof(struct Task) * (*count + 1));
        if (!new_tasks) {
            fprintf(stderr, "Memory allocation error\n");
            free(*tasks);
            fclose(file);
            return -1;
        }

        *tasks = new_tasks;
        tmp.isDone = (strcmp(done_str, "true") == 0);
        (*tasks)[*count] = tmp;
        (*count)++;
                  }

    fclose(file);
    return 0;
}
