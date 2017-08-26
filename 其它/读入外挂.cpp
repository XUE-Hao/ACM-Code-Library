/*
 * 读入外挂
 * 输入完成后要加上文件末尾符
 */
#include <cstdio>
#define LL long long

namespace fastIO {
#define BUF_SIZE 10000000 //如果超内存，这里可以改小一点
    //fread -> read
    bool IOerror = 0;
    inline char nc()
    {
        static char buf[BUF_SIZE], *p1 = buf + BUF_SIZE, *pend = buf + BUF_SIZE;
        if(p1 == pend)
        {
            p1 = buf;
            pend = buf + fread(buf, 1, BUF_SIZE, stdin);
            if(pend == p1)
            {
                IOerror = 1;
                return -1;
            }
        }
        return *p1++;
    }
    inline bool blank(char ch)
    {
        return ch == ' ' || ch == '\n' || ch == '\r' || ch == '\t';
    }
    inline void read(int &x)
    {
        char ch;
        while(blank(ch = nc()));
        if(IOerror)
            return;
        for(x = ch - '0'; (ch = nc()) >= '0' && ch <= '9'; x = x * 10 + ch - '0');
    }
    inline void read(LL &x)//不读入long long时可以去掉
    {  
        bool sign=0;
        char ch=nc();
        x=0;  
        for(;blank(ch);ch=nc());  
        if(IOerror)
            return;  
        if(ch=='-')
            sign=1,ch=nc();  
        for(;ch>='0'&&ch<='9';ch=nc())x=x*10+ch-'0';  
        if(sign)
            x=-x;  
    }  
#undef BUF_SIZE
};
using namespace fastIO;
