#include <stdio.h>
#include <limits.h>
int count = 0;
int frames;
int checkHit(int incomingPage, int queue[], int occupied)
{

    for (int i = 0; i < occupied; i++)
    {
        if (incomingPage == queue[i])
            return 1;
    }

    return 0;
}

void printFrame(int queue[], int occupied, int flag)
{
    for (int i = 0; i < occupied; i++)
    {
        printf("%4d |", queue[i]);
    }
    // if (count == 0)
    // {
    //     printf("%4d |", -1);
    //     printf("%4d |", -1);
    //     count++;
    // }
    // else if (count == 1)
    // {
    //     printf("%4d |", -1);
    //     count++;
    // }
    // while(count!=0)
    // {
    //     printf("%4d |", -1);
    //     count--;
    // }
    // for (int i = frames-count; i >1; i--)
    // {
    //     printf("%4d |", -1);
    // }
    // printf("\n%d",count);
    if(flag !=1)
        count--;
    for (int i = count; i>0;i--)
    {
        printf("%4d |", -1);
    }
}
// void line(int f)
// {
//     if (f == 3)
//     {
//         printf("\n|---------------------------------------|");
//     }
//     if (f == 4)
//     {
//         printf("\n|---------------------------------------------|");
//     }
//     if (f == 5)
//     {
//         printf("\n|---------------------------------------------------|");
//     }
// }
// void midline(int f)
// {
//     if (f == 3)
//     {
//         printf("\n|---------------------------      /     |");
//     }
//     if (f == 4)
//     {
//         printf("\n|---------------------------------      /     |");
//     }
//     if (f == 5)
//     {
//         printf("\n|---------------------------------------      /     |");
//     }
// }
// void Firstline(int f)
// {
//     if (f == 3)
//     {
//         line(f);
//         printf("\n|Refrence|   Page frames   | Page Fault |");
//     }
//     else if (f == 4)
//     {
//         line(f);
//         printf("\n|Refrence|       Page frames     | Page Fault |");
//     }
//     else if (f == 5)
//     {
//         line(f);

//         printf("\n|Refrence|         Page frames         | Page Fault |");
//     }
// }

void line(int nf)
{
    if (nf >=3)
    {
        printf("\n|---------------------------------");
    }
    // if (nf == 4)
    // {
    //     printf("\n|---------------------------------------------|");
    // }
    // if (nf == 5)
    // {
    //     printf("\n|---------------------------------------------------|");
    // }
    for (int i = 3; i <= nf; i++)
    {
        printf("------");
    }
    printf("|");
    
}
void midline(int nf)
{
    if (nf >= 3)
    {
        printf("\n|        -------------");
    }
    // if (nf == 4)
    // {
    //     printf("\n|        -------------------------            |");
    // }
    // if (nf == 5)
    // {
    //     printf("\n|        -------------------------------            |");
    // }
    for (int i = 3; i <= nf; i++)
    {
        printf("------");
    }
    printf("            |");
}
void Firstline(int nf)
{
    // else if (nf == 4)
    // {
    //     line(nf);
    //     printf("\n|Refrence|      Page  frames     | Page Fault |");
    //     midline(nf);
    //     printf("\n|        |      Frame number     |      /     |");
    // }
    // else if (nf == 5)
    // {
    //     line(nf);
    //     printf("\n|Refrence|         Page  frames        | Page Fault |");
    //     midline(nf);
    //     printf("\n|        |         Frame number        |      /     |");
    // }
    line(nf);
    printf("\n|Refrence|");
    for (int i = 3; i <= nf; i++)
    {
        printf("   ");
    }
    printf("Page  frames  ");
    for (int i = 4; i <= nf; i++)
    {
        // for (int j = 2; j < ; j+=3)
        // {
        //     printf(" ");
        // }
        printf("   ");
    }
    printf("| Page Fault |");
    midline(nf);
    printf("\n|        |");
    for (int i = 3; i <= nf; i++)
    {
        printf("   ");
    }
    printf("Frame number  ");
    for (int i = 4; i <= nf; i++)
    {
        printf("   ");
    }
    printf("|      /     |");
    
    
}


int main()
{

    printf("Enter the number of Pages: ");
    int nop;
    scanf("%d", &nop);
    int incomingStream[nop];
    printf("Enter Page Reference String:\n");
    for (int i = 0; i < nop; i++)
    {
        scanf("%d", &incomingStream[i]);
    }

    // int frames;
    printf("Enter the number of Frames: ");
    scanf("%d", &frames);
    count=frames;
    int n = sizeof(incomingStream) / sizeof(incomingStream[0]);
    int queue[n];
    int distance[n];
    int occupied = 0;
    int pagefault = 0;
    //
    Firstline(frames);
    midline(frames);
    printf("\n| String ");
    for (int i = 1; i <= frames; i++)
    {
        printf("|%3d  ", i);
    }
    printf("| Page Hit   |");
    line(frames);
    // printf("\n");
    //
    for (int i = 0; i < n; i++)
    {
        // count=i;
        printf("\n|   %d\t |", incomingStream[i]);

        if (checkHit(incomingStream[i], queue, occupied))
        {
            printFrame(queue, occupied,1);
            printf("%5c       |", 'H');
        }

        else if (occupied < frames)
        {
            queue[occupied] = incomingStream[i];
            pagefault++;
            occupied++;

            printFrame(queue, occupied,0);
            printf("%5c       |", 'P');
        }
        else
        {

            int max = INT_MIN;
            int index;
            // get LRU distance for each item in frame
            for (int j = 0; j < frames; j++)
            {
                distance[j] = 0;
                // traverse in reverse direction to find
                // at what distance  frame item occurred last
                for (int k = i - 1; k >= 0; k--)
                {
                    ++distance[j];

                    if (queue[j] == incomingStream[k])
                        break;
                }

                // find frame item with max distance for LRU
                // also notes the index of frame item in queue
                // which appears furthest(max distance)
                if (distance[j] > max)
                {
                    max = distance[j];
                    index = j;
                }
            }
            queue[index] = incomingStream[i];
            printFrame(queue, occupied,0);
            printf("%5c       |", 'F');
            pagefault++;
        }
    }

    line(frames);
    printf("\n");

    int hit = n - pagefault;
    float pfr = ((float)pagefault / (float)n) * 100;
    float phr = ((float)hit / (float)n) * 100;
    printf("\n\n1) Total no. of page faults : %d", pagefault);
    printf("\n2) Total no. of page hits : %d", hit);
    printf("\n3) Page Fault Rate \n\t= (No. of Page Fault / No. of Pages) * 100 \n\t= ( %.2f / %.2f ) * 100 \n\t= %.2f%%", (float)pagefault, (float)n, pfr);
    printf("\n4) Page Hit Rate \n\t= (No. of Pagehit / No. of Pages) * 100 \n\t= ( %.2f / %.2f ) * 100 \n\t= %.2f%%", (float)hit, (float)n, phr);
    printf("\n");
    return 0;
}