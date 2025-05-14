#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>

#define MAX_PROCESS 10

typedef struct {
    int id;
    int burst_time;
    float priority;
} Task;

int num_of_process;
int execution_time[MAX_PROCESS], period[MAX_PROCESS],
    remain_time[MAX_PROCESS], deadline[MAX_PROCESS],
    remain_deadline[MAX_PROCESS];

void get_process_info(int selected_algo) {
    printf("Enter total number of processes (maximum %d): ", MAX_PROCESS);
    scanf("%d", &num_of_process);

    if (num_of_process < 1) {
        printf("Invalid number of processes. Exiting...\n");
        exit(0);
    }

    for (int i = 0; i < num_of_process; i++) {
        printf("\nProcess %d:\n", i + 1);
        printf("==> Execution time: ");
        scanf("%d", &execution_time[i]);
        remain_time[i] = execution_time[i];

        if (selected_algo == 2) {
            printf("==> Deadline: ");
            scanf("%d", &deadline[i]);
        } else {
            printf("==> Period: ");
            scanf("%d", &period[i]);
        }
    }
}

int max(int a, int b, int c) {
    int max_value = a;
    if (b > max_value) max_value = b;
    if (c > max_value) max_value = c;
    return max_value;
}

int get_observation_time(int selected_algo) {
    if (selected_algo == 1) {
        return max(period[0], period[1], period[2]);
    } else if (selected_algo == 2) {
        return max(deadline[0], deadline[1], deadline[2]);
    }
    return 0;
}

void print_schedule(int process_list[], int cycles) {
    printf("\nScheduling:\n\n");
    printf("Time: ");
    for (int i = 0; i < cycles; i++) {
        if (i < 10) {
            printf("| 0%d ", i);
        } else {
            printf("| %d ", i);
        }
    }
    printf("|\n");

    for (int i = 0; i < num_of_process; i++) {
        printf("P[%d]: ", i + 1);
        for (int j = 0; j < cycles; j++) {
            if (process_list[j] == i + 1) {
                printf("|####");
            } else {
                printf("|    ");
            }
        }
        printf("|\n");
    }
}

void rate_monotonic(int time) {
    int process_list[100] = {0}, next_process = 0;
    float utilization = 0;
    for (int i = 0; i < num_of_process; i++) {
        utilization += (1.0 * execution_time[i]) / period[i];
    }

    int n = num_of_process;
    float m = n * (pow(2, 1.0 / n) - 1);
    if (utilization > m) {
        printf("\nGiven problem is not schedulable under Rate Monotonic scheduling algorithm.\n");
        return;
    }

    for (int i = 0; i < time; i++) {
        int min = 1000;
        for (int j = 0; j < num_of_process; j++) {
            if (remain_time[j] > 0) {
                if (min > period[j]) {
                    min = period[j];
                    next_process = j;
                }
            }
        }

        if (remain_time[next_process] > 0) {
            process_list[i] = next_process + 1;
            remain_time[next_process] -= 1;
        }

        for (int k = 0; k < num_of_process; k++) {
            if ((i + 1) % period[k] == 0) {
                remain_time[k] = execution_time[k];
            }
        }
    }
    print_schedule(process_list, time);
}

int main() {
    int option;
    int observation_time;
    while (1) {
        printf("\n1. Rate Monotonic\n2. Exit\n\nEnter your choice: ");
        scanf("%d", &option);
        switch (option) {
            case 1:
                get_process_info(option);
                observation_time = get_observation_time(option);
                rate_monotonic(observation_time);
                break;
            case 2:
                printf("Exiting program.\n");
                exit(0);
                break;
            default:
                printf("\nInvalid option. Please try again.\n");
        }
    }
    return 0;
}
