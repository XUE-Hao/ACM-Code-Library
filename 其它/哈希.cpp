#include <cstring>

struct HashMap
{
    const static int mod=1196473;//比总状态数小一些即可
    const static int maxn=2000000;//大概状态数大一些
    int head[mod];//链表头指针
    int next[maxn];//指向链表下一个节点
    int size;//当前节点数
    int key[maxn],val[maxn];//键，值
    void clear()
    {
        size=0;
        memset(head,-1,sizeof head);
    }
    inline void insert(int _key,int _val)
    {
        int p=_key%mod;//取模后对应的链
        key[size]=_key;
        val[size]=_val;
        next[size]=head[p];
        head[p]=size++;
    }
    int find(int _key)
    {
        int p=_key%mod;
        for(int i=head[p];~i;i=next[i])//沿着链找到目标值
            if(val[i]==_key)
                return val[i];
        return -1;//没找到
    }
};
