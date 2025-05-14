#include <stdio.h>
#include <stdbool.h>

int main() {
    int alloc[10][10], max[10][10], avail[10], total[10];
    int need[10][10];
    bool finish[10] = {false};
    int i, j, n, m;
    int count = 0;

    printf("Enter the number of processes and resources: ");
    scanf("%d %d", &n, &m);

    printf("Enter the claim matrix (Max matrix):\n");
    for(i = 0; i < n; i++) {
        for(j = 0; j < m; j++) {
            scanf("%d", &max[i][j]);
        }
    }

    printf("Enter the allocation matrix:\n");
    for(i = 0; i < n; i++) {
        for(j = 0; j < m; j++) {
            scanf("%d", &alloc[i][j]);
        }
    }

    printf("Enter the total resource vector:\n");
    for(i = 0; i < m; i++) {
        scanf("%d", &total[i]);
    }

    for(i = 0; i < m; i++) {
        avail[i] = total[i];
        for(j = 0; j < n; j++) {
            avail[i] -= alloc[j][i];
        }
    }

    for(i = 0; i < n; i++) {
        for(j = 0; j < m; j++) {
            need[i][j] = max[i][j] - alloc[i][j];
        }
    }

    while(1) {
        bool progress = false;

        for(i = 0; i < n; i++) {
            if(!finish[i]) {
                bool canExecute = true;
                for(j = 0; j < m; j++) {
                    if(need[i][j] > avail[j]) {
                        canExecute = false;
                        break;
                    }
                }

                if(canExecute) {
                    printf("Process %d can execute.\n", i);
                    for(j = 0; j < m; j++) {
                        avail[j] += alloc[i][j];
                    }
                    finish[i] = true;
                    progress = true;
                    count++;
                }
            }
        }

        if(!progress) {
            break;
        }

        if(count == n) {
            printf("\nSystem is in a safe state.\n");
            return 0;
        }
    }

    printf("\nSystem is in an unsafe state.\n");
    return 0;
}






















