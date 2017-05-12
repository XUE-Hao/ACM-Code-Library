/*
 * 单源最短路SPFA(也可以判是否有负环)
 * 综合考率，最短路最佳算法
 * 时间复杂度 O (kE)
 * 这个是队列实现，有时候改成栈实现会更快，很容易修改
 * 这个复杂度是不定的
 * 能够自动处理重边，负边，不需要额外处理
 * 不判负环时不需要返回值，不需要数组cnt，不需要参数n
 */

#include <string.h>
#include <queue>//可以换成stack
#include <vector>
using namespace std;

struct Edge
{
    int to,cost;
    Edge(int t,int c):to(t),cost(c){}
};

const int MAXV=1000+5;//最多顶点数，根据题意修改
const int INF=0x3f3f3f3f;
vector<Edge> G[MAXV];//用邻接表存边(G[v]是以v为起点的各个边的vector)，输入时用G[from].push_back(Edge(to,cost))
bool vis[MAXV];//在队列标志
int cnt[MAXV];//每个点的入队列次数
int dist[MAXV];//储存从起点到各个边的最短距离

bool SPFA(int start,int n)//起点，总共点数
{
    memset(vis,false,sizeof vis);
    memset(dist,0x3f,sizeof dist);
    vis[start]=true;
    dist[start]=0;
    queue<int> que;
    que.push(start);
    memset(cnt,0,sizeof cnt);
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
                    if(++cnt[v]>n)//cnt[i]为入队列次数，用来判定是否存在负环回路
                        return false;
                }
            }
        }
    }
    return true;
}
