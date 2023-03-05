#include <stdio.h>
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

// void midline(int nf)
// {
//     if (nf == 3)
//     {
//         printf("\n|---------------------------      /     |");
//     }
//     if (nf == 4)
//     {
//         printf("\n|---------------------------------      /     |");
//     }
//     if (nf == 5)
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
    int n, pg[30], fr[10];
    int count[10], i, j, k, fault, f, flag, temp, current, c, dist, max, m, cnt, p, x, avail;
    int tmp1[10], tmp2[10];
    fault = 0;
    dist = 0;
    k = 0;
    int hitflag = 0;
    printf("Enter the total no pages:");
    scanf("%d", &n);
    printf("Enter the reference string:\n");
    for (i = 0; i < n; i++)
        scanf("%d", &pg[i]);
    printf("\nEnter frame size:");
    scanf("%d", &f);
    ///////////
    Firstline(f);
    midline(f);
    printf("\n| String ");
    for (i = 1; i <= f; i++)
    {
        printf("|%3d  ", i);
        tmp1[i] = 0;
    }
    printf("| Page Hit   |");
    line(f);
    //////////////////
    for (i = 0; i < f; i++)
    {
        count[i] = 0;
        fr[i] = -1;
    }
    for (i = 0; i < n; i++)
    {
        flag = 0;
        temp = pg[i];
        for (j = 0; j < f; j++)
        {
            if (temp == fr[j])
            {
                flag = 1;
                break;
            }
        }
        if ((flag == 0) && (k < f))
        {
            fault++;
            fr[k] = temp;
            k++;
        }
        else if ((flag == 0) && (k == f))
        {
            fault++;
            for (cnt = 0; cnt < f; cnt++)
            {
                current = fr[cnt];
                for (c = i; c < n; c++)
                {
                    if (current != pg[c])
                        count[cnt]++;
                    else
                        break;
                }
            }
            max = 0;
            for (m = 0; m < f; m++)
            {
                if (count[m] > max)
                {
                    max = count[m];
                    p = m;
                }
            }
            fr[p] = temp;
        }
        printf("\n|   %d\t |", pg[i]);
        for (x = 0; x < f; x++)
        {
            printf("%4d |", fr[x]);
            tmp2[x] = fr[x];
            if (tmp1[x] != tmp2[x])
            {
                hitflag = 1;
            }
        }
        /////
        if (hitflag == 1)
        {
            printf("%5c       |", 'P');
        }
        else
        {
            printf("%5c       |", 'H');
        }
        for (int i = 0; i < f; i++)
        {
            tmp1[i] = tmp2[i];
        }
        hitflag = 0;
        ////
    }

    line(f);

    //
    int hit = n - fault;
    float pfr = ((float)fault / (float)n) * 100;
    float phr = ((float)hit / (float)n) * 100;
    printf("\n\n1) Total no. of page faults : %d", fault);
    printf("\n2) Total no. of page hits : %d", hit);
    printf("\n3) Page Fault Rate \n\t= (No. of Page Fault / No. of Pages) * 100 \n\t= ( %.2f / %.2f ) * 100 \n\t= %.2f%%", (float)fault, (float)n, pfr);
    printf("\n4) Page Hit Rate \n\t= (No. of Pagehit / No. of Pages) * 100 \n\t= ( %.2f / %.2f ) * 100 \n\t= %.2f%%", (float)hit, (float)n, phr);
    return 0;
}
