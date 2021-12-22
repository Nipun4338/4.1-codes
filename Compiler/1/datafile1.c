#include<stdio.h>

int main(void)
{
    FILE *p1, *p2;
    char c;
    p1=fopen("datafile1.c", "r");
    p2=fopen("parentheses.txt","w");

    if(!p1)
    {
        printf("File cann't be opened!\n");
    }
    else
    {
        while((c=fgetc(p1))!=EOF)
        {
            if(c=='(' || c==')')
            {
                fputc(c,p2);
            }
        }
        fclose(p1);
        fclose(p2);

        p1=fopen("parentheses.txt","r");
        while((c=fgetc(p1))!=EOF)
        {
            printf("%c",c);
        }
        fclose(p1);
    }
}
