long long combineNumber(int n,int m)//从n中取m个.
{
    if(m>n/2)
        m=n-m;
    long long ans=1;
    for(int i=1;i<=m;++i)
        ans=ans*(n-i+1)/i;
    return ans;
}
