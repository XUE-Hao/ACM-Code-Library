/*
 * 无向图最大团Bron_Kerbosch算法（轴优化）
 * 由于使用unsigned long long状压，图的节点数能超过64需要手写bitset
 * 下标从0开始
 */
#include <algorithm>
#include <cstdio>
using namespace std;
#define ULL unsigned long long

const int MAXN=45;//最大结点数，根据题意修改
int V;//顶点数
int max_clique;//最大团的大小
ULL G[MAXN];//邻接矩阵的状压表示

inline int ctz(ULL s)//返回末尾0的个数，由于__bilitin_ctzll输入0时未定义，这里手动定义
{
    return s?__builtin_ctzll(s):64;
}

void dfs(ULL R,ULL P,ULL X)//已经在团中的点状压，可能在团中的点状压，不考虑的点状压
{
    if(!P && !X)//当前团是极大团
    {
        max_clique=max(max_clique,__builtin_popcountll(R));//R中1的就是极大团中点，如果要输出构成最大团的点，这里更新时保存R中的点即可
        return ;
    }
    if(!P)//当前团是以求得的极大团的子图
        return;
    int pivot = ctz(P|X);//选择一个轴点
    ULL PP = P&~G[pivot];//代选择点中不与轴点相邻的点
    for(int u=ctz(PP);u<V;u+=ctz(PP>>(u+1))+1)//枚举PP中的点
    {
        dfs(R|((ULL)1<<u),P&G[u],X&G[u]);
        P ^= (ULL)1<<u;//把u移到不考虑的点中
        X |= (ULL)1<<u;
    }
}

int BronKerbosch()
{
    max_clique=0;
    dfs(0,((ULL)1<<V)-1,0);//初始团中没有点，所有点都可能在团中，没有点不考虑
    return max_clique;
}
