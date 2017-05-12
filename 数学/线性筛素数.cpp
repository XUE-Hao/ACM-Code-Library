const int MAXN=200000;//所需要的素数的上限(根据题意修改)
long long prime[MAXN]={0},num_prime=0;//num_pirme记录素数个数,prime储存素数
void primeList()
{
    int a[MAXN]={1,1},i,j;
    for(i=2;i<MAXN;i++)
    {
        if(!a[i])
            prime[num_prime++]=i;
        for(j=0;j<num_prime && i*prime[j]<MAXN;j++)
        {
            a[i*prime[j]]=1;//合数标为1，同时，prime[j]是合数i*prime[j]的最小素因子
            if(!(i%prime[j]))//即比一个合数大的质数和该合数的乘积可用一个更大的合数和比其小的质数相乘得到
                break;
        }
    }
}
