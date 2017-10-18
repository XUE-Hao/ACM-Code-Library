/*
 * 最大流 Dinic算法
 * 时间复杂度 O(V^2 *E)
 * 下标从0开始
 * 调用dinid函数前，要设定G和V
 */
#include <vector>
#include <queue>
using namespace std;
#define INF 0x3f3f3f3f

const int MAXV=20000+3;//最大结点数，根据题意修改

struct Edge
{
    int to, cap, rev;
    Edge(int t, int c, int r):to(t), cap(c), rev(r){}
};

vector<Edge> G[MAXV];//图的邻接表表示
int level[MAXV];//顶点到原点的距离标号
int iter[MAXV];//当前弧，在其之前的边已经没有用了
int V;//顶点数

//有向图中增加一条从from到to的容量为cap的边
void add_edge(int from, int to, int cap)
{
    G[from].push_back(Edge(to, cap, G[to].size()));
    G[to].push_back(Edge(from, 0, G[from].size()-1));
}

//通过bfs计算从源点出发的距离标号
void bfs(int s)
{
    for(int i=0;i<V;++i)
        level[i]=-1;
    queue<int> que;
    level[s]=0;
    que.push(s);
    while(!que.empty())
    {
        int u=que.front(); que.pop();
        for(int i=0;i<G[u].size();++i)
        {
            Edge &e=G[u][i];
            if(e.cap>0 && level[e.to]<0)
            {
                level[e.to]=level[u]+1;
                que.push(e.to);
            }
        }
    }
}

//通过dfs寻找增广路
int dfs(int u, int t, int f)
{
    if(u==t)
        return f;
    for(int &i=iter[u];i<G[u].size();++i)
    {
        Edge &e=G[u][i];
        if(e.cap>0 && level[u]<level[e.to])
        {
            int d=dfs(e.to, t, min(f, e.cap));
            if(d>0)
            {
                e.cap-=d;
                G[e.to][e.rev].cap+=d;
                return d;
            }
        }
    }
    return 0;
}

//求解从s到t的最大流
int dinic(int s, int t)
{
    int flow=0;
    while(true)
    {
        bfs(s);
        if(level[t]<0)
            return flow;
        for(int i=0;i<V;++i)
            iter[i]=0;
        int f;
        while((f=dfs(s, t, INF))>0)
            flow+=f;
    }
}
