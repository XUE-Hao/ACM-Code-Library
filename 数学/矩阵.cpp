#include <cstring>
#include <algorithm>
using namespace std;
#define MOD 1000000007

struct Matrix
{
    int a[2][2];//矩阵大小根据需求修改
    Matrix()
    {
        memset(a,0,sizeof(a));
    }
    void init()
    {
        for(int i=0;i<2;i++)
            for(int j=0;j<2;j++)
                a[i][j]=(i==j);
    }
    Matrix operator + (const Matrix &B)const
    {
        Matrix C;
        for(int i=0;i<2;i++)
            for(int j=0;j<2;j++)
                C.a[i][j]=(a[i][j]+B.a[i][j]+MOD)%MOD;
        return C;
    }
    Matrix operator * (const Matrix &B)const
    {
        Matrix C;
        for(int i=0;i<2;i++)
            for(int k=0;k<2;k++)
                for(int j=0;j<2;j++)
                    C.a[i][j]=(C.a[i][j]+1LL*a[i][k]*B.a[k][j]+MOD)%MOD;
        return C;
    }
    Matrix operator ^ (const int &t)const
    {
        Matrix A=(*this),res;
        res.init();
        int p=t;
        while(p)
        {
            if(p&1)res=res*A;
            A=A*A;
            p>>=1;
        }
        return res;
    }
    int det(int n)//求前n行n列的行列式的值
    {
        for(int i=0;i<n;++i)
            for(int j=0;j<n;++j)
                a[i][j]=(a[i][j]%MOD+MOD)%MOD;
        int ret=1;
        for(int i=0;i<n;i++)
        {
            for(int j=i+1;j<n;j++)
                while(a[j][i])
                {
                    int t=a[i][i]/a[j][i];//这里不需要求逆元，直接除即可
                    for(int k=i;k<n;++k)
                        a[i][k]=((a[i][k]-a[j][k]*t)%MOD+MOD)%MOD;
                    for(int k=i;k<n;++k)
                        swap(a[i][k],a[j][k]);
                    ret=-ret;
                }
            if(!a[i][i])
                return 0;
            ret=ret*a[i][i]%MOD;
        }
        ret=(ret%MOD+MOD)%MOD;
        return ret;//不取模的话要改成绝对值
    }
};
