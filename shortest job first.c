// SJF Scheduling 

#include <stdio.h>

struct process
{
    int pid;
    int bt;
    int wt;
    int tt;
} p[10], temp;

main()
{
    int i, j, k, n, ttat, twt, tbt,ci=0;
    float awt, atat, tp, cut;

    printf("Enter the number of process : ");
    scanf("%d", &n);
    for (i = 0; i < n; i++)
    {
        printf("Enter the Burst time for process P%d (in ms) : ", (i+1));
        scanf("%d", &p[i].bt);
        p[i].pid = i+1;
    }

    for (i = 0; i < n - 1; i++)
    {
        for (j = i + 1; j < n; j++)
        {
            if ((p[i].bt > p[j].bt) ||
                (p[i].bt == p[j].bt && p[i].pid > p[j].pid))
            {
                temp = p[i];
                p[i] = p[j];
                p[j] = temp;
            }
        }
    }
    p[0].wt = 0;
    for (i = 0; i < n; i++)
    {
        p[i + 1].wt = p[i].wt + p[i].bt;
        p[i].tt = p[i].wt + p[i].bt;
    }
    ttat = twt = 0;
    for (i = 0; i < n; i++)
    {
        ttat += p[i].tt;
        twt += p[i].wt;
        tbt += p[i].bt;
    }
    awt = (float)twt / n;
    atat = (float)ttat / n;
    tp = n / (float)tbt;
   cut=((tbt+ci)/tbt)*100;
    printf("\n\nGANTT Chart\n");
    printf("-");
    for (i = 0; i < (p[n - 1].tt + 2 * n); i++)
        printf("-");
    printf("\n|");
    for (i = 0; i < n; i++)
    {
        k = p[i].bt / 2;
        for (j = 0; j < k; j++)
            printf(" ");
        printf("P%d", p[i].pid);
        for (j = k + 1; j < p[i].bt; j++)
            printf(" ");
        printf("|");
    }
    printf("\n-");
    for (i = 0; i < (p[n - 1].tt + 2 * n); i++)
        printf("-");
    printf("\n0");
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < p[i].bt; j++)
            printf(" ");
        printf("%2d", p[i].tt);
    }

    printf("\n\nSJF Process Scheduling\n");
    for (i = 0; i < 39; i++)
        printf("-");
    printf("\n|Time|Process| B-Time| T-Time| W-Time |");
    printf("\n|    |       |       | =PC-AT| =TAT-BT|\n");
    for (i = 0; i < 39; i++)
        printf("-");
        
    printf("\n| 0  |   -   |   -   |   -   |    -   |");
	for(i=0;i<n-1;i++)
        printf("\n|%2d  |   P%d  |  %2d   |  %2d   |   %2d   |", p[i].tt,p[i].pid, p[i].bt, p[i].tt, p[i].wt);
		
		
	if(n=10){
		printf("\n|%2d  |  P%2d  |  %2d   |  %2d   |   %2d   |", p[i].tt,p[i].pid, p[i].bt, p[i].tt, p[i].wt);
	}
	printf("\n");
    for (i = 0; i < 39; i++)
        printf("-");

        printf("\n\nAverage waiting time: (");
          for (int i = 0; i < n; i++)
    {
        if (i == n - 1)
            printf("P%d", i);
        else
            printf("P%d + ", i);
    }
    printf(")/ Total processes)");
    printf(" = (");
    for(i=0;i<n;i++)
    {
       if(i==n-1)
        	printf("%d",p[i].wt);
       else
            printf("%d+",p[i].wt);
    }
    printf(") / %d = %.2f ms",n,awt);
    printf("\nAverage turnaround time: (");
     for (int i = 0; i < n; i++)
    {
        if (i == n - 1)
            printf("P%d", i);
        else
            printf("P%d + ", i);
    }
    printf(")/ Total processes)");
    printf(" = (");
    for(i=0;i<n;i++)
    {
       if(i==n-1)
        printf("%d",p[i].tt);
       else
               printf("%d+",p[i].tt);
    }
    printf(") / %d = %.2f ms",n,atat);
    printf("\nThroughput = no of procees / total burst time  = %d/%d = %.2f 1/ms",n,tbt,tp);
    printf("\nCPU Utililazation=((CPU busy time + CPU idel time)/CPU busy time)*100= ((%d+%d)/%d)*100 = %.2f percentage",tbt,ci,tbt,cut);
}
