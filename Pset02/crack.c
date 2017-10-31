#define _XOPEN_SOURCE
#include <unistd.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
int main(int arg , char** argv)
{
   
    if(arg != 2)
    {
        printf("Error, program will terminate!\n");
        return 1;
    }
    char salt[3];
    for (int i =0 ; i < 2 ; i++)
    {
        salt[i]=argv[1][i];
    }
    salt[2]='\0';

    char _1,_2,_3,_4;

    for(_1 = 'A' ; _1<='z' ; _1++)
    {
        if(!isalpha(_1)) continue;
        for(_2 = 'A' ; _2<='z' ; _2++)
        {
            if(!isalpha(_2)) continue;
            for(_3 = 'A' ; _3<='z' ; _3++)
            {
                if(!isalpha(_3)) continue;
                for(_4 = 'A' ; _4<='z' ; _4++)
                {
                    if(!isalpha(_4)) continue;
                    char key[5] = {_1,_2,_3,_4,'\0'};
                    char *ciphered= crypt(key,salt) ;
                    if(strcmp(ciphered , argv[1] ) == 0) goto PRINT;
                }
            }
        }
    }
PRINT:
    printf("%c%c%c%c\n",_1,_2,_3,_4);
    return 0;
}