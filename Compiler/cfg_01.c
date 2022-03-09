#include<stdio.h>
#include<ctype.h>
#include <string.h>

char a[100000];
int f=0, i=0;

void input()
{
    scanf("%s", a);
}


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
        printf("String Not matched\n");
    }
}

/*A=aXd
A=abbXd
A=abcXd
A=abbd
A=abcd
A=abbbcd
A=abcbbd
A=ad*/
