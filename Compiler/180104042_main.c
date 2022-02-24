#include<stdio.h>
#include<ctype.h>
#include <string.h>

FILE *p1, *p2, *p3;
char c;
char *cd[100000];
char array[3]={'/','*',' '};
char *symbol[10000][6];
char x1[100000],x2[100000],temp[100000],x3[10000][1000],ckt[70][70][500];;
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
        else if(str[0]=='(' || str[0]==')')
        {
            flag=3;
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

void error(){
    char str[10000][10000];
    char ar[10000],br[10000];
    char a[10000],b[10000],temp[10000],c[70][70][500];
    int inde[10000];
    int cur = 0;
    int sz[1000];
    int i,n,t,k,j,x=0,y=0,m;
    FILE *fp = fopen("input.txt","r");
    FILE *fp2 = fopen("intermediate ouput.txt","w");
    FILE *fp3 = fopen("error.txt","w");
    i = 1;

    // take input and comment remove 1st assignment
    int c1 = 0, c2  = 0;
    while(fgets(str[i],500,fp))
    {
        int sz = strlen(str[i]);
        c1 = 0;
        for(j=0; j<sz; j++)
        {

            if(j+1<sz && str[i][j]=='/' && str[i][j+1]=='/')
            {
                c1 = 1;
                str[i][j]  = str[i][j+1]  = ' ';
                j++;
            }
            else if(j+1<sz && str[i][j]=='/' && str[i][j+1]=='*')
            {
                c2 = 1;
                str[i][j] = str[i][j+1]  =' ';
                j++;
            }
            else if(j+1<sz && str[i][j]=='*' && str[i][j+1]=='/')
            {
                c2 = 0;
                str[i][j]  = str[i][j+1] = ' ';
                j++;
            }
            else if(c1 || c2)
            {
                str[i][j]  = ' ';
            }

        }
        i++;
    }
    int totalsz = i;



    // add proper space 2nd assignment
    for(k=1; k<totalsz; k++)
    {

        int flag  =0;
        int n = strlen(str[k]);
        strcpy(ar,str[k]);
        j = 0;
        int sepOn = 0;
        for(i=0; i<n; i++)
        {

            if(seperator(ar[i], 1)==1)
            {
                if(ar[i]=='\'')
                {
                    if(sepOn)
                    {
                        sepOn = 0;
                        br[j++]  = ' ';
                        br[j++]  = ar[i];
                    }
                    else
                    {
                        br[j++]  = ar[i];
                        br[j++]  = ' ';
                        sepOn = 1;
                    }
                }
                else
                {
                    br[j++]  = ' ';
                    br[j++]  = ar[i];
                }
                br[j++]  = ' ';


            }
            else if(operators(ar[i], 1)==1)
            {
                if(ar[i+1]=='=')
                {
                    br[j++]  = ' ';
                    br[j++]  = ar[i];
                    br[j++]  = ar[i+1];
                    i++;
                    br[j++]  = ' ';
                }
                else
                {
                    br[j++]  = ' ';
                    br[j++]  = ar[i];
                    br[j++]  = ' ';
                }
                flag  =1;
            }
            else if(number(ar[i], 1)==1)
            {
                if(flag==0)
                {
                    flag = 1;
                    br[j++]  = ' ';
                }
                br[j++]  = ar[i];
            }
            else if(parentheses(ar[i], 1)==3)
            {
                br[j++]  = ' ';
                br[j++]  = ar[i];
                if(ar[i]!=')')
                    br[j++]  = ' ';
            }
            else if(parentheses(ar[i],1)==2)
            {
                br[j++]  = ' ';
                br[j++]  = ar[i];
                if(ar[i]!='}')
                    br[j++]  = ' ';
            }
            else
            {
                flag  =1;
                br[j++]  = ar[i];
            }
        }
        br[j-1]  = ' ';
        br[j] = '\0';

        strcpy(str[k],br);
    }



    //remove multiple whitespace 1st assignment

    for(k=1; k<totalsz; k++)
    {
        strcpy(ar,str[k]);
        br[0]  = '\0';
        j = 0;
        for(i=0; i<strlen(ar); i++)
        {
            if(ar[i]==' ')
            {
                br[j++]  = ' ';
                while(i<strlen(ar) && ar[i]==' ')
                    i++;
                i--;
            }
            else br[j++]  =ar[i];

        }
        br[j]  = '\0';
        strcpy(str[k],br);
    }


    //label the tokens assignment 2
    int fb = 0,sb = 0;
    int isIf = 0,semicolonIf=0;
    for(k=1; k<=totalsz; k++)
    {
        j = 0;
        int forloop = 0;
        int pt = 0;
        fprintf(fp2,"%d ",k);
        strcpy(br,str[k]);
        char pre[100] = {'-','1'};
        for(i=0; i<strlen(br); i++)
        {
            if(br[i]==' ')
            {

                ar[j++] = '\0';
                if(strlen(ar)==0)
                {
                    j  =0;
                    continue;
                }

                if(seperator(ar, 1)==1)
                {
                    fprintf(fp2,"sep %s ",ar);
                    if(strcmp(ar,";")==0)
                    {
                        semicolonIf++;
                        if(forloop==2 || forloop==3)
                            forloop++;
                        else if(forloop>=4)
                        {
                            fprintf(fp3,"Only two semicolon in for loop at line %d\n",k);
                        }
                        else if(strcmp(ar,pre)==0)
                        {
                            fprintf(fp3,"Duplicate token at line %d\n",k);
                        }
                    }
                    else if(strcmp(ar,pre)==0)
                    {
                        fprintf(fp3,"%Duplicate token at line %d\n",k);
                    }
                    strcpy(c[k][pt++],ar);

                }
                else if(keyword(ar, 1)==1)
                {
                    fprintf(fp2,"kw %s ",ar);
                    if(strcmp(ar,"if")==0)
                    {
                        isIf  = 1;
                        semicolonIf = 0;
                    }
                    else if(strcmp(ar,"else")==0)
                    {
                        if(isIf==0 || semicolonIf!=1)
                        {
                            fprintf(fp3,"'else' without a previous 'if' at line %d\n",k);
                        }
                        else isIf  = 0;
                    }
                    else if(strcmp(ar,"for")==0)
                    {
                        forloop = 1;
                    }
                    if(strcmp(ar,pre)==0)
                    {
                        fprintf(fp3,"Duplicate token at line %d\n",k);
                    }
                    strcpy(c[k][pt++],ar);

                }
                else if(identifier(ar, 1)==1)
                {

                    fprintf(fp2,"id %s ",ar);
                    if(strcmp(ar,pre)==0)
                    {
                        fprintf(fp3,"Duplicate token at line %d\n",k);
                    }
                    strcpy(c[k][pt++],"id");
                    strcpy(c[k][pt++],ar);
                }
                else if(operators(ar, 1)==1)
                {
                    fprintf(fp2,"op %s ",ar);
                    strcpy(c[k][pt++],ar);
                }
                else if(parentheses(ar, 1)==3)
                {
                    fprintf(fp2,"par %s ",ar);
                    if(strcmp(ar,"(")==0)
                    {
                        fb++;
                        if(forloop==1)
                            forloop++;
                    }
                    else
                    {
                        if(forloop>0 && forloop<4)
                        {
                            fprintf(fp3,"Expected ; in for loop at line %d\n",k);
                        }
                        else if(fb==0)
                            fprintf(fp3,"Misplaced ) at line %d\n",k);
                        else
                        {
                            fb--;
                            if(forloop>0)
                                forloop = 0;
                        }
                    }
                    strcpy(c[k][pt++],ar);

                }
                else if(parentheses(ar, 1)==2)
                {
                    fprintf(fp2,"brc %s ",ar);
                    if(strcmp(ar,"{")==0)
                        sb++;
                    else
                    {

                        if(sb==0)
                            fprintf(fp3,"Misplaced } at line %d\n",k);
                        else sb--;
                    }
                    strcpy(c[k][pt++],ar);
                }
                else if(number(ar, 1)==1)
                {
                    fprintf(fp2,"num %s ",ar);
                    strcpy(c[k][pt++],ar);
                }
                else
                {
                    fprintf(fp2,"unkn %s ",ar);
                    fprintf(fp3,"Undeclared/Unknown %s at line %d\n",ar,k);
                    strcpy(c[k][pt++],ar);
                }
                j= 0;
                strcpy(pre,ar);
            }
            else
            {
                ar[j++]  = br[i];
            }

        }
        fprintf(fp2,"\n");
        sz[k] =  pt;
    }
    if(sb>0)
        fprintf(fp3,"Expected } at line %d\n",k-1);
    if(fb>0)
        fprintf(fp3,"Expected ) at line %d\n",k-1);



    //duplicate/no declaration assignment 3
    int it = 0;
    char * scope = "global";
    for(k=1; k<totalsz; k++)
    {
        for(i=0; i<sz[k]; i++)
        {
            if(strcmp(c[k][i],"id")==0)
            {
                if(strcmp(c[k][i+2],"(")==0)
                {
                    if(strcmp(c[k][i-1],"int")==0 || strcmp(c[k][i-1],"double")==0 || strcmp(c[k][i-1],"float")==0 || strcmp(c[k][i-1],"char")==0 || strcmp(c[k][i-1],"void")==0)
                    {
                        inde[it++]  = cur;
                        insert(cur++,c[k][i+1],"func",c[k][i-1],scope,"");
                        scope = c[k][i+1];
                        i+= 2;
                    }
                    else
                    {
                        int pq  = search(c[k][i+1],"func","global");
                        if(pq!=-1)
                            inde[it++] = pq;
                        else fprintf(fp3,"Expected declaration of function %s at line %d\n",c[k][i+1],k);
                        i+= 2;
                    }
                }
                else if(strcmp(c[k][i+2],"=")==0)
                {
                    if(strcmp(c[k][i-1],"int")==0 || strcmp(c[k][i-1],"double")==0 || strcmp(c[k][i-1],"float")==0 || strcmp(c[k][i-1],"char")==0 )
                    {
                        if(search(c[k][i+1],"var",scope)==-1)
                        {
                            inde[it++]  = cur;
                            insert(cur++,c[k][i+1],"var",c[k][i-1],scope,modify(c[k][i+3]));
                        }
                        else
                        {
                            fprintf(fp3,"ID %s at line %d already declared in %s scope\n",c[k][i+1],k,scope);
                        }
                    }
                    else
                    {
                        int pq = search(c[k][i+1],"var",scope);
                        if(pq==-1)
                        {
                            fprintf(fp3,"Expected declaration of %s at line %d\n",c[k][i+1],k);
                        }
                        else
                        {
                            update(pq,modify(c[k][i+3]));
                            inde[it++]  = pq;
                        }
                    }
                    i+=2;
                }
                else if(strcmp(c[k][i+2],";")==0 || strcmp(c[k][i+2],",")==0 || strcmp(c[k][i+2],")")==0 )
                {
                    if(strcmp(c[k][i-1],"int")==0 || strcmp(c[k][i-1],"double")==0 || strcmp(c[k][i-1],"float")==0 || strcmp(c[k][i-1],"char")==0 )
                    {
                        if(search(c[k][i+1],"var",scope)==-1)
                        {
                            inde[it++]  = cur;
                            insert(cur++,c[k][i+1],"var",c[k][i-1],scope,"");
                        }
                        else fprintf(fp3,"ID %s at line %d already declared in %s scope\n",c[k][i+1],k,scope);
                        i+= 2;
                    }
                    else
                    {
                        if(search(c[k][i+1],"var",scope)==-1)
                        {
                            fprintf(fp3,"Expected declaration of %s at line %d\n",c[k][i+1],k);
                        }
                        else inde[it++]  = search(c[k][i+1],"var",scope);
                        i+= 2;
                    }
                }
            }
            else if(strcmp(c[k][i],"}")==0)
            {
                scope = "global";
            }
        }
    }
}

int main(void)
{
    input();
    comment_newline_remove();
    extra_space_remove("comments_and_newline_removed.txt");
    tokenize();
    onlyIdentifier();
    symbolTable();
    error();
    //output("tokenized_all.txt");
}

