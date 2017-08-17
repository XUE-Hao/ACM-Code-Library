/*
 * 一般图匹配带花树
 * 时间复杂度 O(V^3)
 */
#include <cstring>
using namespace std;
#define mem(a,b) memset((a),(b),sizeof(a))

const int MAXV=222+3;//最大结点数，
int V;//点的个数，点的编号从1到V
bool G[MAXV][MAXV];//图的邻接矩阵
int match[MAXV];//每个点匹配的点的编号
bool inqueue[MAXV],inpath[MAXV],inblossom[MAXV];
int  head,tail;
int queue[MAXV];
int start,finish;
int newbase;
int father[MAXV],base[MAXV];
int Count;//匹配数，匹配对数是Count/2

void Push(int u)
{
    queue[tail]=u;
    ++tail;
    inqueue[u]=true;
}

int Pop()
{
    int res=queue[head];
    head++;
    return res;
}

int findCommonAncestor(int u,int v)
{
    mem(inpath,0);
    while(true)
    {
        u=base[u];
        inpath[u]=true;
        if(u==start)
            break;
        u=father[match[u]];
    }
    while(true)
    {
        v=base[v];
        if(inpath[v])
            break;
        v=father[match[v]];
    }
    return v;
}

void resetTrace(int u)
{
    int v;
    while(base[u]!=newbase)
    {
        v=match[u];
        inblossom[base[u]]=inblossom[base[v]]=true;
        u=father[v];
        if(base[u]!=newbase)
            father[u]=v;
    }
}

void bloosomContract(int u,int v)
{
    newbase=findCommonAncestor(u,v);
    mem(inblossom,0);
    resetTrace(u);
    resetTrace(v);
    if(base[u]!=newbase)
        father[u]=v;
    if(base[v]!=newbase)
        father[v]=u;
    for(int tu=1;tu<=V;++tu)
        if(inblossom[base[tu]])
        {
            base[tu]=newbase;
            if(!inqueue[tu])
                Push(tu);
        }
}

void findAugmentingPath()
{
    mem(inqueue,0);
    mem(father,0);
    for(int i=1;i<=V;++i)
        base[i]=i;
    head=tail=1;
    Push(start);
    finish=0;
    while(head<tail)
    {
        int u=Pop();
        for(int v=1;v<=V;++v)
            if(G[u][v]&&(base[u]!=base[v])&&(match[u]!=v))
            {
                if((v==start)||((match[v]>0)&&father[match[v]]>0))
                    bloosomContract(u,v);
                else if(father[v]==0)
                {
                    father[v]=u;
                    if(match[v]>0)
                        Push(match[v]);
                    else
                    {
                        finish=v;
                        return ;
                    }
                    
                }
            }
    }
}

void augmentPath()
{
    int u,v,w;
    u=finish;
    while(u>0)
    {
        v=father[u];
        w=match[v];
        match[v]=u;
        match[u]=v;
        u=w;
    }
}

void edmonds()//匹配
{
    mem(match,0);
    for(int u=1;u<=V;++u)
        if(match[u]==0)
        {
            start=u;
            findAugmentingPath();
            if(finish>0)
                augmentPath();
        }
    Count=0;
    for(int u=1;u<=V;++u)
        if(match[u]>0)
            ++Count;
}
