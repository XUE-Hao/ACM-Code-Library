/*
 * LCA 离线Tarjan算法
 * 复杂度O(V+Q)
 * 下标从1开始
 */
#include <vector>
using namespace std;
#define mem(a,b) memset((a),(b),sizeof(a))

const int MAXV=900+3;//最大结点数，根据题意修改
const int MAXQ=500000+3;//最大查询数，根据题意修改

struct Query
{
    int q;
    int id;//查询编号
    Query(int q, int i):q(q), id(i){}
};

vector<int> G[MAXV];//有向树的邻接表表示
int par[MAXV];//并查集父亲结点
bool vis[MAXV];
int ancestor[MAXV];//祖先
int answer[MAXQ];//存储最后的查询结果，下标0~Q-1
vector<Query> query[MAXV];//与当前结点关联的查询的邻接表
int V, Q;//结点数，查询数

int findfather(int x)
{
    return par[x]=par[x]==x?x:findfather(par[x]);
}

void unite(int u, int v)//定向合并
{
    int fa=findfather(u), fb=findfather(v);
    if(fa!=fb)
        par[fa]=fb;
}

void add_query(int u, int v, int id)//添加查询
{
    query[u].push_back(Query(v, id));
    query[v].push_back(Query(u, id));
}

void lca_init()//调用lca()前使用
{
    for(int i=0;i<=V;++i)
    {
        vis[i]=false;
        par[i]=i;
        query[i].clear();
    }
}

void lca(int u)//调用时传入根节点
{
    ancestor[u]=u;
    vis[u]=true;
    for(int i=0;i<G[u].size();++i)
    {
        int v=G[u][i];
        if(vis[v])
            continue;
        lca(v);
        unite(u, v);
        ancestor[findfather(u)]=u;
    }
    for(int i=0;i<query[u].size();++i)
    {
        int v=query[u][i].q;
        if(vis[v])
            answer[query[u][i].id]=ancestor[findfather(v)];
    }
}
