#include<iostream>

const int MAX = 10;
int quantum = 4;
struct process
{
    int id, Atime, Btime, Ttime, Wtime;
};

struct sequence
{
    int id;
    int time;
    int isLast;
    struct sequence *next;
};

struct sequence *head = NULL, *foot = NULL;

int nextprocess(struct process arr[], int n, int start)
{
    for (int i = (start == n - 1) ? 0 : start + 1; i < n; i++)
    {
        if (arr[i].Btime > 0)
        {
            return i;
        }
    }
    for (int i = 0; i < start; i++)
    {
        if (arr[i].Btime > 0)
        {
            return i;
        }
    }
    return -1;
}

void addSequence(int info, int duration, int flag)
{
    struct sequence *node = (struct sequence *)malloc(sizeof(struct sequence));
    node->id = info;
    node->time = duration;
    node->isLast = flag;
    node->next = NULL;
    if (head == NULL)
    {
        head = node;
        foot = node;
    }
    else
    {
        foot->next = node;
        foot = node;
    }
}

void printlist(struct sequence *n)
{
    while (n != NULL)
    {
        printf("\n%d ", n->id);
        printf("%d", n->time);
        n = n->next;
    }
}

void schedule(struct process arr[], int n, int origBurst[])
{
    int time = 0;
    int start = arr[0].Atime;
    int i = nextprocess(arr, n, -1);
    while (i != -1)
    {
        if (arr[i].Btime > quantum)
        {
            // printf("%d",arr[i].Btime);
            // printf("\nScheduling process p%d with burst time > quantum because burst=%d", arr[i], arr[i].Btime);
            start = start + quantum;
            addSequence(i, start, 0);
            arr[i].Btime -= quantum;
            i = nextprocess(arr, n, i);
        }
        else if (arr[i].Btime == quantum)
        {
            // printf("%d",arr[i].Btime);
            // printf("\nScheduling process p%d with burst time = quantum because burst=%d", arr[i], arr[i].Btime);
            start = start + quantum;
            addSequence(i, start, 1);
            arr[i].Ttime = start - arr[i].Atime;
            arr[i].Wtime = arr[i].Ttime - origBurst[i];
            arr[i].Btime = 0;
            i = nextprocess(arr, n, i);
        }
        else
        {
            // printf("%d",arr[i].Btime);
            // printf("\nScheduling process p%d with burst time < quantum because burst=%d", arr[i], arr[i].Btime);
            start = start + arr[i].Btime;
            addSequence(i, start, 1);
            arr[i].Ttime = start - arr[i].Atime;
            arr[i].Wtime = arr[i].Ttime - origBurst[i];
            arr[i].Btime = 0;
            i = nextprocess(arr, n, i);
        }
    }
}



int getInput(struct process arr[], int origBurst[])
{
    int n;
    printf("Hello world\n");
    printf("Enter number of processes: ");
    scanf("%d", &n);
    int start = 0;
    for (int i = 0; i < n; i++)
    {
        arr[i].id = i;
        // printf("Enter Arrival time for process P%d: ", i);
        // scanf("%d", &arr[i].Atime);
        arr[i].Atime = 0;
        printf("Enter Burst time for process P%d: ", i);
        scanf(" %d", &arr[i].Btime);
        origBurst[i] = arr[i].Btime;
    }
    printf("\n");
    return n;
}

void printGanttChart(struct process arr[], int n)
{
    printf("\n                        ##### RR #####\n\n");

    printf("\nTime Quantum is : 4 ms\n");

    struct sequence *var = head;
    int ctr = 0;
    while (var != NULL)
    {
        ctr++;
        // printf("\niteration %d",ctr);
        var = var->next;
    }
    printf("\nGantt Chart:\n");
    printf(".");
    for (int i = 0; i < ctr; i++)
    {
        printf("-----------");
    }
    printf("\n");

    var = head;
    while (var != NULL)
    {
        printf("|    P%d    ", var->id);
        var = var->next;
    }
    printf("|");
    printf("\n");
    printf(".");
    for (int i = 0; i < ctr; i++)
    {
        printf("-----------");
    }
    printf("\n");

    int start = arr[0].Btime;
    printf("%d", start);

    var = head;
    // int trial=0;
    while (var != NULL)
    {
        // trial++;
        // printf("\niteration %d\n",trial);
        // start = start + var->time;
        printf("      %5d", var->time);
        var = var->next;
    }
    printf("\n");
}

