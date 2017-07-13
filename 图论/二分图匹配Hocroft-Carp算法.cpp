/*********************************
 * 二分图匹配(Hopcroft-Carp算法)
 * 复杂度O(sqrt(V)*E)
 * 邻接表存图，vector实现
 * vector先初始化，然后加入边
 * num_N为左端的顶点数，使用前赋值（点编号从0开始）
 * 不会破坏原图
 */

#include <cstring>
#include <vector>
#include <queue>
using namespace std;
#define INF 0x3f3f3f3f
#define mem(a,b) memset((a),(b),sizeof(a))

const int MAXV=1000+3;//顶点数（根据题意修改）
int num_x;//左边顶点数
vector<int> G[MAXV];//图的邻接表形式（左边顶点在前面，只需要建立从左边指向右边的边即可）
int match_x[MAXV],match_y[MAXV];//顶点匹配对象
int dis,dis_x[MAXV],dis_y[MAXV];//距离（用于多路增广）
bool used[MAXV];

bool searchP()//标记距离（用于多路增广）
{
    queue<int> que;
    dis=INF;
    mem(dis_x,-1);
    mem(dis_y,-1);
    for(int i=0;i<num_x;++i)
        if(match_x[i]==-1)
        {
            que.push(i);
            dis_x[i]=0;
        }
    while(!que.empty())
    {
        int u=que.front(); que.pop();
        if(dis_x[u]>dis)
            break;
        for(int i=0;i<G[u].size();++i)
        {
            int v=G[u][i];
            if(dis_y[v]==-1)
            {
                dis_y[v]=dis_x[u]+1;
                if(match_y[v]==-1)
                    dis=dis_y[v];
                else
                {
                    dis_x[match_y[v]]=dis_y[v]+1;
                    que.push(match_y[v]);
                }
            }
        }
    }
    return dis!=INF;
}

bool dfs(int u)//dfs增广
{
    for(int i=0;i<G[u].size();++i)
    {
        int v=G[u][i];
        if(!used[v]&&dis_y[v]==dis_x[u]+1)
        {
            used[v]=true;
            if(match_y[v]!=-1&&dis_y[v]==dis)
                continue;
            if(match_y[v]==-1||dfs(match_y[v]))
            {
                match_y[v]=u;
                match_x[u]=v;
                return true;
            }
        }
    }
    return false;
}

int hopcroft_carp()
{
    int res=0;
    mem(match_x,-1);
    mem(match_y,-1);
    while(searchP())
    {
        mem(used,0);
        for(int i=0;i<num_x;++i)
            if(match_x[i]==-1&&dfs(i))
                ++res;
    }
    return res;
}
