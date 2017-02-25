/*
 *以SPFA为基础的最小费用最大流算法
 *O(F*E*k)
 *求最大费用只需要取相反数，结果取反即可
 */
#include <queue>
#include <algorithm>
using namespace std;
#define INF 0x3f3f3f3f
#define mem(a,b) memset((a),(b),sizeof(a))

const int MAXV=100;//最大顶点数（根据题意修改）
const int MAXE=MAXV*MAXV;//最大边数（根据题意修改）

struct Edge
{
    int to,next,cap,cost;
    Edge(int t=0,int n=0,int ca=0,int f=0,int co=0):to(t),next(n),cap(ca),cost(co){}
}edge[MAXE];

int head[MAXV],tol;
int pre[MAXV],dis[MAXV];
bool vis[MAXV];
int V;//节点总个数，节点编号从0~V-1

void init(int n)
{
    V=n;
    tol=0;
    mem(head,-1);
}

void add_edge(int u,int v,int cap,int cost)
{
    edge[tol]=Edge(v,head[u],cap,0,cost);
    head[u]=tol++;
    edge[tol]=Edge(u,head[v],0,0,-cost);
    head[v]=tol++;
}

bool spfa(int s,int t)
{
    queue<int> que;
    for(int i=0;i<V;++i)
    {
        dis[i]=INF;
        vis[i]=false;
        pre[i]=-1;
    }
    dis[s]=0;
    vis[s]=true;
    que.push(s);
    while(!que.empty())
    {
        int u=que.front(); que.pop();
        vis[u]=false;
        for(int i=head[u];i!=-1;i=edge[i].next)
        {
            int v=edge[i].to;
            if(edge[i].cap>0&&dis[v]>dis[u]+edge[i].cost)
            {
                dis[v]=dis[u]+edge[i].cost;
                pre[v]=i;
                if(!vis[v])
                {
                    vis[v]=true;
                    que.push(v);
                }
            }
        }
    }
    return pre[t]!=-1;
}

int min_cost_flow(int s,int t,int &cost)//返回的是最大流，cost存的是最小费用
{
    int flow=0;
    cost=0;
    while(spfa(s,t))
    {
        int the_min=INF;
        for(int i=pre[t];i!=-1;i=pre[edge[i^1].to])
            the_min=min(the_min,edge[i].cap);
        for(int i=pre[t];i!=-1;i=pre[edge[i^1].to])
        {
            edge[i].cap-=the_min;
            edge[i^1].cap+=the_min;
            cost+=edge[i].cost*the_min;
        }
        flow+=the_min;
    }
    return flow;
}
