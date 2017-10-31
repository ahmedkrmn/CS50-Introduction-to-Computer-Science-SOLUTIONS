#include <stdio.h>
#include <cs50.h>
#include <ctype.h>
#include <string.h>
int main()
{
    string s = get_string();
    printf("%c",toupper(s[0]));
    for(int i =1 , size = strlen(s) ; i<size ; i++)
    {
        if(s[i-1]==' ') printf("%c",toupper(s[i]));
    }
    printf("\n");
}