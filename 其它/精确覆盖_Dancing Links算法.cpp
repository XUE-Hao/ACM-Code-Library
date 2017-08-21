/*
 * Dancing Links精确覆盖
 * 选择一些行，使得每列有且恰好有一个1
 * 下标从1开始
 */

struct DLX
{
    static const int maxn=1000+3;//最大行数，根据题意修改
    static const int maxm=1000+3;//最大列数，根据题意修改
    static const int maxnode=100000+3;//最大结点数，根据题意修改
    int n, m, size;//行数，列数，节点数
    int U[maxnode], D[maxnode], R[maxnode], L[maxnode], Row[maxnode], Col[maxnode];
    int H[maxn], S[maxm];
    int ansd, ans[maxn];//选取的行数，每一行的id
    void init(int _n, int _m)//初始化，传入行数列数
    {
        ansd=-1;
        n = _n;
        m = _m;
        for(int i = 0;i <= m;i++)
        {
            S[i] = 0;
            U[i] = D[i] = i;
            L[i] = i-1;
            R[i] = i+1;
        }
        R[m] = 0;
        L[0] = m;
        size = m;
        for(int i = 1;i <= n;i++)
            H[i] = -1;
    }
    void Link(int r, int c)//在第i行第j列添加一个结点1
    {
        ++S[Col[++size] = c];
        Row[size] = r;
        D[size] = D[c];
        U[D[c]] = size;
        U[size] = c;
        D[c] = size;
        if(H[r] < 0)
            H[r] = L[size] = R[size] = size;
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
        L[R[c]] = L[c]; R[L[c]] = R[c];
        for(int i = D[c];i != c;i = D[i])
            for(int j = R[i];j != i;j = R[j])
            {
                U[D[j]] = U[j];
                D[U[j]] = D[j];
                --S[Col[j]];
            }
    }
    void resume(int c)
    {
        for(int i = U[c];i != c;i = U[i])
            for(int j = L[i];j != i;j = L[j])
                ++S[Col[U[D[j]] = D[U[j]] = j]];
        L[R[c]] = R[L[c]] = c;
    }
    //搜索函数，返回是否有解
    bool Dance(int d)//d为递归深度
    {
        if(ansd!=-1 && ansd<=d)//剪枝
            return false;
        if(R[0] == 0)
        {
            ansd = d;
            return true;
        }
        int c = R[0];
        for(int i = R[0];i != 0;i = R[i])//选择结点数最小的行
            if(S[i] < S[c])
                c = i;
        remove(c);
        for(int i = D[c];i != c;i = D[i])
        {
            ans[d] = Row[i];
            for(int j = R[i]; j != i;j = R[j])
                remove(Col[j]);
            if(Dance(d+1))
                return true;//如果要求输出最小行数，不要返回
            for(int j = L[i]; j != i;j = L[j])
                resume(Col[j]);
        }
        resume(c);
        return false;
    }
};
