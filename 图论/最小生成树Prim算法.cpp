#include<stdio.h>
#define Min(a,b) (a<b?a:b)

const int INF=0x3f3f3f3f;
const int maxn=105;//maxn需要根据题目要求修改
int cost[maxn][maxn];//cost[u][v]表示e=(u,v)的权值(不存在的情况下设为INF)
int mincost[maxn];//从集合X发出的边到每个顶点的最小权值
bool used[maxn];//顶点i是否包含在集合X中
int V;//定点数

int prim()//定点是从1到V
{
    for(int i=1;i<=V;++i)
    {
        mincost[i]=INF;
        used[i]=false;
    }
    mincost[1]=0;
    int res=0;
    while(true)
    {
        int v=-1;
        //从不属于X的顶点中选取从X到其权值最小的顶点
        for(int u=1;u<=V;++u)
        {
            if(!used[u]&&(v==-1||mincost[u]<mincost[v]))
                v=u;
        }
        if(v==-1)
            break;
        used[v]=true;//把定点v加入X
        res+=mincost[v];//把边的长度加入到结果里
        for(int u=1;u<=V;++u)
        {
            mincost[u]=Min(mincost[u],cost[v][u]);
        }
    }
    return res;
}
