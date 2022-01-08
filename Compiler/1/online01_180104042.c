/*
Course Name: CSE 4130
Online-1
Lab-2
Group-A2
ID-180104042
*/

#include<stdio.h>

int main(int a, int b)
{
    FILE *p1, *p2;
    char c;
    char d[5]={'m','a','i','n','('};
    char e[7]={'r','e','t','u','r','n',' '};
    int flag=0,flag1=0;

    p1=fopen("online.c", "r");
    p2=fopen("output.txt","w");
    if(!p1)
    {
        printf("File cann't be opened!\n");
    }
    else
    {
        while((c=fgetc(p1))!=EOF)
        {
            if(flag==5 && c!=')')
            {
                printf("%c",c);
            }
            else if(flag==5 && c==')')
            {
                printf("\n");
                flag=0;
            }
            else if(flag<5 && d[flag]==c)
            {
                flag++;
            }
            else
            {
                flag=0;
            }
            if(flag1==7 && c!=';')
            {
                printf("%c",c);
            }
            else if(flag1==7 && c==';')
            {
                printf("\n");
                flag1=0;
            }
            else if(flag1<7 && e[flag1]==c)
            {
                flag1++;
            }
            else
            {
                flag1=0;
            }

        }
        fclose(p1);
        fclose(p2);

        p1=fopen("output.txt","r");
        while((c=fgetc(p1))!=EOF)
        {
            printf("%c",c);
        }

        fclose(p1);
    }
    return 1;
}
