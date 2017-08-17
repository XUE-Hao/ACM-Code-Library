/*
 * 二分图多重匹配 匈牙利算法
 * 一个右边结点可以和多个左边结点匹配
 */

const int MAXN=100000+3;//最大左边结点数，根据题意修改
const int MAXM=10;//最大右边结点数，根据题意修改
int uN, vN;//左边结点数，右边结点数，两边都从0开始
int G[MAXN][MAXM];//只建立从左边到右边的有向边
int linker[MAXM][MAXN];//保存每个右边结点匹配到的左边点，数组模拟vector
bool used[MAXM];
int num[MAXM];//右边最大的匹配数

bool dfs(int u)
{
    for(int v=0;v<vN;++v)
        if(G[u][v] && !used[v])
        {
            used[v]=true;
            if(linker[v][0]<num[v])
            {
                linker[v][++linker[v][0]]=u;
                return true;
            }
            for(int i=1;i<=num[v];++i)
                if(dfs(linker[v][i]))
                {
                    linker[v][i]=u;
                    return true;
                }
        }
    return false;
}

int hungary()
{
    int res=0;
    for(int i=0;i<vN;++i)
        linker[i][0]=0;
    for(int u=0;u<uN;++u)
    {
        for(int i=0;i<vN;++i)
            used[i]=false;
        if(dfs(u))//如果只要判左边能否完全匹配，只需要在第一次增广失败时返回false即可
            ++res;
    }
    return res;
}
