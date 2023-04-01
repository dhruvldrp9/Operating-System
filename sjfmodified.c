#include <stdio.h>
const int MAX = 10;
struct process
{
        int id, Atime, Btime, Ttime, Wtime;
};

void sort(struct process arr[], int n)
{
        struct process tmp;
        int i, j, min;
        for (i = 0; i < n; i++)
        {
                min = i;
                for (j = i + 1; j < n; j++)
                {
                        if (arr[j].Btime < arr[min].Btime)
                        {
                                min = j;
                        }
                }
                tmp = arr[i];
                arr[i] = arr[min];
                arr[min] = tmp;
        }
}

void calculate(struct process arr[], int n)
{
        int start = arr[0].Atime;
        for (int i = 0; i < n; i++)
        {
                start = start + arr[i].Btime;
                arr[i].Ttime = start - arr[i].Atime;
                arr[i].Wtime = arr[i].Ttime - arr[i].Btime;
        }
}

void printStats(struct process arr[], int n)
{
        char per='%';
        int Tsum = 0, Wsum = 0, start = 0;
        for (int i = 0; i < n; i++)
        {
                start = start + arr[i].Btime;
                Tsum = Tsum + arr[i].Ttime;
                Wsum = Wsum + arr[i].Wtime;
        }
        float avgT, avgW, throughput;
        avgT = (float)Tsum / n;
        avgW = (float)Wsum / n;
        throughput = (float)n / start;
        float utilisation = (float)((start + 0.0)/(float)start)*100;
        printf("\n\nAverage Turnaround Time: %.2f ms.", avgT);
        printf("\n\nAverage Waiting Time: %.2f ms.", avgW);
        printf("\n\nCPU Utilization: \n\tFormula: ((CPU Busy Time + CPU Idle Time)/CPU Busy Time)\n\tEvaluation: (%d + %d ) / %d ) = %.2f %c.",start, 0,start, utilisation,per);
        printf("\n\nThroughput: \n\tFormula: (Number of processes/Total Time)\n\tEvaluation: %d / %d  = %.2f ms.",n,start, throughput);
        printf("\n\n");
}

int getInput(struct process arr[])
{
        int n;
        printf("Hello world\n");
        printf("Enter number of processes: ");
        scanf("%d", &n);
        int start = 0;
        for (int i = 0; i < n; i++)
        {
                arr[i].id = i;
                //printf("Enter Arrival time for process P%d: ",i);
                arr[i].Atime = 0;
                printf("Enter Burst time for process P%d: ", i);
                scanf(" %d", &arr[i].Btime);
        }
        printf("\n");
        return n;
}

void printGanttChart(struct process arr[], int n)
{
        printf("\nGantt Chart:\n");
        printf(".");
        for (int i = 0; i < n; i++)
        {
                printf("...........");
        }
        printf("\n");
        for (int i = 0; i < n; i++)
        {
                printf("|    P%d    ", arr[i].id);
        }
        printf("|");
        printf("\n");
        printf(".");
        for (int i = 0; i < n; i++)
        {
                printf("...........");
        }
        printf("\n");
        int start = arr[0].Atime;
        for (int i = 0; i < n; i++)
        {
                printf("%-11d", start);
                start = start + arr[i].Btime;
        }
        printf("%d", start);
        printf("\n");
}

void printTable(struct process arr[], int n)
{
        printf("\n|----------|-------|---------------|-------------|");
        printf("\n|  Time    |  PC   |  TAT=PC-AT    |  WT=TAT-PT  |");
        printf("\n|----------|-------|---------------|-------------|");
        int start = arr[0].Atime;
        printf("\n|     %d    |   -   |       -       |      -      |", start);
        for (int i = 0; i < n; i++)
        {
                start = start + arr[i].Btime;
                printf("\n| %5d    | %2c%d   |  %7d      |  %5d      |", start,'P', arr[i].id, arr[i].Ttime, arr[i].Wtime);
        }
        printf("\n|----------|-------|---------------|-------------|");
        printf("\n");
}

void main()
{
        struct process arr[MAX];
        int n = getInput(arr);
        sort(arr, n);
        calculate(arr, n);
        printGanttChart(arr, n);
        printTable(arr,n);
        printStats(arr, n);
}
