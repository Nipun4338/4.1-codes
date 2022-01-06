#include<stdio.h>
#include<ctype.h>
#include <string.h>

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
        if(strcmp(cd,"exit\n")==0)
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
                else
                {
                    fputc(array[0],p2);
                    fputc(c,p2);
                }
            }
            else if(c!='\n')
            {
                fputc(c,p2);
            }
            else if(c=='\n')
            {
                fputc(' ',p2);
            }
        }
    }
    fclose(p1);
    fclose(p2);
}

void extra_space_remove(char *ch)
{
    p1=fopen("extra_space_removed.txt", "w");
    p2=fopen(ch,"r");
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

int keyword(char *str, int len)
{
    int flag;
    if(strcmp(str,"int")==0 || strcmp(str,"char")==0 || strcmp(str,"float")==0 || strcmp(str,"double")==0 || strcmp(str,"if")==0 || strcmp(str,"else")==0 || strcmp(str,"while")==0 || strcmp(str,"for")==0)
    {
        flag=1;
    }
    else
    {
        flag=0;
    }
    return flag;
}

int seperator(char *str, int len)
{
    int flag;
    if(len==1 && (str[0]==';' || str[0]=='\'' || str[0]==','))
    {
        flag=1;
    }
    else
    {
        flag=0;
    }
    return flag;
}

int parentheses(char *str, int len)
{
    int flag;
    if(len==1 && (str[0]=='(' || str[0]==')' || str[0]=='{' || str[0]=='}' || str[0]=='[' || str[0]==']'))
    {
        flag=1;
    }
    else
    {
        flag=0;
    }
    return flag;
}

int operators(char *str, int len)
{
    int flag;
    if(str[0]=='+' || str[0]=='-' || str[0]=='*' || str[0]=='/' || str[0]=='=' || str[0]=='>' || str[0]=='<' || str[0]=='%' || str[0]=='!' || str[0]=='&' || str[0]=='|' || str[0]=='^')
    {
        flag=1;
    }
    else
    {
        flag=0;
    }
    return flag;
}

void tokenize()
{
    p1=fopen("extra_space_removed.txt", "r");
    p2=fopen("tokenized.txt","w");

    while((c=fgetc(p1))!=EOF)
    {
        if(c==';' || c==',' || c=='(' || c==')' || c=='{' || c=='}' || c=='[' || c==']' || c=='\'')
        {
            fputc(' ', p2);
            fputc(c, p2);
            fputc(' ', p2);
        }
        else if(c=='<')
        {
            c=fgetc(p1);
            if(c=='=')
            {
                fputc(' ', p2);
                fputc('<', p2);
                fputc(c, p2);
                fputc(' ', p2);
            }
            else
            {
                fputc(' ', p2);
                fputc('<', p2);
                fputc(' ', p2);
                fputc(c, p2);
            }
        }
        else if(c=='>')
        {
            c=fgetc(p1);
            if(c=='=')
            {
                fputc(' ', p2);
                fputc('>', p2);
                fputc(c, p2);
                fputc(' ', p2);
            }
            else
            {
                fputc(' ', p2);
                fputc('>', p2);
                fputc(' ', p2);
                fputc(c, p2);
            }
        }
        else if(c=='!')
        {
            c=fgetc(p1);
            if(c=='=')
            {
                fputc(' ', p2);
                fputc('!', p2);
                fputc(c, p2);
                fputc(' ', p2);
            }
            else
            {
                fputc(' ', p2);
                fputc('!', p2);
                fputc(' ', p2);
                fputc(c, p2);
            }
        }
        else if(c=='+')
        {
            c=fgetc(p1);
            if(c=='+')
            {
                fputc(' ', p2);
                fputc(c, p2);
                fputc(c, p2);
                fputc(' ', p2);
            }
            else if(c=='=')
            {
                fputc(' ', p2);
                fputc('+', p2);
                fputc(c, p2);
                fputc(' ', p2);
            }
            else
            {
                fputc(' ', p2);
                fputc('+', p2);
                fputc(' ', p2);
                fputc(c, p2);
            }
        }
        else if(c=='-')
        {
            c=fgetc(p1);
            if(c=='-')
            {
                fputc(' ', p2);
                fputc(c, p2);
                fputc(c, p2);
                fputc(' ', p2);
            }
            else if(c=='=')
            {
                fputc(' ', p2);
                fputc('-', p2);
                fputc(c, p2);
                fputc(' ', p2);
            }
            else
            {
                fputc(' ', p2);
                fputc('-', p2);
                fputc(' ', p2);
                fputc(c, p2);
            }
        }
        else if(c=='=')
        {
            c=fgetc(p1);
            if(c=='=')
            {
                fputc(' ', p2);
                fputc(c, p2);
                fputc(c, p2);
                fputc(' ', p2);
            }
            else
            {
                fputc(' ', p2);
                fputc('=', p2);
                fputc(' ', p2);
                fputc(c, p2);
            }
        }
        else if(c=='*')
        {
            c=fgetc(p1);
            if(c=='=')
            {
                fputc(' ', p2);
                fputc('*', p2);
                fputc(c, p2);
                fputc(' ', p2);
            }
            else
            {
                fputc(' ', p2);
                fputc('*', p2);
                fputc(' ', p2);
                fputc(c, p2);
            }
        }
        else if(c=='/')
        {
            c=fgetc(p1);
            if(c=='=')
            {
                fputc(' ', p2);
                fputc('/', p2);
                fputc(c, p2);
                fputc(' ', p2);
            }
            else
            {
                fputc(' ', p2);
                fputc('/', p2);
                fputc(' ', p2);
                fputc(c, p2);
            }
        }
        else if(c=='%')
        {
            c=fgetc(p1);
            if(c=='=')
            {
                fputc(' ', p2);
                fputc('%', p2);
                fputc(c, p2);
                fputc(' ', p2);
            }
            else
            {
                fputc(' ', p2);
                fputc('%', p2);
                fputc(' ', p2);
                fputc(c, p2);
            }
        }
        else
        {
            fputc(c, p2);
        }
    }
    fclose(p1);
    fclose(p2);
    extra_space_remove("tokenized.txt");
    p1=fopen("extra_space_removed.txt", "r");
    p2=fopen("tokenized_all.txt","w");
    char s[100];
    int len=0;
    while((c=fgetc(p1))!=EOF)
    {
        if(!isspace(c) && c!='\0' && c!='\n')
        {
            s[len]=c;
            len++;
        }
        else
        {
            int check=seperator(s,len);
            if(check)
            {
                fputs("[sep ",p2);
                fputs(s,p2);
                fputs("]",p2);
                //printf("[sep %s]", s);
            }
            else
            {
                check=keyword(s,len);
                if(check)
                {
                    fputs("[kw ",p2);
                    fputs(s,p2);
                    fputs("]",p2);
                    //printf("[kw %s]", s);
                }
                else
                {
                    check=parentheses(s,len);
                    if(check)
                    {
                        fputs("[par ",p2);
                        fputs(s,p2);
                        fputs("]",p2);
                        //printf("[par %s]", s);
                    }
                    else
                    {
                        check=operators(s,len);
                        if(check)
                        {
                            fputs("[op ",p2);
                            fputs(s,p2);
                            fputs("]",p2);
                            //printf("[op %s]", s);
                        }
                    }
                }
            }
            memset(s, 0, sizeof s);
            len=0;
        }
    }
    fclose(p1);
    fclose(p2);
}

int main(void)
{
    input();
    comment_newline_remove();
    extra_space_remove("comments_and_newline_removed.txt");
    tokenize();
    output("tokenized_all.txt");
}