void printTable(struct process arr[], int n)
{
    int Tsum = 0, Wsum = 0,time=0;
    char per = '%';
    printf("\n--------------------------------------------------");
    printf("\n|  Time    |  PC   |  TAT=PC-AT    |  WT=TAT-PT  |");
    printf("\n--------------------------------------------------");
    printf("\n|     %d    |   -   |       -       |      -      |", 0);
    printf("\n--------------------------------------------------");
    struct sequence *var = head;
    while (var != NULL)
    {
        if (var->isLast == 1)
        {
            printf("\n| %5d    | %2c%d   |  %7d      |  %5d      |", var->time, 'P', var->id, arr[var->id].Ttime, arr[var->id].Wtime);
            printf("\n--------------------------------------------------");
            Tsum = Tsum + arr[var->id].Ttime;
            Wsum = Wsum + arr[var->id].Wtime;
            time= var->time;
        }
        var = var->next;

    }
    printf("\n");


    float avgT, avgW, throughput;
    avgT = (float)Tsum / n;
    avgW = (float)Wsum / n;
    // printf("hello again");
    throughput = (float)n / time;
    float utilisation = (float)((time + 0.0) / (float)time) * 100;
    printf("\n\nAverage Turnaround Time = ");
    printf("((");
    for(int i=0; i< n; i++)
    {
        if(i==n-1)
            printf("P%d",i);
        else
            printf("P%d + ",i);
    }
    printf(")/ Total processes)");
    printf(" = ((");
    for(int i=0; i< n; i++)
    {
        if(i==n-1)
            printf("%d",arr[i].Ttime);
        else
            printf("%d + ",arr[i].Ttime);
    }
    printf(")/ %d) = %.2f ms.",n, avgT);
    printf("\n\nAverage Waiting Time: = ");
    printf("((");
    for(int i=0; i< n; i++)
    {
        if(i==n-1)
            printf("P%d",i);
        else
            printf("P%d + ",i);
    }
    printf(")/ Total processes)");
    printf(" = ((");
    for(int i=0; i< n; i++)
    {
        if(i==n-1)
            printf("%d",arr[i].Wtime);
        else
            printf("%d + ",arr[i].Wtime);
    }
    printf(")/ %d) = %.2f ms.",n, avgW);
    printf("\n\nCPU Utilization = ((CPU Busy Time + CPU Idle Time)/CPU Busy Time) = (%d + %d ) / %d ) = %.2f %c.", time, 0, time, utilisation, per);
    printf("\n\nThroughput = (Number of processes/Total Burst Time) = %d / %d  = %.2f ms.", n, time, throughput);
    printf("\n\n");

    /*float avgT, avgW, throughput;
    avgT = (float)Tsum / n;
    avgW = (float)Wsum / n;
    // printf("hello again");
    throughput = (float)n / time;
    float utilisation = (float)((time + 0.0) / (float)time) * 100;




    printf("\n\nAverage Turnaround Time: %.2f ms.", avgT);
    printf("\n\nAverage Waiting Time: %.2f ms.", avgW);
    printf("\n\nCPU Utilization: \n\tFormula: ((CPU Busy Time + CPU Idle Time)/CPU Busy Time)\n\tEvaluation: (%d + %d ) / %d ) = %.2f %c.", time, 0, time, utilisation, per);
    printf("\n\nThroughput: \n\tFormula: (Number of processes/Total Time)\n\tEvaluation: %d / %d  = %.2f ms.", n, time, throughput);
    printf("\n\n");*/
}

int main()
{
    struct process arr[MAX];
    int origBurst[MAX];
    int n = getInput(arr, origBurst);

    schedule(arr, n, origBurst);
    printGanttChart(arr, n);
    printTable(arr, n);
    return 0;
}

/*
let us consider we have 5 processes and total burst time is 25,
so one edge edge case is that one process has 25 burst and rest 4
processes have 0 burst times.

so now for process with 25 burst time and at quantum q, we have to go through
(int)25/q + 1 cycles. we take + 1 extra because of the case with decimal parts. so one cycle extra.
so in this case, our sequence string hase (int)totalTime/quantum + 1 as length.
but, now take one step back, consider one process has 21 burst time and rest 4 processes have 1 burst time,
in this case we will have (int)21/q + 1 for one process and extra 4 cycles for the rest of 4 processes.
Still, deciding the size of string is such a mess, "Can use a linked list".
but still its just fucking boring. no other option. linked list solves this mess. also i can delete the list later
no need to create a big list for process, can make a int list instead.
just took a string because it was easy to store my data. but nows not the case.
plus i dont think i have quite a grip with this language.
*/