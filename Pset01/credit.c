#include <stdio.h>
#include <cs50.h>

int main(void)
{
    long long x;
        printf("Number: ");
        x = get_long_long();
    int arr[100], c = 0;
    for(int i = 0 ; x ; i++)
    {
        arr[i]=x%10;
        c++;
        x/=10;
    }
    if(c>5){
    int tempsum = 0;
    for(int i = 1 ; i<c ; i+=2)
    {
        int q = arr[i]*2;
        while(q)
        {
            tempsum+=q%10;
            q/=10;
        }
    }
     for(int i = 0 ; i<c ; i+=2)
    {

            tempsum+=arr[i];

    }
    bool valid;
    if(tempsum%10 == 0 ) valid = true;
    else valid = false;

    if(!valid) printf("INVALID\n");
    else
    {
        if(arr[c-1]==3) printf("AMEX\n");
        else if (arr[c-1]==4) printf("VISA\n");
        else printf("MASTERCARD\n");
    }
    }
    else
        printf("INVALID\n");
}