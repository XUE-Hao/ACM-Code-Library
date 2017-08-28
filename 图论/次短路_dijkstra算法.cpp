/*
 * 堆优化dijkstra算法求解次短路
 * 下标从0开始
 * 如果有多条最短路，则次短路是其中一条最短路
 */
#include <vector>
#include <queue>
using namespace std;
#define INF 0x3f3f3f3f
#define LL long long
#define fi first
#define se second
#define P pair<int,int>

const int MAXV=100000+3;//最大顶点数，根据题意修改

struct Edge//边
{
    int to, cost;
    Edge(int t, int c):to(t), cost(c){}
};

int V;//结点数
vector<Edge> G[MAXV];//图的邻接表表示
int dist[2][MAXV];//最短距离，次短距离
priority_queue<P, vector<P>, greater<P> > que;//保存待确定点：距离，结点编号

void dij()
{
    fill(dist[0], dist[0]+V, INF);
    fill(dist[1], dist[1]+V, INF);
    while(!que.empty())
        que.pop();
    dist[0][0]=0;
    que.push(P(0, 0));
    while(!que.empty())
    {
        P p=que.top(); que.pop();
        int u=p.se, d=p.fi;
        if(dist[1][u]<d)
            continue;
        for(int i=0;i<G[u].size();i++)
        {
            Edge &e=G[u][i];
            int d2=d+e.cost;
            if(dist[0][e.to]>d2)//更新最短距离
            {
                swap(dist[0][e.to], d2);
                que.push(P(dist[0][e.to], e.to));
            }
            if(dist[1][e.to]>d2&&dist[0][u]<d2)//更新次短距离
            {
                dist[1][e.to]=d2;
                que.push(P(dist[1][e.to], e.to));
            }
        }
    }
}
