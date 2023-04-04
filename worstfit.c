#include <stdio.h>

struct process
{
   int size;
   int set;
   int holeid;
} p[10];

struct hole
{
   int hid;
   int size;
   int actual;
   int set;
} h[10];

void sorthole(struct hole a[], int n)
{
   struct hole temp;
   int i, j;
   for (i = 0; i < n - 1; i++)
   {
      for (j = i + 1; j < n; j++)
      {
         if (a[i].size < a[j].size)
         {
            temp = a[i];
            a[i] = a[j];
            a[j] = temp;
         }
      }
   }
}

int enterhole(struct hole a[])
{
   int n;
   printf("Enter the number of Holes : ");
   scanf("%d", &n);
   for (int i = 0; i < n; i++)
   {
      printf("Enter size for hole H%d : ", i);
      scanf("%d", &a[i].size);
      a[i].actual = a[i].size;
      a[i].hid = i;
      a[i].set = 0;
   }
   return n;
}

int enterprocess(struct process a[])
{
   int n;
   printf("\nEnter number of process : ");
   scanf("%d", &n);
   for (int i = 0; i < n; i++)
   {
      printf("enter the size of process P%d : ", i);
      scanf("%d", &a[i].size);
      a[i].set = 0;
   }
   return n;
}
void calcu(struct hole a[], struct process b[], int no_h, int no_p)
{
   for (int i = 0; i < no_p; i++)
   {
      sorthole(a, no_h);
      for (int j = 0; j < no_h; j++)
      {
         if (b[i].set != 1 && a[j].set != 1)
         {
            if (b[i].size <= a[j].size)
            {
               b[i].set = 1;
               a[j].set = 1;
               b[i].holeid = a[j].hid;
               a[j].size -= b[i].size;
            }
         }
      }
   }
}

void out(struct hole a[], struct process b[], int no_h, int no_p)
{
   printf("\n\t\t\tBest fit\n");
   printf("=========================================================");
   printf("\n|\tProcess\t|\tPSize\t|\tHole\t\t|\n");
   printf("=========================================================\n");
   for (int i = 0; i < no_p; i++)
   {
      if (b[i].set != 1)
      {
         printf("|\tP%d\t|\t%d\t|\tNot allocated\t|", i, b[i].size);
         printf("\n---------------------------------------------------------\n");
      }
      else
      {
         printf("|\tP%d\t|\t%d\t|\tH%d\t\t|", i, b[i].size, b[i].holeid);
         printf("\n---------------------------------------------------------\n");
      }
   }
   printf("\n\n=========================================================");
   printf("\n|\tHole\t|\tActual\t|\tAvailable\t|\n");
   printf("=========================================================\n");
   int vest = 0;
   for (int i = 0; i < no_h; i++)
   {
      vest = vest + a[i].size;
      printf("|\tH%d\t|\t%d\t|\t%d\t\t|", a[i].hid, a[i].actual, a[i].size);
      printf("\n---------------------------------------------------------\n");
   }
   printf("\t\t\tTotal = |\t%d\t\t|\n", vest);
   printf("\t\t\t\t-------------------------\n\n\n");

   printf("Total Wastage is %d MB.", vest);
   printf("\n\n\n");
}

int main()
{
   int no_h, no_p;
   no_h = enterhole(h);
   no_p = enterprocess(p);
   calcu(h, p, no_h, no_p);
   out(h, p, no_h, no_p);

   return 0;
}
