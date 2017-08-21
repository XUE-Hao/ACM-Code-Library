/*
 * RMQ - ST 算法
 * 解决RMQ问题，查询区间最大／最小值
 * 可以修改一下返回最大／最小值的下标
 * 预处理 O(N * log N)
 * 查询 O(1)
 */
#include <algorithm>
#include <cmath>
using namespace std;

struct ST
{
    static const int maxn=1000000+3;//最大长度
    static const int maxk=20;//最大层数（为最大长度的log）
    int n, k;//长度，层数
    int data[maxk][maxn];
    void build(int a[], int _n)//预处理，传入初始数组，长度
    {
        n=_n;
        k=(int)(log(n*1.0)/log(2.0))+1;
        for(int i=0;i<n;++i)
            data[0][i]=a[i];
        int d=1;
        for(int j=1;j<k;++j)
        {
            for(int i=0;i<n-d;++i)
                data[j][i]=min(data[j-1][i], data[j-1][i+d]);
            d<<=1;
        }
    }
    int query(int l, int r)//查询，输入查询区间的左闭右开下标
    {
        int k=(int)(log((r-l)*1.0)/log(2.0));
        return min(data[k][l], data[k][r-(1<<k)]); 
    }
}st;
