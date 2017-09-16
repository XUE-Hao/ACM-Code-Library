/*
 * 最小费用最大流Dijkstra寻找增广路
 * 时间复杂度 O(F * E * log V)
 * 需要在运行前设置好V和G
 */
#include <algorithm>
#include <vector>
#include <queue>
using namespace std;
#define INF 0x3f3f3f3f
#define fi first
#define se second
#define P pair<int,int>

const int MAXV=1000+3;//最大结点数，根据题意修改

struct Edge//用于表示边的结构体（终点，容量，费用，反向边）
{
    int to, cap, cost, rev;
    Edge(int t, int ca, int co, int r):to(t), cap(ca), cost(co), rev(r){}
};

int V;//顶点数
vector<Edge> G[MAXV];//图的邻接表表示
int h[MAXV];//顶点的势
int dist[MAXV];//最短距离
int prevv[MAXV], preve[MAXV];//最短路中的前驱节点和对应的边
priority_queue< P, vector< P >, greater< P > > que;//first保存最短路径，second保存顶点编号

void add_edge(int from, int to, int cap, int cost)//向图中添加一条从from到to容量为cap费用为cost的边
{
    G[from].push_back(Edge(to, cap, cost, G[to].size()));
    G[to].push_back(Edge(from, 0, -cost, G[from].size()-1));
}

int min_cost_flow(int s, int t, int &cost)//求解从s到t的最小费用最大流，返回流量，花费保存在cost中
{
    cost=0;
    int f=0;
    fill(h, h+V, 0);//初始化h
    while(true)
    {
        //使用Dijkstra算法更新h
        while(!que.empty())
            que.pop();
        fill(dist, dist+V, INF);
        dist[s]=0;
        que.push(P(0, s));
        while(!que.empty())
        {
            P p=que.top(); que.pop();
            int u=p.se;
            if(dist[u]<p.fi)
                continue;
            for(int i=0;i<G[u].size();++i)
            {
                Edge &e=G[u][i];
                if(e.cap>0 && dist[e.to]>dist[u]+e.cost+h[u]-h[e.to])
                {
                    dist[e.to]=dist[u]+e.cost+h[u]-h[e.to];
                    prevv[e.to]=u;
                    preve[e.to]=i;
                    que.push(P(dist[e.to], e.to));
                }
            }
        }
        if(dist[t]==INF)//不能再增广
            return f;
        for(int u=0;u<V;++u)
            h[u]+=dist[u];
        //沿s到t的最短路尽量增广
        int d=INF;
        for(int u=t;u!=s;u=prevv[u])
            d=min(d, G[prevv[u]][preve[u]].cap);
        f+=d;
        cost+=d*h[t];
        for(int u=t;u!=s;u=prevv[u])
        {
            Edge &e=G[prevv[u]][preve[u]];
            e.cap-=d;
            G[u][e.rev].cap+=d;
        }
    }
    return f;
}
