struct HashMap
{
    const static int MOD=1196473;//比总状态数大一些即可
    const static int MAXN=2000000;//大概状态数的两倍
    int head[MOD];//链表头指针
    int next[MAXN];//指向链表下一个节点
    int cnt;//当前节点数
    int key[MAXN],val[MAXN];//键，值
    void clear()
    {
        cnt=0;
        memset(head,0,sizeof head);
    }
    inline void insert(int _key,int _val)
    {
        int p=_key%MOD;//取模后对应的链
        ++cnt;
        key[cnt]=_key;
        val[cnt]=_val;
        next[cnt]=head[p];
        head[p]=cnt;
    }
    int find(int _key)
    {
        int p=_key%MOD;
        for(int i=head[p];i;i=next[i])//沿着链找到目标值
            if(val[i]==_key)
                return val[i];
        return -1;//没找到
    }
};
