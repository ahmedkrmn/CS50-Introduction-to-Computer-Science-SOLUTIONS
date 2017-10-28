#include <stdio.h>
#include <cs50.h>

int main(void)
{
    printf("O hai! How much change is owed?\n");
    float x1 = get_float();
    while(x1<0)
    {
        printf("How much change is owed?\n");
        x1 = get_float();
    }
    x1*=100;
//This code block is used to overcome the percision innacuracy of floats, if input is 4.2 it might be saved as 4.199999999999
/////////////////////////////
    float y = x1-(int)x1;
    int x;
    if(y>0.1) x = (int) x1+1;
    else x = (int) x1;
/////////////////////////////
    int counter = 0;
    while(x>0)
    {

        if(x-25>=0) x-=25;
        else if(x-10>=0) x-=10;
        else if(x-5>=0) x-=5;
        else x-=1;
        counter++;

    }
    printf("%d\n",counter);
}
