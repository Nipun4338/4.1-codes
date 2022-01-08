#include<stdio.h>
char *cd[100000];
FILE *p1;

int check(char *cd)
{
    int flag=0, found=0, count=0;
    for(int i=0; i<strlen(cd); i++)
    {
        if(i==0 && cd[i]!='c')
        {
            return flag=1;
        }
        else if(i==0 && cd[i]=='c')
        {
            continue;
        }
        else if(i>0 && cd[i]>='a' && cd[i]<='z')
        {
            continue;
        }
        else if(i>0 && cd[i]=='_' && !found)
        {
            found=1;
            continue;
        }
        else if(i>0 && cd[i]>='0' && cd[i]<='9' && found)
        {
            count++;
        }
        else
        {
            return flag=1;
        }
    }
    if(count>=2)
    {
        return flag=0;
    }
    else
    {
        return flag=1;
    }
}

int main()
{
    printf("Input String: ");
    scanf("%s", &cd);
    int a=check(cd);
    if(a)
    {
        printf("String doesn't follows the pattern.\n");
    }
    else
    {
        printf("String follows the pattern.\n");
    }
}
