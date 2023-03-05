#include <stdio.h>
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
    if (nf == 3)
    {
        line(nf);
        printf("\n|Refrence|   Page  frames  | Page Fault |");
        // midline(nf);
        // printf("\n|        |   Frame number  |      /     |");
    }
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
    int i, j, l, rs[25], frame[10], nf, k, avail, count = 0, hit = 0;
    float pfr = 0, phr = 0;

    printf("Enter the length of Reference String: ");
    scanf("%d", &l);
    printf("Enter Reference String:\n");
    for (i = 1; i <= l; i++)
        scanf("%d", &rs[i]);
    printf("Enter the number of Frames: ");
    scanf("%d", &nf);
    for (i = 0; i < nf; i++)
        frame[i] = -1;
    j = 0;

    Firstline(nf);
    midline(nf);
    printf("\n| String ");
    for (i = 1; i <= nf; i++)
    {
        printf("|%3d  ", i);
    }
    printf("| Page Hit   |");
    line(nf);

    for (i = 1; i <= l; i++)
    {
        printf("\n|   %d\t |", rs[i]);
        avail = 0;
        for (k = 0; k < nf; k++)
            if (frame[k] == rs[i])
                avail = 1;
        if (avail == 0)
        {
            frame[j] = rs[i];
            j = (j + 1) % nf;
            count++;
            for (k = 0; k < nf; k++)
                printf("%4d |", frame[k]);
            printf("%5c       |", 'P');
        }
        else
        {
            for (k = 0; k < nf; k++)
                printf("     |");
            printf("%5c       |", 'H');
        }
    }
    line(nf);
    hit = l - count;
    pfr = ((float)count / (float)l) * 100;
    phr = ((float)hit / (float)l) * 100;
    printf("\n\n1) Total number of page faults : %d", count);
    printf("\n2) Total number of page hits : %d", hit);
    printf("\n3) Page Fault Rate \n\t= (No. of Page Faults / No. of Pages) * 100 \n\t= ( %.2f / %.2f ) * 100 \n\t= %.2f%%", (float)count, (float)l, pfr);
    printf("\n4) Page Hit Rate \n\t= (No. of Page Hits / No. of Pages) * 100 \n\t= ( %.2f / %.2f ) * 100 \n\t= %.2f%%", (float)hit, (float)l, phr);
}
