/*
 * 二分图最大权匹配 KM算法
 * 时间复杂度 O(nx * nx *ny)
 * 若求最小匹配，可将权值取相反数，结果取相反数
 * 左右点的标号都是从0开始
 */
#define INF 0x3f3f3f3f

const int MAXN=300+3;//一侧最大顶点数，根据题意修改
int nx, ny;//两边的点数
int G[MAXN][MAXN];//G[i][j]表示从左边的i到右边的j的边的花费
int linker[MAXN], lx[MAXN], ly[MAXN];//y中各点匹配状态，x,y中的点的标号
int slack[MAXN];
bool visx[MAXN], visy[MAXN];

bool dfs(int x)
{
    visx[x]=true;
    for(int y=0;y<ny;++y)
    {
        if(visy[y])
            continue;
        int tmp=lx[x]+ly[y]-G[x][y];
        if(tmp==0)
        {
            visy[y]=true;
            if(linker[y]==-1 || dfs(linker[y]))
            {
                linker[y]=x;
                return true;
            }
        }
        else if(slack[y]>tmp)
            slack[y]=tmp;
    }
    return false;
}

int km()
{
    for(int i=0;i<ny;++i)
    {
        linker[i]=-1;
        ly[i]=0;
    }
    for(int i=0;i<nx;++i)
    {
        lx[i]=-INF;
        for(int j=0;j<ny;++j)
            if(G[i][j]>lx[i])
                lx[i]=G[i][j];
    }
    for(int x=0;x<nx;++x)
    {
        for(int i=0;i<ny;++i)
            slack[i]=INF;
        while(true)
        {
            for(int i=0;i<nx;++i)
                visx[i]=false;
            for(int i=0;i<ny;++i)
                visy[i]=false;
            if(dfs(x))
                break;
            int d=INF;
            for(int i=0;i<ny;++i)
                if(!visy[i]&&d>slack[i])
                    d=slack[i];
            for(int i=0;i<nx;++i)
                if(visx[i])
                    lx[i]-=d;
            for(int i=0;i<ny;++i)
            {
                if(visy[i])
                    ly[i]+=d;
                else slack[i]-=d;
            }
        }
    }
    int res=0;
    for(int i=0;i<ny;++i)
        if(linker[i]!=-1)
            res+=G[linker[i]][i];
    return res;
}
