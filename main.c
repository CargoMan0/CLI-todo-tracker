//
// Created by Wilhelm Reich on 17.10.2025.
//

#include <stdio.h>
#include <stdlib.h>
#include "tasks.h"
#include "readers.h"

int main(void) {
    struct Task *tasks = malloc(sizeof(struct Task));
    int choice, task_id, count = 0, err_code;

    for (;;) {
        printf("Enter your choice: \n"
            "1. Add Task\n"
            "2. Delete Task\n"
            "3. Get your Tasks\n"
            "4. Mark task as done\n"
        );
        err_code = read_number(&choice);
        if (err_code != 0) {
            return err_code;
        }


        switch (choice) {
            case 1:
                add_task(&tasks, &count);
                break;
            case 2:
                printf("Enter Task ID: \n");
                read_number(&task_id);

                delete_task(&tasks, &count, task_id);
                break;
            case 3:
                get_tasks(tasks, count);
                break;
            case 4:
                printf("Enter Task ID: \n");
                read_number(&task_id);

                mark_task_done(&tasks, count, task_id);
                break;
            case 5:
                printf("Saving your tasks to file...\n");
                save_tasks_to_file(tasks, count);
                break;
            case 6:
                printf("Loading tasks from file... \n");

                read_tasks_from_file("tasks.txt", &tasks, &count);
                break;
            default:
                printf("Wrong input. Please try again.\n");
                abort();
        }
    }
}
