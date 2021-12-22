#include<stdio.h>
#include<stdio.h>
int main(void)
{
    FILE *p1;
    char c;
    char d[9]={'#','i','n','c','l','u','d','e','<'};
    int flag=0;
    p1=fopen("print header.c", "r");
    if(!p1)
    {
        printf("File cann't be opened!\n");
    }
    else
    {
        while((c=fgetc(p1))!=EOF)
        {
            if(flag==9 && c!='>')
            {
                printf("%c",c);
            }
            else if(flag==9 && c=='>')
            {
                printf("\n");
                flag=0;
            }
            else if(flag<9 && d[flag]==c)
            {
                flag++;
            }
            else
            {
                flag=0;
            }
        }
        fclose(p1);
    }
}

