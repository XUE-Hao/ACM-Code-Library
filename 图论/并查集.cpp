#include<stdio.h>

const int maxn=50005;//原始个数,需要根据题目要求修改
int par[maxn];//父亲
int rank[maxn];//树的高度

void init(int n)//初始化n个元素
{
    for(int i=1;i<=n;++i)//元素从1到n
    {
        par[i]=i;
        rank[i]=0;
    }
}
int findfather(int x)//查询数的根
{
    return par[x]==x?x:par[x]=findfather(par[x]);
}
void unite(int x,int y)//合并x和y所属的集合
{
    x=findfather(x);
    y=findfather(y);
    if(x==y)
        return;
    if(rank[x]<rank[y])
    {
        par[x]=y;
    }
    else
    {
        par[y]=x;
        if(rank[x]==rank[y])
            rank[x]++;
    }
}
bool same(int x,int y)
{
    return findfather(x)==findfather(y);
}
