/*
 * 使用优先队列优化的Dijkstra算法
 * 复杂度O(E log E)
 * 注意对vector<Edge> G[MAXV]进行初始化后加边
 * 下标从0开始
 */
#include <cstdio>
#include <vector>
#include <queue>
using namespace std;
#define INF 0x3f3f3f3f

const int MAXV=200+3;//图的最大结点数，根据题意修改

struct Node//候选构成最路的点
{
    int u, c;
    Node(int u, int c):u(u), c(c){}
    bool operator<(const Node &other)const
    {
        return c>other.c;//为了使最短的在优先队列中先出来
    }
};

struct Edge//边
{
    int to, cost;
    Edge(int t=0, int c=0):to(t), cost(c){}
};

vector<Edge> G[MAXV];//图的邻接表表示
bool vis[MAXV];//访问标记
int dist[MAXV];//从起点到当前点的最短路径

void dijkstra(int n, int s)//节点数，起点
{
    for(int i=0;i<n;++i)
    {
        vis[i]=false;
        dist[i]=INF;
    }
    priority_queue<Node> que;//使用优先队列优化
    dist[s]=0;
    que.push(Node(s, 0));
    while(!que.empty())
    {
        Node tmp=que.top(); que.pop();
        int u=tmp.u;
        if(vis[u])
            continue;
        vis[u]=true;
        for(int i=0;i<G[u].size();++i)
        {
            int v=G[u][i].to;
            if(!vis[v] && dist[v]>dist[u]+G[u][i].cost)
            {
                dist[v]=dist[u]+G[u][i].cost;
                que.push(Node(v, dist[v]));
            }
        }
    }
}
