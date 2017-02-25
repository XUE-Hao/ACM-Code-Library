/*
 *二维区间BIT
 *用于处理二维空间中对区间的利用树状数组求和
 *O(log M * log H)
 */

#include <stdio.h>
#include <string.h>

const int maxn=1000+5;//长宽最大值，根据题意修改

// 二维矩阵的区间和
struct BinaryIndexedTree2D
{
#define MAX_BIT maxn+1
    long long data[MAX_BIT][MAX_BIT];
    int size;
    
    void init(int size)
    {
        memset(data, 0, sizeof(data));
        this->size = size;
    }
    
    // 求(0,0) 到(x,y)围成的矩形区域元素之和
    long long sum(int y, int x)
    {
        long long ret = 0;
        for (int ty = y; ty; ty -= ty&-ty)
            for (int tx = x; tx; tx -= tx&-tx)
                ret += data[ty][tx];
        return ret;
    }
    
    // 执行(x,y) += v
    void add(int y, int x, long long v)
    {
        for (int ty = y + 1; ty <= size; ty += ty&-ty)//注意这里下标加了1
            for (int tx = x + 1; tx <= size; tx += tx&-tx)
                data[ty][tx] += v;
    }
};

BinaryIndexedTree2D bit_xy, bit_x, bit_y, bit;
// sum(y,x)=bit_xy(y,x)*yx + bit_y(y,x)*y + bit_x(y,x)*x + bit(y,x)


//矩形[y1, y2) * [x1, x2)区域内每个元素增加v
void add(int y1, int y2, int x1, int x2, long long v)
{
    bit_xy.add(y1, x1, v);
    bit_xy.add(y1, x2, -v);
    bit_xy.add(y2, x1, -v);
    bit_xy.add(y2, x2, v);
    
    bit_x.add(y1, x1, -y1 * v);
    bit_x.add(y1, x2, y1 * v);
    bit_x.add(y2, x1, y2 * v);
    bit_x.add(y2, x2, -y2 * v);
    
    bit_y.add(y1, x1, -x1 * v);
    bit_y.add(y1, x2, x2 * v);
    bit_y.add(y2, x1, x1 * v);
    bit_y.add(y2, x2, -x2 * v);
    
    bit.add(y1, x1, y1 * x1 * v);
    bit.add(y1, x2, -x2 * y1 * v);
    bit.add(y2, x1, -y2 * x1 * v);
    bit.add(y2, x2, y2 * x2 * v);
}

// 区域和
long long sum(int y, int x)
{
    return bit_xy.sum(y, x) * y * x + bit_x.sum(y, x) * x + bit_y.sum(y, x) * y + bit.sum(y, x);
}

// 区域和，左开右闭
long long sum(int y1, int y2, int x1, int x2)
{
    return sum(y1, x1) + sum(y2, x2) - (sum(y1, x2) + sum(y2, x1));
}
