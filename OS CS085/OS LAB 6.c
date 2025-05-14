#include <stdio.h>
#define max 25

void firstFit(int b[], int nb, int f[], int nf);
void worstFit(int b[], int nb, int f[], int nf);
void bestFit(int b[], int nb, int f[], int nf);

int main() {
    int b[max], f[max], nb, nf;

    printf("Memory Management Schemes\n");
    printf("\nEnter the number of blocks: ");
    scanf("%d", &nb);
    printf("Enter the number of files: ");
    scanf("%d", &nf);

    printf("\nEnter the size of the blocks:\n");
    for (int i = 1; i <= nb; i++) {
        printf("Block %d: ", i);
        scanf("%d", &b[i]);
    }

    printf("\nEnter the size of the files:\n");
    for (int i = 1; i <= nf; i++) {
        printf("File %d: ", i);
        scanf("%d", &f[i]);
    }

    printf("\nMemory Management Scheme - First Fit");
    firstFit(b, nb, f, nf);

    printf("\n\nMemory Management Scheme - Worst Fit");
    worstFit(b, nb, f, nf);

    printf("\n\nMemory Management Scheme - Best Fit");
    bestFit(b, nb, f, nf);

    return 0;
}

void firstFit(int b[], int nb, int f[], int nf) {
    int bf[max] = {0}, ff[max] = {0}, frag[max];
    int i, j;

    for (i = 1; i <= nf; i++) {
        for (j = 1; j <= nb; j++) {
            if (bf[j] != 1 && b[j] >= f[i]) {
                ff[i] = j;
                bf[j] = 1;
                frag[i] = b[j] - f[i];
                break;
            }
        }
    }

    printf("\nFile_no:\tFile_size:\tBlock_no:\tBlock_size:\tFragment");
    for (i = 1; i <= nf; i++) {
        if (ff[i] != 0)
            printf("\n%d\t\t%d\t\t%d\t\t%d\t\t%d", i, f[i], ff[i], b[ff[i]], frag[i]);
        else
            printf("\n%d\t\t%d\t\tNot Allocated", i, f[i]);
    }
}

void worstFit(int b[], int nb, int f[], int nf) {
    int bf[max] = {0}, ff[max] = {0}, frag[max];
    int i, j, temp, highest;

    for (i = 1; i <= nf; i++) {
        highest = -1;
        for (j = 1; j <= nb; j++) {
            if (bf[j] != 1) {
                temp = b[j] - f[i];
                if (temp >= 0 && (highest == -1 || temp > frag[i])) {
                    ff[i] = j;
                    frag[i] = temp;
                    highest = temp;
                }
            }
        }
        if (ff[i] != 0)
            bf[ff[i]] = 1;
    }

    printf("\nFile_no:\tFile_size:\tBlock_no:\tBlock_size:\tFragment");
    for (i = 1; i <= nf; i++) {
        if (ff[i] != 0)
            printf("\n%d\t\t%d\t\t%d\t\t%d\t\t%d", i, f[i], ff[i], b[ff[i]], frag[i]);
        else
            printf("\n%d\t\t%d\t\tNot Allocated", i, f[i]);
    }
}

void bestFit(int b[], int nb, int f[], int nf) {
    int bf[max] = {0}, ff[max] = {0}, frag[max];
    int i, j, temp, lowest;

    for (i = 1; i <= nf; i++) {
        lowest = 10000;
        for (j = 1; j <= nb; j++) {
            if (bf[j] != 1) {
                temp = b[j] - f[i];
                if (temp >= 0 && temp < lowest) {
                    ff[i] = j;
                    frag[i] = temp;
                    lowest = temp;
                }
            }
        }
        if (ff[i] != 0)
            bf[ff[i]] = 1;
    }

    printf("\nFile_no:\tFile_size:\tBlock_no:\tBlock_size:\tFragment");
    for (i = 1; i <= nf; i++) {
        if (ff[i] != 0)
            printf("\n%d\t\t%d\t\t%d\t\t%d\t\t%d", i, f[i], ff[i], b[ff[i]], frag[i]);
        else
            printf("\n%d\t\t%d\t\tNot Allocated", i, f[i]);
    }
}
