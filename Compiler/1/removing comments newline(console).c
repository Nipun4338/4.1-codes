#include<stdio.h>
FILE *p1, *p2, *p3;
char c;
char *cd[100000];
char array[3]={'/','*',' '};

/*
gdksgkl
*/

void input()
{
    p1=fopen("user_input_from_console.txt","w");
    while(1)
    {
        fgets(cd,sizeof(cd),stdin);
        if(strncmp(cd,"exit\n")==0)
        {
            break;
        }
        fputs(cd,p1);
    }
    fclose(p1);
}

void output(char *str)
{
    p1=fopen(str,"r");
    while((c=fgetc(p1))!=EOF)
    {
        printf("%c",c);
    }
    fclose(p1);
}

void comment_newline_remove()
{
    p1=fopen("user_input_from_console.txt","r");
    p2=fopen("comments_and_newline_removed.txt","w");
    if(!p1)
    {
        printf("File cann't be opened!\n");
    }
    else
    {
        while((c=fgetc(p1))!=EOF)
        {
            if(c==array[0])
            {
                c=fgetc(p1);
                if(c==array[0])
                {
                    while((c=fgetc(p1))!='\n')
                    {

                    }
                }
                else if(c==array[1])
                {
                    while(c=fgetc(p1))
                    {
                        if(c==array[1])
                        {
                            char d=fgetc(p1);
                            if(d==array[0])
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
    }
    fclose(p1);
    fclose(p2);
}

void extra_space_remove()
{
    p1=fopen("extra_space_removed.txt", "w");
    p2=fopen("comments_and_newline_removed.txt","r");
    int flag=0;
    while((c=fgetc(p2))!=EOF)
    {
        if(c==array[2] && flag==0)
        {
            fputc(c, p1);
            flag=1;
            continue;
        }
        else if(c==array[2] && flag==1)
        {
            continue;
        }
        else
        {
            fputc(c, p1);
            flag=0;
        }
    }
    fclose(p1);
    fclose(p2);
}

int main(void)
{
    input();
    comment_newline_remove();
    extra_space_remove();
    output("extra_space_removed.txt");
}
