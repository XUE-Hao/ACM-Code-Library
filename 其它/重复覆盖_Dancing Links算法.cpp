/*
 * Dancing Links重复覆盖
 * 选择一些行，使得每列最少有一个1
 * 下标从1开始
 */

#define INF 0x3f3f3f3f

struct DLX
{
    static const int maxn=15*15+10;//最大行数，根据题意修改
    static const int maxm=15*15+10;//最大列数，根据题意修改
    static const int maxnode=maxn*maxm;//最大结点数，根据题意修改
    int n,m,size;//行数，列数，节点数
    int U[maxnode],D[maxnode],R[maxnode],L[maxnode],Row[maxnode],Col[maxnode];
    int H[maxn],S[maxm];
    int ansd;//选择的行数
    void init(int _n,int _m)//初始化，传入行数列数
    {
        ansd=INF;
        n = _n;
        m = _m;
        for(int i = 0;i <= m;i++)
        {
            S[i] = 0;
            U[i] = D[i] = i;
            L[i] = i-1;
            R[i] = i+1;
        }
        R[m] = 0; L[0] = m;
        size = m;
        for(int i = 1;i <= n;i++)
            H[i] = -1;
    }
    void Link(int r,int c)//在第i行第j列添加一个结点1
    {
        ++S[Col[++size]=c];
        Row[size] = r;
        D[size] = D[c];
        U[D[c]] = size;
        U[size] = c;
        D[c] = size;
        if(H[r] < 0)H[r] = L[size] = R[size] = size;
        else
        {
            R[size] = R[H[r]];
            L[R[H[r]]] = size;
            L[size] = H[r];
            R[H[r]] = size;
        }
    }
    void remove(int c)
    {
        for(int i = D[c];i != c;i = D[i])
            L[R[i]] = L[i], R[L[i]] = R[i];
    }
    void resume(int c)
    {
        for(int i = U[c];i != c;i = U[i])
            L[R[i]] = R[L[i]] = i;
    }
    bool v[maxm];
    int f()//估值函数
    {
        int ret = 0;
        for(int c = R[0]; c != 0;c = R[c])
            v[c] = true;
        for(int c = R[0]; c != 0;c = R[c])
            if(v[c])
            {
                ret++;
                v[c] = false;
                for(int i = D[c];i != c;i = D[i])
                    for(int j = R[i];j != i;j = R[j])
                        v[Col[j]] = false;
            }
        return ret;
    }
    //搜索函数
    void Dance(int d)//d为递归深度
    {
        if(d + f() >= ansd)//A*剪枝
            return;
        if(R[0] == 0)
        {
            if(d < ansd)//保存最小行数
                ansd = d;
            return;
        }
        int c = R[0];
        for(int i = R[0];i != 0;i = R[i])//选择结点数最小的行
            if(S[i] < S[c])
                c = i;
        for(int i = D[c];i != c;i = D[i])
        {
            remove(i);
            for(int j = R[i];j != i;j = R[j])
                remove(j);
            Dance(d+1);
            for(int j = L[i];j != i;j = L[j])
                resume(j);
            resume(i);
        }
    }
};
