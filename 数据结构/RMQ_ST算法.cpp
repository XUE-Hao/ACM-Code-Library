/*
 * RMQ - ST 算法
 * 解决RMQ问题，查询区间最大／最小值
 * 可以修改一下返回最大／最小值的下标
 * 预处理 O(N * log N)
 * 查询 O(1)
 * 下标从1开始
 */
#include <algorithm>
using namespace std;

struct ST
{
    static const int maxn=1000000+3;//最大长度
    static const int maxk=20;//最大层数（为最大长度的log）
    int dp[maxk][maxn];
    int save_k[maxn];//保存任意长度对应的深度
    void build(int a[], int n)//预处理，传入初始数组，长度
    {
        save_k[0]=-1;
        for(int i=1;i<=n;++i)
        {
            save_k[i]=((i&(i-1))==0)?save_k[i-1]+1:save_k[i-1];
            dp[0][i]=a[i];
        }
        for(int j=1;j<=save_k[n];++j)
            for(int i=1;i+(1<<j)-1<=n;++i)
                dp[j][i]=min(dp[j-1][i], dp[j-1][i+(1<<(j-1))]);
    }
    int query(int l, int r)//查询[l, r]
    {
        int k=save_k[r-l+1];
        return min(dp[k][l], dp[k][r-(1<<k)+1]); 
    }
};
