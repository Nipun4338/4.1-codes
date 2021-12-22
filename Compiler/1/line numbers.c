#include<stdio.h>

int main(void)
{
    FILE *p1;
    char c;
    int flag=1;
    p1=fopen("line numbers.c", "r");
    if(!p1)
    {
        printf("File cann't be opened!\n");
    }
    else
    {
        printf("1.");
        while((c=fgetc(p1))!=EOF)
        {
            printf("%c",c);
            if(c=='\n')
            {
                flag++;
                printf("%d",flag);
                printf(".");
            }
        }
        fclose(p1);
    }
}


