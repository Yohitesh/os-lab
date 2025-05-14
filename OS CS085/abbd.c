#include<stdio.h>
#include <stdlib.h>
#define MAX_TASKS 10

typedef struct {
    int task_id;
    int execution_time;
    int period;
    int arrival_time;
    int remaining_time;
    int next_arrival_time;
} Task;

void sortTasksByPeriod(Task *tasks, int n) {
    Task temp;
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (tasks[i].period > tasks[j].period) {
                temp = tasks[i];
                tasks[i] = tasks[j];
                tasks[j] = temp;
            }
        }
    }
}

void checkTaskArrival(Task *tasks, int n, int current_time) {
    for (int i = 0; i < n; i++) {
        if (tasks[i].next_arrival_time == current_time) {
            printf("Task %d has arrived at time %d\n", tasks[i].task_id, current_time);
        }
    }
}

Task* getNextTask(Task *tasks, int n, int current_time) {
    Task *next_task = NULL;
    for (int i = 0; i < n; i++) {
        if (tasks[i].next_arrival_time <= current_time && tasks[i].remaining_time > 0) {
            if (next_task == NULL || tasks[i].period < next_task->period) {
                next_task = &tasks[i];
            }
        }
    }
    return next_task;
}


void scheduler(Task *tasks, int n, int total_time) {
    int current_time = 0;
    while (current_time < total_time) {

        checkTaskArrival(tasks, n, current_time);


        Task *next_task = getNextTask(tasks, n, current_time);

        if (next_task != NULL) {

            printf("Executing Task %d at time %d\n", next_task->task_id, current_time);
            next_task->remaining_time--;


            if (next_task->remaining_time == 0) {
                next_task->next_arrival_time = current_time + next_task->period;
                next_task->remaining_time = next_task->execution_time;
                printf("Task %d completed and rescheduled at time %d\n", next_task->task_id, current_time);
            }
        } else {
            printf("Idle at time %d\n", current_time);
        }

        current_time++;
    }
}


void inputTasks(Task *tasks, int n) {
    for (int i = 0; i < n; i++) {
        printf("Enter details for Task %d:\n", i + 1);
        printf("Execution time: ");
        scanf("%d", &tasks[i].execution_time);
        printf("Period: ");
        scanf("%d", &tasks[i].period);
        printf("Arrival time: ");
        scanf("%d", &tasks[i].arrival_time);


        tasks[i].remaining_time = tasks[i].execution_time;
        tasks[i].next_arrival_time = tasks[i].arrival_time;
        tasks[i].task_id = i + 1;
    }
}
int main() {
    int n;
    printf("Enter number of tasks: ");
    scanf("%d", &n);
    Task tasks[MAX_TASKS];
    inputTasks(tasks, n);
    sortTasksByPeriod(tasks, n);
    int total_time = 20;
    scheduler(tasks, n, total_time);

    return 0;
}

