/*
 * 单源最短路SPFA(也可以判是否有负环)
 * 时间复杂度 O (kE)
 * 这个是队列实现，有时候改成栈实现会更快，很容易修改
 * 这个复杂度是不定的
 * 能够自动处理重边，负边，不需要额外处理
 * 不判负环时不需要返回值，不需要数组cnt，不需要参数n
 */

#include <string.h>
#include <queue>
#include <vector>
using namespace std;
#define INF 0x3f3f3f3f

struct Edge
{
    int to,cost;
    Edge(int t,int c):to(t),cost(c){}
};

const int MAXV=1000+5;//最多顶点数，根据题意修改
vector<Edge> G[MAXV];//用邻接表存边(G[v]是以v为起点的各个边的vector)，输入时用G[from].push_back(Edge(to,cost))
bool vis[MAXV];//在队列标志
int cnt[MAXV];//每个点的入队列次数
int dist[MAXV];//储存从起点到各个边的最短距离
int V;//顶点数

bool spfa(int start)//起点
{
    for(int i=0;i<=V;++i)
    {
        vis[i]=false;
        dist[i]=INF;
        cnt[i]=0;
    }
    vis[start]=true;
    dist[start]=0;
    queue<int> que;
    que.push(start);
    cnt[start]=1;
    while(!que.empty())
    {
        int u=que.front();
        que.pop();
        vis[u]=false;
        for(int i=0;i<G[u].size();++i)
        {
            int v=G[u][i].to;
            if(dist[v]>dist[u]+G[u][i].cost)
            {
                dist[v]=dist[u]+G[u][i].cost;
                if(!vis[v])
                {
                    vis[v]=true;
                    que.push(v);
                    if(++cnt[v]>V)//cnt[i]为入队列次数，用来判定是否存在负环回路
                        return false;
                }
            }
        }
    }
    return true;
}
