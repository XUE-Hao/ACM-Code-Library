/*
 * 次小生成树
 * 求次小生成树时，用数组the_max[i][j]来表示MST中i到j最大边权
 * 求完后，直接枚举所有不在MST中的边，替换掉最大边权的边，更新答案
 * 点的编号从0开始
 */
#include <algorithm>
using namespace std;
#define INF 0x3f3f3f3f

const int MAXV=100+3;//最大结点树，根据题意修改
bool vis[MAXV];//访问标记（prime中使用）
int min_cost[MAXV];//连接到已经连通的集合中的最小花费
int pre[MAXV];//前驱结点（prim中使用）
int save_max[MAXV][MAXV];//the_max[i][j]表示最小生成树中从i到j的路径中最大边权
bool in_mst[MAXV][MAXV];//是否在最小生成树中的标记

//Prim算法求最小生成树的同时求出求次小生成树需要的信息。返回最小生成树的权值
int prim(int cost[][MAXV], int n)//图的邻接矩阵（没有连接的边花费为INF），节点数
{
    int res=0;
    for(int i=0;i<n;++i)//初始化
    {
        vis[i]=0;
        for(int j=0;j<n;++j)
        {
            save_max[i][j]=0;
            in_mst[i][j]=false;
        }
    }
    vis[0]=true;
    pre[0]=-1;
    for(int i=1;i<n;++i)
    {
        min_cost[i]=cost[0][i];
        pre[i]=0;
    }
    min_cost[0]=0;
    for(int i=1;i<n;++i)
    {
        int minc=INF;
        int p=-1;
        for(int v=0;v<n;++v)
            if(!vis[v] && minc>min_cost[v])
            {
                minc=min_cost[v];
                p=v;
            }
        if(minc==INF)//无法形成生成树，返回-1
            return -1;
        res+=minc;
        vis[p]=true;
        in_mst[p][pre[p]]=in_mst[pre[p]][p]=true;
        for(int v=0;v<n;++v)
        {
            if(v==p)
                continue;
            if(vis[v])
                save_max[v][p]=save_max[p][v]=max(save_max[v][pre[p]], min_cost[p]);
            if(!vis[v] && min_cost[v] > cost[p][v])
            {
                min_cost[v]=cost[p][v];
                pre[v]=p;
            }
        }
    }
    return res;
}
