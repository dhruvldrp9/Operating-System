#include<iostream>

const int max = 10;

struct pro
{
    int id, Arri, Burst, Tur, Wait;
};

void set(struct pro s[],int n)
{
    struct pro temp;
    int a,b,m;
    for (a=0;a<n;a++)
    {
        m=a;
        for (b=a+1;b<n;b++)
        {
            if (s[b].Burst < s[m].Burst)
            {
                m=b;
            }
        }
        temp=s[a];
        s[a]=s[m];
        s[m]=temp;
    }
}

void cal(struct pro s[],int n)
{
    int start = 0;
    for ( int i=0;i<n;i++)
    {
        start = start +s[i].Burst;
        s[i].Tur = start;
        s[i].Wait = s[i].Tur - s[i].Burst;
    }
}


void output(struct pro s[], int n)
{
        int Tsum = 0, Wsum = 0, start = 0, bur = 0;
        for (int i = 0; i < n; i++)
        {
                start = start + s[i].Burst;
                Tsum = Tsum + s[i].Tur;
                Wsum = Wsum + s[i].Wait;
                bur = bur + s[i].Burst;
                
        }
        float avgT, avgW, throughput;
        avgT = (float)Tsum / n;
        avgW = (float)Wsum / n;
        throughput = (float)n / start;
        printf("\nAverage Turnaround Time = Total Turnaround time / No. of processes = (");
        for (int i=0;i<n;i++)
        {
		   printf("%d", s[i].Tur);
		   if ( i < n-1)
		   {
		   	 printf(" + ");
		   }
	    }
	    printf(") / %d ",n);
	    printf(" =  %.4f ms.\n", avgT);
	    
	    printf("\nAverage Waiting Time = Total Waiting time / No. of processes = (");
           for (int i=0;i<n;i++)
           {
		   printf("%d", s[i].Wait);
		   if ( i < n-1)
		   {
		   	 printf(" + ");
		   }
	    }
	    printf(") / %d ",n);
	    printf(" =  %.4f ms.\n", avgW);
	    
        printf("\nCPU Utilization = (CPU burst time + CPU Idle time) / CPU busy time = [ { (");
        for (int i=0;i<n;i++)
        {
                printf("%d", s[i].Burst);
                if (i<n-1)
                {
                        printf(" + ");
                }
        }
        printf(") + (0) } 4/ (");
        for (int i=0;i<n;i++)
        {
                printf("%d", s[i].Burst);
                if (i<n-1)
                {
                        printf(" + ");
                }
        }
        printf(") ] * 100 = 100% \n");
        printf("\nThroughput = No. of process completed / Total time for complition = ");
        printf("%d / (", n);
        for (int i=0;i<n;i++)
        {
                printf("%d", s[i].Burst);
                if (i<n-1)
                {
                        printf(" + ");
                }
        }
        printf(") = %.4f", throughput);
        //%.4f.", throughput);
        printf("\n\n");
}




int input(struct pro s[])
{
        int n;
        printf("Hello world\n");
        printf("Enter number of processes: ");
        scanf("%d", &n);
        int start = 0;
        for (int i = 0; i < n; i++)
        {
                s[i].id = i;
                printf("Enter Arrival time for process P%d: ",i);
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
        printf("\n                        ##### SJF #####\n");
		printf("\nGantt Chart:\n");
        int start = 0;
        for (int i = 0; i < n; i++)
        {
                printf("--------", s[i].id);
        }
        printf("\n");
        for (int i = 0; i < n; i++)
        {
                printf("|  P%d\t", s[i].id);
        }
        printf("|");
        printf("\n");
        for (int i = 0; i < n; i++)
        {
                printf("--------", s[i].id);
        }
        printf("\n");
        for (int i = 0; i < n; i++)
        {
                printf("%d    \t", start);
                start = start + s[i].Burst;
        }
        printf("%d", start);
        printf("\n");
}

void table(struct pro s[], int n)
{
        printf("\n================================================================================");
        printf("\n|\tTime\t|\tPC\t|\tTAT=PC-AT\t|\tWT=TAT-PT\t|");
        printf("\n================================================================================");
        int start = 0;
        for (int i = 0; i < n; i++)
        {
                start = start + s[i].Burst;
                printf("\n|\t%d\t|\tP%d\t|\t    %d\t\t|\t    %d    \t|", start, s[i].id, s[i].Tur, s[i].Wait);
                printf("\n");
                for (int i = 0; i < 4; i++)
                {
                   printf("--------------------");
                }
        }
        printf("\n");
}


int main()

{
        struct pro s[max];
        int n = input(s);
        set(s, n);
        cal(s, n);
        Gantt(s, n);
        table(s,n);
        output(s, n);
}
