#include <stdio.h>
#include <cs50.h>
#include <ctype.h>
#include <string.h>
int main()
{
    string s = get_string();
    for(int i =0 , size = strlen(s) ; i<size ; i++)
    {
        if((s[i-1]==' '|| i==0) && s[i]!=' ') printf("%c",toupper(s[i]));
    }
    printf("\n");
}