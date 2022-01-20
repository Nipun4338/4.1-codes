#include<stdio.h>
#include<ctype.h>
#include <string.h>

FILE *p1, *p2, *p3;
char c;
char *cd[100000];
char array[3]={'/','*',' '};
char *symbol[10000][6];
char x1[100000],x2[100000],temp[100000],x3[10000][1000];
int index[10000];
int cur = 0;
struct data
{
    char* name;
    char* idType;
    char* dataType;
    char* scope;
    char* value;

}v[100];

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
        if(str[0]=='{' || str[0]=='}')
        {
            flag=2;
        }
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

int number(char *str, int len)
{
    int flag=0, count=0;
    for(int i=0; i<len; i++)
    {
        if(!isdigit(str[i]))
        {
            if(str[i]=='.')
            {
                count++;
            }
            else
            {
                flag=1;
            }
        }
    }
    if(count>1)
    {
        flag=1;
    }
    return flag;
}

int identifier(char *str, int len)
{
    int flag=0;
    for(int i=0; i<len; i++)
    {
        if(!isdigit(str[i]) && i==0)
        {
            if(!((str[i]>='A' && str[i]<='Z') || (str[i]>='a' && str[i]<='z') || str[i]=='_'))
            {
                flag=1;
                break;
            }
        }
        else if(!((str[i]>='A' && str[i]<='Z') || (str[i]>='a' && str[i]<='z') || str[i]=='_' || (str[i]>='0' && str[i]<='9')))
        {
            flag=1;
            break;
        }
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
                if(c==';' || c==',' || c=='(' || c==')' || c=='{' || c=='}' || c=='[' || c==']' || c=='\'')
                {
                    fputc(' ', p2);
                    fputc('<', p2);
                    fputc(' ', p2);
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
                if(c==';' || c==',' || c=='(' || c==')' || c=='{' || c=='}' || c=='[' || c==']' || c=='\'')
                {
                    fputc(' ', p2);
                    fputc('>', p2);
                    fputc(' ', p2);
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
                if(c==';' || c==',' || c=='(' || c==')' || c=='{' || c=='}' || c=='[' || c==']' || c=='\'')
                {
                    fputc(' ', p2);
                    fputc('!', p2);
                    fputc(' ', p2);
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
                if(c==';' || c==',' || c=='(' || c==')' || c=='{' || c=='}' || c=='[' || c==']' || c=='\'')
                {
                    fputc(' ', p2);
                    fputc('+', p2);
                    fputc(' ', p2);
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
                if(c==';' || c==',' || c=='(' || c==')' || c=='{' || c=='}' || c=='[' || c==']' || c=='\'')
                {
                    fputc(' ', p2);
                    fputc('-', p2);
                    fputc(' ', p2);
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
                if(c==';' || c==',' || c=='(' || c==')' || c=='{' || c=='}' || c=='[' || c==']' || c=='\'')
                {
                    fputc(' ', p2);
                    fputc('=', p2);
                    fputc(' ', p2);
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
                if(c==';' || c==',' || c=='(' || c==')' || c=='{' || c=='}' || c=='[' || c==']' || c=='\'')
                {
                    fputc(' ', p2);
                    fputc('*', p2);
                    fputc(' ', p2);
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
                if(c==';' || c==',' || c=='(' || c==')' || c=='{' || c=='}' || c=='[' || c==']' || c=='\'')
                {
                    fputc(' ', p2);
                    fputc('/', p2);
                    fputc(' ', p2);
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
                if(c==';' || c==',' || c=='(' || c==')' || c=='{' || c=='}' || c=='[' || c==']' || c=='\'')
                {
                    fputc(' ', p2);
                    fputc('%', p2);
                    fputc(' ', p2);
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
    memset(s, 0, sizeof s);
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
                    if(check==1)
                    {
                        fputs("[par ",p2);
                        fputs(s,p2);
                        fputs("]",p2);
                        //printf("[par %s]", s);
                    }
                    else if(check==2)
                    {
                        fputs("[brc ",p2);
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
                        else
                        {
                            check=number(s,len);
                            if(!check)
                            {
                                fputs("[num ",p2);
                                fputs(s,p2);
                                fputs("]",p2);
                            }
                            else
                            {
                                check=identifier(s,len);
                                if(!check)
                                {
                                    fputs("[id ",p2);
                                    fputs(s,p2);
                                    fputs("]",p2);
                                    //printf("[op %s]", s);
                                }
                                else
                                {
                                    fputs("[unkn ",p2);
                                    fputs(s,p2);
                                    fputs("]",p2);
                                }
                            }
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

void onlyIdentifier()
{
    FILE *p1, *p2;
    p1=fopen("extra_space_removed.txt","r");
    p2=fopen("only_identifer.txt","w");
    char s[100];
    memset(s, 0, sizeof s);
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
                fputs("[",p2);
                fputs(s,p2);
                fputs("]",p2);
                //printf("[sep %s]", s);
            }
            else
            {
                check=keyword(s,len);
                if(check)
                {
                    fputs("[",p2);
                    fputs(s,p2);
                    fputs("]",p2);
                    //printf("[kw %s]", s);
                }
                else
                {
                    check=parentheses(s,len);
                    if(check==1)
                    {
                        fputs("[",p2);
                        fputs(s,p2);
                        fputs("]",p2);
                        //printf("[par %s]", s);
                    }
                    else if(check==2)
                    {
                        fputs("[",p2);
                        fputs(s,p2);
                        fputs("]",p2);
                        //printf("[par %s]", s);
                    }
                    else
                    {
                        check=operators(s,len);
                        if(check)
                        {
                            fputs("[",p2);
                            fputs(s,p2);
                            fputs("]",p2);
                            //printf("[op %s]", s);
                        }
                        else
                        {
                            check=number(s,len);
                            if(!check)
                            {
                                fputs("[",p2);
                                fputs(s,p2);
                                fputs("]",p2);
                            }
                            else
                            {
                                check=identifier(s,len);
                                if(!check)
                                {
                                    fputs("[id ",p2);
                                    fputs(s,p2);
                                    fputs("]",p2);
                                    //printf("[op %s]", s);
                                }
                                else
                                {
                                    fputs("[",p2);
                                    fputs(s,p2);
                                    fputs("]",p2);
                                }
                            }
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


void insert(int index, char* _name, char* _id, char* _dat, char* _scope, char* _value)
{
    v[index].name  = _name;
    v[index].idType = _id;
    v[index].dataType = _dat;
    v[index].scope  =_scope;
    v[index].value  =_value;
}

void display()
{
    int i=0;
    printf("\nSl. No.\t\tName\t\tId Type\t\tData Type\tScope\t\tValue\n");
    for(i=0; i<cur; i++)
    {
        printf("%d\t\t%s\t\t%s\t\t%s\t\t%s\t\t%s\n",i+1,v[i].name,v[i].idType,v[i].dataType,v[i].scope,v[i].value);
    }
}

int search(char* _name, char* _id, char* _scope)
{
    int i=0;

    for(i=0;i<cur;i++)
    {
        if(strcmp(v[i].name,_name)==0 && strcmp(v[i].idType,_id)==0 && strcmp(v[i].scope,_scope)==0 )
        {
            return i;
        }
    }
    return -1;
}

char* modify(char * x)
{
    if(strlen(x)==0)
    {
        return x;
    }
    if(x[0]>='0' && x[0]<='9')
    {
        return x;
    }
    return "";
}

void update(int cur, char* val)
{
    v[cur].value = val;
}


void symbolTable()
{
    FILE *p1, *p2;
    p1=fopen("only_identifer.txt","r");
    int i=0;
    while(fscanf(p1,"%c",&x1[i])!=EOF)
    {
        i++;
    }
    x1[i]='\0';
    fclose(p1);

    int k=0;
    for(i=0;i<strlen(x1);i++)
    {
        if(x1[i]=='[')
        {
            int j=0;
            i++;
            while(x1[i]!=']' && x1[i]!=' ')
            {
                x3[k][j++]=x1[i++];
            }
            x3[k][j]='\0';
            k++;
            if(x1[i]==' ')
            {
                j= 0;
                i++;
                while(x1[i]!=']')
                {
                    x3[k][j++]=x1[i++];
                }
                x3[k][j]= '\0';
                k++;
            }
        }
    }
    int it=0;
    char* scope="global";
    for(i=0;i<k;i++)
    {
        if(strcmp(x3[i],"id")==0)
        {
            if(strcmp(x3[i+2],"(")==0)
            {
                if(strcmp(x3[i-1],"int")==0 || strcmp(x3[i-1],"double")==0 || strcmp(x3[i-1],"float")==0 || strcmp(x3[i-1],"char")==0 )
                {
                    index[it++]=cur;
                    insert(cur++,x3[i+1],"func",x3[i-1],scope,"");
                    scope=x3[i+1];
                    i+=2;
                }
                else
                {
                    int pq=search(x3[i+1],"func","global");
                    if(pq!=-1)
                    {
                        index[it++]=pq;
                    }
                    else
                    {
                        printf("\nID %s is not declared in global scope\n",x3[i+1]);
                    }
                    i+=2;
                }
            }
            else if(strcmp(x3[i+2],"=")==0)
            {
                if(strcmp(x3[i-1],"int")==0 || strcmp(x3[i-1],"double")==0 || strcmp(x3[i-1],"float")==0 || strcmp(x3[i-1],"char")==0 )
                {
                    if(search(x3[i+1],"var",scope)==-1)
                    {
                        index[it++]=cur;
                        insert(cur++,x3[i+1],"var",x3[i-1],scope,modify(x3[i+3]));
                    }
                    else
                    {
                        printf("\nID %s already declared in %s scope\n",x3[i+1],scope);
                    }
                }
                else
                {
                    int pq=search(x3[i+1],"var",scope);
                    if(pq==-1)
                    {
                        printf("\nID %s is not declared in %s scope\n",x3[i+1],scope);
                    }
                    else
                    {
                        update(pq,modify(x3[i+3]));
                        index[it++]=pq;
                    }
                }
                i+=2;
            }
            else if(strcmp(x3[i+2],";")==0 || strcmp(x3[i+2],",")==0 || strcmp(x3[i+2],")")==0 )
            {
                if(strcmp(x3[i-1],"int")==0 || strcmp(x3[i-1],"double")==0 || strcmp(x3[i-1],"float")==0 || strcmp(x3[i-1],"char")==0 )
                {
                    if(search(x3[i+1],"var",scope)==-1)
                    {
                        index[it++]=cur;
                        insert(cur++,x3[i+1],"var",x3[i-1],scope,"");
                    }
                    else
                    {
                        printf("\nID %s already declared in %s scope\n",x3[i+1],scope);
                    }
                    i+=2;
                }
                else
                {
                    if(search(x3[i+1],"var",scope)==-1)
                    {
                        printf("\nID %s is not declared in %s scope\n",x3[i+1],scope);
                    }
                    else
                    {
                        index[it++]=search(x3[i+1],"var",scope);
                    }
                    i+=2;
                }
            }
        }
        else if(strcmp(x3[i],"}")==0)
        {
            scope = "global";
        }
    }
    display();

    p2=fopen("symbol_table_final.txt", "w");
    it =0;
    int j=0;
    for(i=0;i<strlen(x1);i++)
    {
        if(x1[i]=='[')
        {
            printf("%c",x1[i]);
            fputc(x1[i],p2);
            i++;
            while(x1[i]!=']' && x1[i]!=' ')
            {
                printf("%c",x1[i]);
                fputc(x1[i],p2);
                i++;
            }
            if(x1[i]==' ')
            {
                printf("%c",x1[i]);
                fputc(x1[i],p2);
                j=0;
                i++;
                while(x1[i]!=']')
                {
                    i++;
                }
                fputc(index[it]+1+48,p2);
                printf("%d",index[it++]+1);
            }
            printf("%c",x1[i]);
            fputc(x1[i],p2);

        }
        else
        {
            printf("%c",x1[i]);
        }
    }
    fclose(p2);

}

int main(void)
{
    input();
    comment_newline_remove();
    extra_space_remove("comments_and_newline_removed.txt");
    tokenize();
    onlyIdentifier();
    symbolTable();
    //output("tokenized_all.txt");
}

