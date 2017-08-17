/*
 * 最小树形图_朱刘算法
 * 时间复杂度O(VE)
 * 下标从0开始
 * 无法直接通过修改次模板使得字典序最小
 */
#include <vector>
using namespace std;
#define INF 0x3f3f3f3f

const int MAXV=100+3;//最大顶点数，根据题意修改
const int MAXE=10000+3;//最大边数，根据题意修改

struct Edge
{
    int u,v;
    int cost;
}edge[MAXE];//边集

int V,E;//顶点数，边数
int pre[MAXV],id[MAXV],vis[MAXV];
int in[MAXV];

int zhuliu(int root)//返回最小花费
{
    int res=0;
    while(true)
    {
        for(int i=0;i<V;++i)
            in[i]=INF;
        for(int i=0;i<E;++i)
            if(edge[i].u!=edge[i].v&&edge[i].cost<in[edge[i].v])
            {
                pre[edge[i].v]=edge[i].u;
                in[edge[i].v]=edge[i].cost;
            }
        for(int i=0;i<V;++i)
            if(i!=root&&in[i]==INF)
                return -1;//不存在最小树形图
        int tn=0;//新图结点数
        for(int i=0;i<V;++i)
        {
            id[i]=-1;
            vis[i]=-1;
        }
        in[root]=0;
        for(int i=0;i<V;++i)
        {
            res+=in[i];
            int v=i;
            while(vis[v]!=i&&id[v]==-1&&v!=root)
            {
                vis[v]=i;
                v=pre[v];
            }
            if(v!=root&&id[v]==-1)
            {
                for(int u=pre[v];u!=v;u=pre[u])
                    id[u]=tn;
                id[v]=tn++;
            }
        }
        if(tn==0)//没有有向环
            break;
        for(int i=0;i<V;++i)
            if(id[i]==-1)
                id[i]=tn++;
        for(int i=0;i<E;)
        {
            int v=edge[i].v;
            edge[i].u=id[edge[i].u];
            edge[i].v=id[edge[i].v];
            if(edge[i].u!=edge[i].v)
                edge[i++].cost-=in[v];
            else swap(edge[i],edge[--E]);
        }
        V=tn;
        root=id[root];
    }
    return res;
}
