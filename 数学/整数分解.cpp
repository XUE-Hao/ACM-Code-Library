#include <vector>
#include <map>
using namespace std;

//************************************
// Method:    divisor
// FullName:  divisor
// Access:    public 
// Returns:   vector<int> 约数
// Qualifier: 约数枚举，枚举数n的所有约数，并储存在vector中
// Parameter: const int & n 目标数n
//************************************
vector<int> divisor(const int& n)
{
    vector<int> res;
    for (int i=1;i*i<=n;++i)
    {
        if (n%i==0)
        {
            res.push_back(i);
            if (i!=n/i)
                res.push_back(n/i);
        }
    }
    
    return res;
}

//************************************
// Method:    prime_factor
// FullName:  prime_factor
// Access:    public 
// Returns:   map<int, int>
// Qualifier: 整数分解，得到所有质因数以及幂，map储存质因数到幂的映射
// Parameter: int n
//************************************
map<int, int> prime_factor(int n)
{
    map<int,int> res;
    for(int i=2;i*i<=n;++i)
    {
        while(n%i==0)
        {
            ++res[i];
            n/=i;
        }
    }
    if(n!=1)
        res[n]=1;
    return res;
}

//************************************
//
// Method:    prime_factor_time
// FullName:  prime_factor_time
// Access:    public 
// Returns:   vector<int>
// Qualifier: 只求解整数分解的因子的幂，直接将各个幂储存到vector中
// Parameter: int n
//************************************
vector<int> prime_factor_time(int n)
{
    vector<int>res;
    for (int i=2;i*i<=n;++i)
    {
        int time=0;
        while(n%i==0)
        {
            ++time;
            n/=i;
        }
        res.push_back(time);
    }
    if(n!=1)
        res.push_back(1);
    return res;
}