#include<stdio.h>

int main(void)
{
    FILE *p1, *p2;
    char c;
    //okfffffffffffffffffffffffff//kfnkfn
    /*
        hhmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmm
    */
    p1=fopen("removing comments newline.c", "r");
    p2=fopen("filtered.txt","w");
    if(!p1)
    {
        printf("File cann't be opened!\n");
    }
    else
    {
        while((c=fgetc(p1))!=EOF)
        {
            if(c=='/')
            {
                c=fgetc(p1);
                if(c=='/')
                {
                    while(c=fgetc(p1)!='\n')
                    {

                    }
                }
                else if(c=='*')
                {
                    while(c=fgetc(p1))
                    {
                        if(c=='*')
                        {
                            char d=fgetc(p1);
                            if(d=='/')
                            {
                                break;
                            }
                        }
                    }
                }
            }
            else if(c!='\n')
            {
                fputc(c,p2);
            }
        }
        fclose(p1);
        fclose(p2);

        p1=fopen("filtered.txt","r");
        while((c=fgetc(p1))!=EOF)
        {
            printf("%c",c);
        }

        fclose(p1);
    }
}



