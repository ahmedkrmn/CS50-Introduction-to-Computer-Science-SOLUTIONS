#include <string.h>
#include <cs50.h>
#include <stdio.h>
#include <ctype.h>

int main(int arg , string argv[])
{
    if(arg!=2) {
        printf("Erorr, Program will terminate !");
        return 1;
    }
    int key = 0;
    for(int i = 0 , n = strlen(argv[1]) ; i < n ; i++)
    {
        if(i!=0) key*=10;
        key += argv[1][i]-'0';
    }
    printf("plaintext:  ");
    string text = get_string();
    for(int i = 0 , n = strlen(text) ; i < n ; i++)
    {
        if(isalpha(text[i]))
        {
            if(isupper(text[i])) text[i]= 'A' + ((text[i]-'A')+key)%26;
            else
                text[i]='a' + ((text[i]-'a')+key)%26;
        }

        }
    printf("ciphertext: %s\n",text);
}