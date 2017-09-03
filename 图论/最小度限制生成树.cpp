/*
 * 无向图最小度限制生成树
 * 下标从1开始
 * O (E * log(E) + K * V)
 * 调用函数前，要将边存入edge数组，建立好邻接矩阵
 * 固定限制度数的结点为1号结点
 * 度数不超过K，如果要度数恰好为K，修改最后一部分即可
 * 最终结果保存在in_tree中
 */
#include <algorithm>
using namespace std;
#define INF 0x3f3f3f3f

const int MAXV=20+3;
const int MAXE=MAXV*MAXV;

struct Edge
{
    int from, to, cost;
    bool operator < (const Edge &other)const
    {
        return cost<other.cost;
    }
}edge[MAXE];//保存图中的所有边

int V, E, K;//结点数，边数，度数限制
int par[MAXV], high[MAXV];//并查集数组
int G[MAXV][MAXV];//图的邻接矩阵表示（没有边，花费为INF）
bool in_tree[MAXV][MAXV];//在生成树中标记
int the_min[MAXV];//连通块到特殊点的最近的边
Edge dp[MAXV];

int findfather(int x)
{
    return par[x]=par[x]==x?x:findfather(par[x]);
}

bool unite(int a, int b)//并查集合并
{
    int fa=findfather(a), fb=findfather(b);
    if(fa==fb)
        return false;
    if(high[fa]>high[fb])
        par[fb]=fa;
    else
    {
        par[fa]=fb;
        if(high[fa]==high[fb])
            ++high[fb];
    }
    return true;
}

void dfs(int u, int fa)
{
    for(int v=1;v<=V;++v)
        if(v!=fa && in_tree[u][v])
        {
            if(fa==-1)
                dp[v].cost=-INF;
            else
            {
                if(G[u][v]>dp[u].cost)
                {
                    dp[v].from=u;
                    dp[v].to=v;
                    dp[v].cost=G[u][v];
                }
                else dp[v]=dp[u];
            }
            dfs(v, u);
        }
}

bool degree_limit_tree()//返回是否能构成满足要求的树，形成的树保存在in_tree数组中
{
    //初始化
    for(int i=1;i<=V;++i)
    {
        par[i]=i;
        high[i]=0;
        for(int j=1;j<=V;++j)
            in_tree[i][j]=false;
    }
    //Kruskal计算求不与特殊点连接的边的最小生成树
    sort(edge+1, edge+1+E);
    for(int i=1;i<=E;++i)
    {
        if(edge[i].from>edge[i].to)
            swap(edge[i].from, edge[i].to);
        if(edge[i].from!=1 && unite(edge[i].from, edge[i].to))
            in_tree[edge[i].from][edge[i].to]=in_tree[edge[i].to][edge[i].from]=true;
    }
    //把各个连通块连接到特殊点
    for(int i=1;i<=V;++i)
        the_min[i]=-1;
    for(int i=1;i<=E;++i)
        if(edge[i].from==1)
        {
            int fa=findfather(edge[i].to);
            if(the_min[fa]==-1 || edge[i].cost<edge[the_min[fa]].cost)
                the_min[fa]=i;
        }
    int deg=0;//根节点度数
    for(int i=2;i<=V;++i)
        if(~the_min[i])
        {
            int id=the_min[i];
            in_tree[edge[id].from][edge[id].to]=G[edge[id].to][edge[id].from]=true;
            ++deg;
        }
        else if(the_min[findfather(i)]==-1)//有连通块无法连接到根节点
            return false;
    if(deg>K)//无法在限制内构成生成树
        return false;
    dp[1].cost=-INF;
    //不断增加特殊结点的度数
    for(++deg;deg<=K;++deg)
    {
        int add=INF, index=-1;
        dfs(1, -1);
        for(int v=2;v<=V;++v)
            if(G[1][v]!=INF && !in_tree[1][v] && add>G[1][v]-dp[v].cost)
            {
                add=G[1][v]-dp[v].cost;
                index=v;
            }
        if(add>=0)//不能使答案更小，跳出
            break;
        in_tree[1][index]=in_tree[index][1]=true;
        in_tree[dp[index].from][dp[index].to]=in_tree[dp[index].to][dp[index].from]=false;
    }
    return true;
}
