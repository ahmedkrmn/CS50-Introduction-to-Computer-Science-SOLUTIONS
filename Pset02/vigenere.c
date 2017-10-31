#include <string.h>
#include <cs50.h>
#include <stdio.h>
#include <ctype.h>

bool checker ( string x)
{
    for(int i=0 , n = strlen(x) ; i <n ; i ++)
    {
        if (!isalpha(x[i])) return false;
    }
    return true;
}

int main(int arg , string argv[])
{
    if(arg!=2 || !checker(argv[1])) {
        printf("Erorr, Program will terminate !");
        return 1;
    }

    printf("plaintext:  ");
    string text = get_string();
    for(int i = 0 , n = strlen(text) ,k = strlen(argv[1]), j=0 , q=0 , key=0; i < n ; i++ , j=q%k )
    {

        if(isupper(argv[1][j])) key = argv[1][j]-'A';
        else
            key = argv[1][j]-'a';

        if(isalpha(text[i]))
        {
            if(isupper(text[i])) text[i]= 'A' + ((text[i]-'A')+key)%26;
            else
                text[i]='a' + ((text[i]-'a')+key)%26;
            q++;
        }

        }
    printf("ciphertext: %s\n",text);
}