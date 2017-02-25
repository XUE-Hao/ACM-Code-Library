long long mod_pow(long long x,long long n,long long mod)//计算x^n对mod去余
{
    if(n==0)
        return 1;
    long long res=mod_pow(x*x%mod,n/2,mod);
    if(n&1)
        res=res*x%mod;
    return res;
}
