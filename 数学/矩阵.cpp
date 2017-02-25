#include <cstring>
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
                C.a[i][j]=(a[i][j]+B.a[i][j])%MOD;
        return C;
    }
    Matrix operator * (const Matrix &B)const
    {
        Matrix C;
        for(int i=0;i<2;i++)
            for(int k=0;k<2;k++)
                for(int j=0;j<2;j++)
                    C.a[i][j]=(C.a[i][j]+1LL*a[i][k]*B.a[k][j])%MOD;
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
};
