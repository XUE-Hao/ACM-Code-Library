#include<ctype.h>
#include<stdio.h>

inline int readint()
{
    char c=getchar();
    while(!isdigit(c))
        c=getchar();

    int x=0;
    while(isdigit(c))
    {
        x=x*10+c-'0';
        c=getchar();
    }
    return x;
}

void Out(int a)
{
     if(a>9)
         Out(a/10);
     putchar(a%10+'0');
}
