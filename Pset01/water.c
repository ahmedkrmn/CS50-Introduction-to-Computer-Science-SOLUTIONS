#include <stdio.h>
#include <cs50.h>
int main(void)
{
    printf("Mintues: ");
    int x = get_int();
    printf("Bottles: %d\n",((x*192)+16-1)/16);
}