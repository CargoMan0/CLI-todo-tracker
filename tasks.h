//
// Created by Wilhelm Reich on 17.10.2025.
//

#ifndef CLI_TODO_TRACKER_TASKS_H
#define CLI_TODO_TRACKER_TASKS_H

// Task structure.
struct Task {
    char name[50];
    int priority;
    int isDone;
};

// Task functions.
int add_task(struct Task **tasks, int *count);

int get_tasks(struct Task *tasks, int count);

int delete_task(struct Task **tasks, int *count, int id);

int mark_task_done(struct Task **tasks, int count, int id);

// Files interaction.
int save_tasks_to_file(struct Task *tasks, int count);

int read_tasks_from_file(const char *filename, struct Task **tasks, int *count);

#endif //CLI_TODO_TRACKER_TASKS_H
