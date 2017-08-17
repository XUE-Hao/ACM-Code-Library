/*
 * 强连通分量分解Kosaraju算法
 * 时间复杂度O(V+E)
 * 下标从0开始
 */
#include <vector>
using namespace std;

const int MAXV=10000+3;

int V;//顶点数
vector<int> G[MAXV];//图的邻接表表示
vector<int> rG[MAXV];//把边反向后的图
vector<int> vs;//后序遍历的顶点列表
bool used[MAXV];//访问标记
int belong[MAXV];//所属强连通分量的拓扑排序

void add_edge(int from, int to)
{
    G[from].push_back(to);
    rG[to].push_back(from);
}

void dfs(int u)//正向dfs
{
    used[u]=true;
    for(int i=0;i<G[u].size();++i)
        if(!used[G[u][i]])
            dfs(G[u][i]);
    vs.push_back(u);
}

void rdfs(int u, int k)//反向dfs
{
    used[u]=true;
    belong[u]=k;
    for(int i=0;i<rG[u].size();++i)
        if(!used[rG[u][i]])
            rdfs(rG[u][i], k);
}

int scc()//返回强连通分量的个数
{
    for(int i=0;i<V;++i)
        used[i]=false;
    vs.clear();
    for(int u=0;u<V;++u)
        if(!used[u])
            dfs(u);
    for(int i=0;i<V;++i)
        used[i]=false;
    int k=0;
    for(int i=vs.size()-1;i>=0;--i)
        if(!used[vs[i]])
            rdfs(vs[i], k++);
    return k;
}
