
#include <iostream>
const int max = 10;
int ci=0,cut;
struct pro
{
        int id, Arri, Burst, Tur, Wait;
};

struct profi
{
        int id, Arri, Burst, Tur, Wait;
};

void set(struct pro s[], int n)
{
        struct pro temp;
        int a, b, m;
        for (a = 0; a < n; a++)
        {
                m = a;
                for (b = a + 1; b < n; b++)
                {
                        if (s[b].Burst < s[m].Burst)
                        {
                                m = b;
                        }
                }
                temp = s[a];
                s[a] = s[m];
                s[m] = temp;
        }
}

void cal(struct pro s[], int n)
{
        int start = 0;
        for (int i = 0; i < n; i++)
        {
                start = start + s[i].Burst;
                s[i].Tur = start;
                s[i].Wait = s[i].Tur - s[i].Burst;
        }
}

void output(struct pro s[], int n)
{
	int tbt=0;
	
        int Tsum = 0, Wsum = 0, start = 0, bur = 0;
        for (int i = 0; i < n; i++)
        {
                start = start + s[i].Burst;
                Tsum = Tsum + s[i].Tur;
                Wsum = Wsum + s[i].Wait;
                bur = bur + s[i].Burst;
        }
        for(int i=0;i<n;i++)
        {
        	tbt=tbt+s[i].Burst;
		}
        float avgT, avgW, throughput;
        avgT = (float)Tsum / n;
        avgW = (float)Wsum / n;
        throughput = (float)n / start;
        printf("\nAverage Turnaround Time = Total Turnaround time / No. of processes = (");
         for (int i = 0; i < n; i++)
    {
        if (i == n - 1)
            printf("P%d", i);
        else
            printf("P%d + ", i);
    }
    printf(")/ Total processes)");
    printf(" = (");
       for (int i = 0; i < n; i++)
        {
                printf("%d", s[i].Tur);
                if (i < n - 1)
                {
                        printf("+");
                }
        }
        printf(") / %d ", n);
        printf(" = %d / %d = %.2f ms.\n",Tsum,n ,avgT);

        printf("Average Waiting Time = Total Waiting time / No. of processes = (");
          for (int i = 0; i < n; i++)
    {
        if (i == n - 1)
            printf("P%d", i);
        else
            printf("P%d + ", i);
    }
    printf(")/ Total processes)");
    printf(" = (");
        for (int i = 0; i < n; i++)
        {
                printf("%d", s[i].Wait);
                if (i < n - 1)
                {
                        printf("+");
                }
        }
        printf(") / %d ", n);
        printf(" =  %d / %d = %.2f ms.",Wsum,n, avgW);
        cut=((tbt+ci)/tbt)*100;
	
      printf("\nThroughput = no of process / total brust time = %d / %d = %.2f 1/ms",n,tbt,throughput);
        printf("\nCPU Utililazation=((CPU busy time + CPU idel time)/CPU busy time)*100= ((%d+%d)/%d)*100 = %3.2d percentage",tbt,ci,tbt,cut);
     
        printf("\n\n");
}

int input(struct pro s[])
{
        int n;
        printf("Enter number of processes: ");
        scanf("%d", &n);
        int start = 0;
        for (int i = 0; i < n; i++)
        {
                s[i].id = i;
                printf("Enter Arrival time for process P%d: ", i);
                scanf("%d", &s[i].Arri);
        }
        for (int i = 0; i < n; i++)
        {
                s[i].id = i;
                printf("Enter Burst time for process P%d: ", i);
                scanf(" %d", &s[i].Burst);
        }
        printf("\n");
        return n;
}

void Gantt(struct pro s[], int n)
{
        
          printf("\n                        ##### SRTF #####\n");
		printf("\nGantt Chart:\n");
        int start = 1;
        for (int i = 0; i <= n; i++)
        {
                printf("--------");
        }
        printf("\n");
        printf("|  P0\t");
        for (int i = 0; i < n; i++)
        {
              //  printf("%d",s[i].id);
                printf("|  P%d\t", s[i].id);
        }
        printf("|");
        printf("\n");
        for (int i = 0; i <= n; i++)
        {
                printf("--------");
        }
        printf("\n");
        printf("0    \t");
        for (int i = 0; i < n; i++)
        {
                if (s[i].id == 0)
                {
                        s[i].Burst = s[i].Burst - 1;
                }
                if (s[i].Burst == 0)
                {
                        continue;
                }
                else
                {
                        printf("%d    \t", start);
                        start = start + s[i].Burst;
                }
        }
        printf("%d", start);
        printf("\n");
        for (int i = 0; i < n; i++)
        {
                if (s[i].id == 0)
                {
                        s[i].Burst = s[i].Burst + 1;
                }
        }
}

void table(struct pro s[], int n)
{
	printf("\n\nSRTF Process Schedulling\n");
        int j;
        for (j = 0; j < 41; j++)
                printf("-");
        printf("\n|TIME|Process Completed|TA-Time|W-Time  |\n");
        printf("|(ms)|       \t       |(PC-AT)|(TAT-BT)|\n");
        for (j = 0; j < 41; j++)
                printf("-");
        int start = 0;
        printf("\n|  0 |\t    -- \t       |   -   |  -     |");
        for (int i = 0; i < n; i++)
        {
                start = start + s[i].Burst;
                printf("\n|%3d |\t    P%d \t       |%4d   |%3d     |", start, s[i].id, s[i].Tur, s[i].Wait);
        }
        printf("\n");
        for (j = 0; j < 41; j++)
                printf("-");
        printf("\n");
}

int main()

{
        struct pro s[max];
        struct profi q[max];
        int n = input(s);
        set(s, n);
        cal(s, n);
        Gantt(s, n);
        table(s, n);
        output(s, n);
}
