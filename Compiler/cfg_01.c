#include<stdio.h>
#include<ctype.h>
#include <string.h>

char a[100000];
int f=0, i=0;

void input()
{
    scanf("%s", a);
}

///Task 2
void ID()
{
    if(i<strlen(a) && a[i]>='a' && a[i]<='e')
    {
        i++;
        f=1;
        return;
    }
    f=0;
    return;
}

void NUM()
{
    if(i<strlen(a) && a[i]>='0' && a[i]<='9')
    {
        i++;
        f=1;
        return;
    }
    f=0;
    return;
}

void Factor()
{
    ID();
    if(f==1)
    {
        return;
    }
    NUM();
    if(f==1)
    {
        return;
    }
    if(i<strlen(a) && a[i]=='(')
    {
        i++;
        Exp();
        if(f==1)
        {
            if(i<strlen(a) && a[i]==')')
            {
                i++;
                f=1;
                return;
            }
            f=0;
            return;
        }
        f=0;
        return;
    }
    f=0;
    return;
}

void Term()
{
    Factor();
    if(i==strlen(a) || f==0)
    {
        return;
    }
    if(a[i]=='*' || a[i]=='/')
    {
        i++;
        Factor();
    }
    printf("%d\n", i);
}

void Exp()
{
    Term();
    if(i==strlen(a) || f==0)
    {
        return;
    }
    if(a[i]=='+' || a[i]=='-')
    {
        i++;
        Term();
    }
}



///Task 3
void relop()
{
    if(i+1<strlen(a) && a[i]=='=' && a[i+1]=='=')
    {
        f=1;
        i+=2;
        return;
    }

    if(i+1<strlen(a) && a[i]=='!' && a[i+1]=='=')
    {
        f=1;
        i+=2;
        return;
    }
    if(i+1<strlen(a) && a[i]=='<' && a[i+1]=='=')
    {
        f=1;
        i+=2;
        return;
    }
    if(i+1<strlen(a) && a[i]=='>' && a[i+1]=='=')
    {
        f=1;
        i+=2;
        return;
    }
    if(i<strlen(a) && a[i]=='>')
    {
        f=1;
        i++;
        return;
    }
    if(i<strlen(a) && a[i]=='<')
    {
        f=1;
        i++;
        return;
    }
    f=0;
    return;
}

void extn()
{
    int temp=i;
    relop();
    if(f==1)
    {
        Exp();
        if(f==1)
        {
            return;
        }
    }
    i=temp;
    f=1;
    return;
}

void extn1()
{
    int temp = i;
    if(i+3<strlen(a) && a[i]=='e' && a[i+1]=='l' && a[i+2]=='s' && a[i+3]=='e')
    {
        i+=4;
        stat();
        if(f==1)
        {
            return;
        }

    }
    i=temp;
    f=1;
    return;
}

void expn()
{
    Exp();
    if(f==1)
    {
        extn();
        return;
    }
    return;
}

void loop_stat()
{
    int temp=i;
    if(i+5<strlen(a) && a[i]=='w' && a[i+1]=='h' && a[i+2]=='i' && a[i+3]=='l' && a[i+4]=='e' && a[i+5]=='(')
    {
        i+= 6;
        expn();
        if(f==1 && i<strlen(a) && a[i]==')')
        {
            i++;
            stat();
            if(f==1)
            {
                return;
            }
        }

    }
    i=temp;
    if(i+3<strlen(a) && a[i]=='f' && a[i+1]=='o' && a[i+2]=='r' && a[i+3]=='(')
    {
        i+=4;
        asgn_stat();
        if(f==1)
        {
            if(i<strlen(a) && a[i]==';')
            {
                i++;
                expn();
                if(f==1)
                {
                    if(i<strlen(a) && a[i]==';')
                    {
                        i++;
                        asgn_stat();
                        if(i<strlen(a) && a[i]==')')
                        {
                            i++;
                            stat();
                            if(f==1)
                            {
                                return;
                            }
                        }
                    }
                }
            }
        }

    }
    f=0;
    return;
}

void dscn_stat()
{
    if(i+2<strlen(a) && a[i]=='i' && a[i+1]=='f' && a[i+2]=='(')
    {
        i+=3;
        expn();
        if(f==1)
        {
            if(i<strlen(a) && a[i]==')')
            {
                i++;
                stat();
                if(f==1)
                {
                    extn1();
                    return;
                }
                else
                {
                    return;
                }
            }
            else
            {
                f=0;
                return;
            }
        }
        else
        {
            return;
        }
    }
    f=0;
    return;
}

void asgn_stat()
{
    ID();
    if(f==1)
    {
        if(i<strlen(a) && a[i]=='=')
        {
            i++;
            expn();
            return;

        }
        f=0;
        return;
    }
    return;
}

void stat(int i)
{
    int temp=i;
    asgn_stat();
    if(f==1)
    {
        return;
    }
    i=temp;
    dscn_stat();
    if(f==1)
    {
        return;
    }
    i=temp;
    loop_stat();
    if(f==1)
    {
        return;
    }
    f=0;
    return;
}



///Task 1
void B(int i)
{
    if (a[i] == 'd')
    {
        i++;
        f=1;
        return;
    }
    else
    {
        f=0;
        return;
    }
}

int A(int i, int x)
{
    if (a[i] == 'b')
    {
        i++;
        x++;
        if(x==2)
        {
            f=1;
            x=0;
        }
        else
        {
            f=0;
        }
    }
    else if (a[i] == 'c')
    {
        i++;
        //printf("%d\n", x);
        if(x==1)
        {
            //printf("%d\n", f);
            f=1;
            x=0;
        }
        else
        {
            f=0;
        }
    }
    else
    {
        //printf("%d\n", f);
        if(i==strlen(a)-1)
        {
            return;
        }
        f=0;
        return i;
    }
    if (i<=strlen(a)-1)
    {
        A(i, x);
    }
}

void S()
{
    int i=0;
    if(a[i] == 'a')
    {
        i++;
        f=1;
    }
    if(f)
    {
        i=A(i, 0);
        if(f)
        {
            B(i);
            return;
        }
    }
    else
    {
        return;
    }
}

int main()
{
    input();
    /*S();
    if(f)
    {
        printf("String Matched!\n");
    }
    else
    {
        printf("String Not Matched!\n");
    }*/

    f=0;
    i=0;
    Exp(0);
    if(f==1 && i==strlen(a))
    {
        printf("String Matched!\n");
    }
    else
    {
        printf("String Not Matched!\n");
    }


    /*f=0;
    i=0;
    stat(0);
    if(f==1 && i==strlen(a))
    {
        printf("String Matched!\n");
    }
    else
    {
        printf("String Not Matched!\n");
    }*/
}

/*A=aXd
A=abbXd
A=abcXd
A=abbd
A=abcd
A=abbbcd
A=abcbbd
A=ad*/

/*
(1+2)-6
(1+2)**(3+4)*/

/*while(a==b)if(a==c)c=2elsec=3
for(a=b;b<c;d=a)if(a==c)c=2
if(a==b)c=2
if(a+b)c=5*/
