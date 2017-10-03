/*
 * 无向图最大团Bron_Kerbosch算法（轴优化）
 * 下标从0开始
 */
#include <algorithm>
#include <bitset>
using namespace std;

const int MAXV=45;//最大结点数，根据题意修改
int V;//顶点数
int max_clique;//最大团的大小
bitset<MAXV> G[MAXV];//邻接矩阵的状压表示

int ctz(const bitset<MAXV> &s)//返回末尾0的个数
{
    for(int i=0;i<MAXV;++i)
        if(s.test(i))
            return i;
    return MAXV;
}

void dfs(bitset<MAXV> R,bitset<MAXV> P,bitset<MAXV> X)//已经在团中的点状压，可能在团中的点状压，不考虑的点状压
{
    if(P.none() && X.none())//当前团是极大团（如果要计数，只需修改里面的操作即可）
    {
        max_clique=max(max_clique, (int)R.count());//R中1的就是极大团中点，如果要输出构成最大团的点，这里更新时保存R中的点即可
        return ;
    }
    if(P.none())//当前团是以求得的极大团的子图
        return;
    int pivot = ctz(P|X);//选择一个轴点
    bitset<MAXV> PP = P&~G[pivot];//代选择点中不与轴点相邻的点
    for(int u=ctz(PP);u<V;u+=ctz(PP>>(u+1))+1)//枚举PP中的点
    {
        R.set(u);
        dfs(R,P&G[u],X&G[u]);
        R.reset(u);
        P.reset(u);//把u移到不考虑的点中
        X.set(u);
    }
}

int BronKerbosch()
{
    max_clique=0;
    bitset<MAXV> tmp;
    for(int i=0;i<V;++i)
        tmp.set(i);
    dfs(0,tmp,0);//初始团中没有点，所有点都可能在团中，没有点不考虑
    return max_clique;
}
