#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_PROCESS 10

int num_of_process;
int execution_time[MAX_PROCESS], deadline[MAX_PROCESS], remain_time[MAX_PROCESS], remain_deadline[MAX_PROCESS];

void get_process_info() {
    printf("Enter total number of processes (maximum %d): ", MAX_PROCESS);
    scanf("%d", &num_of_process);

    if (num_of_process < 1) {
        exit(0);
    }

    for (int i = 0; i < num_of_process; i++) {
        printf("\nProcess %d:\n", i + 1);
        printf("==> Execution time: ");
        scanf("%d", &execution_time[i]);
        remain_time[i] = execution_time[i];

        printf("==> Deadline: ");
        scanf("%d", &deadline[i]);
        remain_deadline[i] = deadline[i];
    }
}

void print_schedule(int process_list[], int cycles) {
    printf("\nScheduling:\n\n");
    printf("Time: ");
    for (int i = 0; i < cycles; i++) {
        printf("| %02d ", i);
    }
    printf("|\n");

    for (int i = 0; i < num_of_process; i++) {
        printf("P[%d]: ", i + 1);
        for (int j = 0; j < cycles; j++) {
            if (process_list[j] == i + 1)
                printf("|####");
            else
                printf("|    ");
        }
        printf("|\n");
    }
}

void earliest_deadline_first(int time) {
    int process_list[100] = {0};
    int current_process = -1, min_deadline;
    bool is_ready[MAX_PROCESS] = {true};

    for (int t = 0; t < time; t++) {
        min_deadline = 9999;
        for (int i = 0; i < num_of_process; i++) {
            if (remain_time[i] > 0 && deadline[i] < min_deadline) {
                min_deadline = deadline[i];
                current_process = i;
            }
        }

        if (current_process != -1) {
            process_list[t] = current_process + 1;
            remain_time[current_process]--;
        } else {
            process_list[t] = 0;
        }

        for (int i = 0; i < num_of_process; i++) {
            if (remain_time[i] == 0 && !is_ready[i]) {
                deadline[i] = remain_deadline[i];
                is_ready[i] = true;
            }
        }
    }

    print_schedule(process_list, time);
}

int main() {
    int observation_time;

    get_process_info();
    observation_time = deadline[0];
    for (int i = 1; i < num_of_process; i++) {
        if (deadline[i] > observation_time) {
            observation_time = deadline[i];
        }
    }

    earliest_deadline_first(observation_time);
    return 0;
}

