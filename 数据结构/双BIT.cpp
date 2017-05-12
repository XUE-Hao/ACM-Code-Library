/*
 *双BIT
 *利用双树状数组，实现计算区间的和，区间的插入
 *O(log n)
 */

const int MAXN=100000+5;

long long bit0[MAXN],bit1[MAXN];//bit0与普通bit相同，表示和。bit1表示区间所需要加的数字

// 求和sum{a[t], 0 <= t <= i}
long long sum(long long *b, int i)
{
    int s = 0;
    while (i > 0)
    {
        s += b[i];
        i -= (i & -i);
    }
    return s;
}

// 求和a[from, to)
long long sum(long long* bit, int from, int to)
{
    return sum(bit, to - 1) - sum(bit, from - 1);
}

// 执行 a[i] += v
void add(long long *b, int i, long long v)
{
    while (i < MAXN)
    {
        b[i] += v;
        i += (i & -i);
    }
}
// 基础bit结束

// 双BIT

//[0,n]
long long sum(int i)
{
    return sum(bit1, i) * i + sum(bit0, i);
}

//(from, to]
long long sum(int from, int to)
{
    return sum(to) - sum(from);
}

// [from, to]
void add(int from, int to, long long x)
{
    add(bit0, from, -x * (from - 1));
    add(bit1, from, x);
    add(bit0, to, x * to);
    add(bit1, to, -x);
}
