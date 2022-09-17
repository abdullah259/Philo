#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int ft_atoi(char *sp)
{
    int res;
    int i;
    int neg;
    // int base1;

    i = 0;
    neg = 1;
    res = 0;
    while (sp[i])
    {
        res = res * 10 + (sp[i] - '0');
        i++;
    }
    return (res);
}

// int     *ft_range(int start, int end)
// {
//     int *ptr;
//     int i;
//     int j;

//     if (end == start)
//         i = 1;
//     else if (end > start)
//         i = end - start + 1;
//     else if (start > end)
//         i = start - end ;
//     ptr = malloc(i * sizeof(int));
//     j = 0;
//     while (end >= start)
//     {
//         ptr[j] = end;
//         j++;
//         end--;
//     }
//     if (!j)
//     {
//         while (start >= end)
//         {
//             ptr[j] = end;
//             end++;
//             j++;
//         }
//     }
//     return (ptr);
// }

void    ft_putnbr(int n)
{
    char num[] = "0123456789";

    if (n > 9)
        ft_putnbr(n / 10);
    write(1,&num[n % 10],1);
}

unsigned int    lcm(unsigned int a, unsigned int b)
{
    unsigned int n;


    if (a == 0 || b == 0)
        return (0);
    if (a > b)
        n = a;
    else
        n = b;
    while (1)
    {
        if (n % a == 0 && n % b == 0)
            return (n);
        ++n;
    }
    
}

void    print_hex(int n)
{
    char hex[] = "0123456789abcdef";

    if (n >= 16)
        print_hex(n / 16);
    write(1,&hex[n % 16],1);
}

int main(int arc, char **av)
{
    int i;
    int j;
    int count;

    i = 0;
    // count = 1;
    if (arc == 2)
    {
        while (av[1][i] != '\0')
        {
            if (!((av[1][i] >= 'a' && av[1][i] <= 'z') && av[1][i] >= 'A' && av[1][i] <= 'Z'))
            {
                write(1,&av[1][i],1);
        
            }
            
           else if(av[1][i] >= 'a' && av[1][i] <= 'z')
           {
                count = av[1][i] - 97;
           }
           else if (av[1][i] >= 'A' && av[1][i] <= 'Z')
           {
                count = av[1][i] - 65;
           }
           while (count >= 0)
           {
                write(1,&av[1][i],1);
                count--;
           }
        //    count = 1;
           i++;
        }
        

    }
    // if (arc == 2)
    // {
    //     int i;

    //     i = ft_atoi(sp[1]);
    //     print_hex(i);
    // }
    write(1,"\n",1);
    // printf("\n");
    // int *j = ft_range(0,-3);
    // int i;

    // while (i < 4)
    // {
    //     printf("%d,",j[i]);
    //     i++;
    // }
    // printf("\n");
    // write(1,"\n",1);
    return (0);
}