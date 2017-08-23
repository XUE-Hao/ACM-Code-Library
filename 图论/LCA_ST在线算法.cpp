/*
 * LCA dfs+ST在线算法
 * 预处理O(V * log V)
 * 查询O(1)
 * 下标从1开始
 */
#include <vector>
using namespace std;

const int MAXV=10000+3;//最大结点数，根据题意修改
int depth[2*MAXV];//depth数组，就是dfs序列对应的深度序列

struct ST//ST表
{
    int save_k[2*MAXV];//保存任意长度所在的层数
    int dp[20][2*MAXV];
    void init(int n)
    {
        save_k[0]=-1;
        for(int i=1;i<=n;++i)
        {
            save_k[i]=((i&(i-1))==0)?save_k[i-1]+1:save_k[i-1];
            dp[0][i]=i;
        }
        for(int j=1;j<=save_k[n];++j)
            for(int i=1;i+(1<<j)-1<=n;++i)
                dp[j][i]=depth[dp[j-1][i]]<depth[dp[j-1][i+(1<<(j-1))]]?dp[j-1][i]:dp[j-1][i+(1<<(j-1))];
    }
    int query(int l, int r)
    {
        int k=save_k[r-l+1];
        return depth[dp[k][l]]<=depth[dp[k][r-(1<<k)+1]]?dp[k][l]:dp[k][r-(1<<k)+1];
    }
}st;

vector<int> G[MAXV];//有向树的邻接表表示
int order[MAXV*2];//dfs序列，就是dfs遍历的顺序，长度为2*n-1，下标从1开始
int pos[MAXV];//pos[i]表示点i在order中第一次出现的位置 
int cnt;
int V;

void dfs(int u, int fa, int deep)
{
    order[++cnt]=u;
    depth[cnt]=deep;
    pos[u]=cnt;
    for(int i=0;i<G[u].size();++i)
    {
        int v=G[u][i];
        if(v==fa)
            continue;
        dfs(v, u, deep+1);
        order[++cnt]=u;
        depth[cnt]=deep;
    }
}

void lca_init(int root, int node_num)//查询lca前初始化
{
    cnt=0;
    dfs(root, root, 0);
    st.init(2*node_num-1);
}

int query_lca(int u, int v)//查询u, v的lca编号
{
    if(pos[u]>pos[v])//st表的查询要求左短点一定要小于等于右端点
        swap(u, v);
    return order[st.query(pos[u], pos[v])];
}
