/*
 * LCA 倍增算法
 * 在线查询
 * 下标从0开始
 * 预处理 O(V * log V)
 * 查询 O(log V)
 */
#include <vector>
using namespace std;

const int MAXV=10000+3;//最大结点数
const int MAXD=15;//最大层数，log(MAXV)
vector<int> G[MAXV];//图的邻接表表示
int parent[MAXD][MAXV];//向上走2^k步所到的节点（超过根时记为-1）
int depth[MAXV];//结点的深度

void dfs(int u, int fa, int d)
{
    parent[0][u]=fa;
    depth[u]=d;
    for(int i=0;i<G[u].size();++i)
        if(G[u][i]!=fa)
            dfs(G[u][i], u, d+1);
}

void lca_init(int V, int root)//预处理
{
    //预处理出parent[0]和depth
    dfs(root, -1, 0);
    //预处理出parent
    for(int k=0;k+1<MAXD;++k)
        for(int u=0;u<V;++u)
            if(parent[k][u]<0)
                parent[k+1][u]=-1;
            else parent[k+1][u]=parent[k][parent[k][u]];
}

int lca(int u, int v)//计算u和v的LCA
{
    //让u和v向上走到同一深度
    if(depth[u]>depth[v])
        swap(u, v);
    for(int k=0;k<MAXD;++k)
        if((depth[v]-depth[u])>>k&1)
            v=parent[k][v];
    if(u==v)
        return u;
    //利用二分搜索计算LCA
    for(int k=MAXD-1;k>=0;--k)
        if(parent[k][u]!=parent[k][v])
        {
            u=parent[k][u];
            v=parent[k][v];
        }
    return parent[0][u];
}
