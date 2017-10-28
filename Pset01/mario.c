#include <stdio.h>
#include <cs50.h>

int main(void)
{
    int x;
    do{
        printf("Height: ");
        x = get_int();
    }
    while(x>23 || x<0);
    for (int i=2 ; i <= x+1 ; i++)
    {
        for(int y = 0 ; y <x+1-i ; y++)
            printf(" ");
        for(int y = 0 ; y < i ; y++)
            printf("#");
        printf("\n");
    }
}