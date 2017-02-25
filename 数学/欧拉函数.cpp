const int N=1000005;//所需要求的最大的欧拉函数值(根据题意修改)
int phi[N];//存放欧拉函数值
void euler()//计算欧拉函数(小于n且与n互质的正整数的个数(包括1))
{
    //phi[1]=1;//正常情况下是从2开始,phi[1]=0,但有时题意特别说明,特判phi[1]=1
    for(int i=2;i<=N;i++)
    {//筛选求phi
        if (!phi[i])
        {
            for(int j=i;j<=N;j+=i)
            {
                if(!phi[j])
                    phi[j]=j;
                phi[j]=phi[j]/i*(i-1);
            }
        }
    }
}

int eluer(int n)//计算某一个数的欧拉函数值
{
    int m=n,ans=n;
    for (int i=2;i*i<=ans;i++)
    {
        if (m%i==0) ans=ans/i*(i-1);
        while (m%i==0) m/=i;
    }
    if (m>1) ans=ans/m*(m-1);
    return ans;
}
