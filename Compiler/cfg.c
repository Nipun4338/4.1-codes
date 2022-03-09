#include<stdio.h>
#include<ctype.h>
#include <string.h>

char a[100000];
int f=0;

void input()
{
    scanf("%s", a);
}

void B(int i)
{
    if (a[i] == 'b')
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

int A(int i)
{
    if (a[i] == 'a')
    {
        i++;
        f=1;
    }
    else
    {
        if(i==strlen(a)-1)
        {
            return;
        }
        f=0;
        return i;
    }
    if (i<=strlen(a)-1)
    {
        A(i);
    }
}

void S()
{
    int i=0;
    if(a[i] == 'b')
    {
        i++;
        f=1;
        return;

    }
    else
    {
        i=A(i);
        if(f)
        {
            B(i);
            return;
        }
    }
}

int main()
{
    input();
    S();
    printf("%d\n", f);
}
