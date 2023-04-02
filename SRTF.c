#include<stdio.h>

int n,idle=0;
int arri[10],burst[10],z[10],tut[10],wt[10],cm[10];

void accept_detail()
{
    printf("Enter the number of processes\n");
    scanf("%d",&n);
    for(int i=0;i<n;i++)
    {
        z[i]=i;
        printf("Enter the arrival time of process %d\n",i);
        scanf("%d",&arri[i]);
        printf("Enter the burst time of process %d\n",i);
        scanf("%d",&burst[i]);
    }
}

void sort()
{
    int a=n;
    int temp,temp2;
    int b;
    for(int i=0;i<a;i++)
    {
        for(int j=i+1;j<a;j++)
        {
            if(arri[i]>arri[j])
            {
                temp=arri[i];
                arri[i]=arri[j];
                arri[j]=temp;

                temp2=burst[i];
                burst[i]=burst[j];
                burst[j]=temp2;

                b=z[i];
                z[i]=z[j];
                z[j]=b;
            }
        }
    } 
}

void gantt()
{
    printf("Gantt Chart\n");
    for (int i = 0; i < n; i++)
    {
        printf("-------",z[i]);
    }
    printf("\n");
    for (int i = 0; i < n; i++)
    {
        printf("|  P%d  ",z[i]);
    }
    printf("|\n");
    for (int i = 0; i < n; i++)
    {
        printf("-------",z[i]);
    }
    printf("\n");
    printf("0");
    for (int i = 0; i < n; i++)
    {
        printf("      %d",cm[i]);
    }
    
}

void cal()
{
    if(arri[0]>0)
    {
        cm[0]=arri[0]+burst[0];
        idle=idle+arri[0];
    }
    else
    {
        cm[0]=arri[0]+burst[0];
    }
    for(int i=1;i<n;i++)
    {
        if (arri[i]>cm[i-1])
        {
            idle=idle+arri[i]-cm[i-1];
            cm[i]=arri[i]+burst[i];
        }
        else
        {
            cm[i]=cm[i-1]+burst[i];
        }
        
    }
    for (int i = 0; i < n; i++)
    {
        tut[i]=cm[i]-arri[i];
        wt[i]=tut[i]-burst[i];
    }
    
}

void table()
{
    printf("\n================================================================================");
        printf("\n|\tTime\t|\tPC\t|\tTAT=PC-AT\t|\tWT=TAT-PT\t|");
        printf("\n================================================================================");
        printf("\n|\t0\t|\t-\t|\t    -\t\t|\t    -    \t|\n");
        for (int i = 0; i < 4; i++)
                {
                   printf("--------------------");
                }
        for (int i = 0; i < n; i++)
        {
                printf("\n|\t%d\t|\tP%d\t|\t    %d\t\t|\t    %d    \t|", cm[i], z[i], tut[i], wt[i]);
                printf("\n");
                for (int i = 0; i < 4; i++)
                {
                   printf("--------------------");
                }
        }
        printf("\n");

}


void output()
{
        int Tsum = 0, Wsum = 0,bur = 0,totaltime;
        for (int i = 0; i < n; i++)
        {
                Tsum = Tsum + tut[i];
                Wsum = Wsum + wt[i];
                bur = bur + burst[i];
                
        }
        float acb = (float)bur + (float)idle;
        float uti = (float)bur / acb;
        float uti1 = uti * 100;
        float avgT, avgW, throughput;
        avgT = (float)Tsum / n;
        avgW = (float)Wsum / n;
        throughput = (float)n / cm[n-1];
        printf("\nAverage Turnaround Time = Total Turnaround time / No. of processes = (");
        for (int i=0;i<n;i++)
        {
		   printf("%d", tut[i]);
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
		   printf("%d", wt[i]);
		   if ( i < n-1)
		   {
		   	 printf(" + ");
		   }
	    }
	    printf(") / %d ",n);
	    printf(" =  %.4f ms.\n", avgW);
	    
        printf("\nCPU Utilization = (CPU burst time / (CPU Idle time + CPU burst time)) * 100% = [ (");
        for (int i=0;i<n;i++)
        {
                printf("%d", burst[i]);
                if (i<n-1)
                {
                        printf(" + ");
                }
        }
        printf(") / { (");
        for (int i=0;i<n;i++)
        {
                printf("%d", burst[i]);
                if (i<n-1)
                {
                        printf(" + ");
                }
        }
        printf(") + (%d",idle);
        printf(") } ] * 100 =  %.2f %\n",uti1);
        printf("\nThroughput = No. of process completed / Total time for complition = ");
        printf("%d / (", n);
        printf("%d", cm[n-1]);
        printf(") = %.4f", throughput);
        //%.4f.", throughput);*/
        printf("\n\n");
}

void main()
{
    printf("This is FCFS scheduling algorithm\n");
    accept_detail();
    sort();
    cal();
    gantt();
    table();
    output();
}