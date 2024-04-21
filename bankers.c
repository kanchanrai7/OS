#include<stdio.h>
#include<stdlib.h>
#include<conio.h>

int max[100][100];
int alloc[100][100];
int need[100][100];
int avail[100];
int n, r;

void input();
void show();
void cal();
void request();

void input() {
    int i, j;
    printf("Enter the number of processes: ");
    scanf("%d", &n);
    printf("Enter the number of resources: ");
    scanf("%d", &r);
    printf("Enter the Max Matrix (in order): \n");
    for (i = 0; i < n; i++) {
        for (j = 0; j < r; j++) {
            scanf("%d", &max[i][j]);
        }
    }
    printf("Enter the Allocation Matrix (in order): \n");
    for (i = 0; i < n; i++) {
        for (j = 0; j < r; j++) {
            scanf("%d", &alloc[i][j]);
        }
    }
    printf("Enter the number of available resource instances (in order): \n");
    for (j = 0; j < r; j++) {
        scanf("%d", &avail[j]);
    }
}

void show() {
    int i, j;
    printf("Process\t\tAllocation\tNeed\t\tMax\t\tAvailable");
    for (i = 0; i < n; i++) {
        printf("\nP%d\t\t ", i + 1);
        for (j = 0; j < r; j++) {
            printf("%d ", alloc[i][j]);
        }
        printf("\t\t");
        for (j = 0; j < r; j++) {
            printf("%d ", max[i][j]);
        }
        printf("\t\t");
        for (j = 0; j < r; j++) {
            printf("%d ", need[i][j]);
        }
        printf("\t\t");
        if (i == 0) {
            for (j = 0; j < r; j++)
                printf("%d ", avail[j]);
        }
    }
}

void cal() {
    int finish[100], flag = 1, k, c1 = 0;
    int i, j;
    for (i = 0; i < n; i++) {
        finish[i] = 0;
    }
    for (i = 0; i < n; i++) {
        for (j = 0; j < r; j++) {
            need[i][j] = max[i][j] - alloc[i][j];
        }
    }
    printf("\n");
    while (flag) {
        flag = 0;
        for (i = 0; i < n; i++) {
            int c = 0;
            for (j = 0; j < r; j++) {
                if ((finish[i] == 0) && (need[i][j] <= avail[j])) {
                    c++;
                    if (c == r) {
                        for (k = 0; k < r; k++) {
                            avail[k] += alloc[i][j];
                            finish[i] = 1;
                            flag = 1;
                        }
                        printf("P%d->", i);
                        if (finish[i] == 1) {
                            i = n;
                        }
                    }
                }
            }
        }
    }
    for (i = 0; i < n; i++) {
        if (finish[i] == 1) {
            c1++;
        } else {
            printf("P%d->", i);
        }
    }
    if (c1 == n) {
        printf("\nThe system is in safe state.\n");
    } else {
        printf("\nProcess are in deadlock.\n");
        printf("\nSystem is in unsafe state.\n");
    }
}

void request() {
    int c, pid, request[100][100], i;
    printf("\nDo you want make an additional request for any of the process? (1 = Yes | 0 = No): ");
    scanf("%d", &c);
    if (c == 1) {
        printf("Enter process number : ");
        scanf("%d", &pid);
        printf("Enter additional request : \n");
        for (i = 0; i < r; i++) {
            printf("Request for resource %d : ", i + 1);
            scanf("%d", &request[0][i]);
        }
        for (i = 0; i < r; i++) {
            if (request[0][i] > need[pid][i]) {
                printf("\n ******Error encountered******\n");
                exit(0);
            }
        }
        for (i = 0; i < r; i++) {
            avail[i] -= request[0][i];
            alloc[pid][i] += request[0][i];
            need[pid][i] -= request[0][i];
        }
        cal();
    } else {
        exit(0);
    }
}

int main() {
    int i, j;
    printf("********** Implementing Banker's Algorithm ************\n");
    input();
    cal();
    show();
    request();
    return 0;
}
