const int MAXN=1000005;
struct Node
{
    int l,r,v,tag;//左右端点，值，标记
}a[MAXN<<2];

void build_tree(int i,int left,int right)//使用时用build_tree(1,1,N)
{
    a[i].l=left;
    a[i].r=right;
    a[i].tag=0;
    a[i].v=2;
    
    if(left==right)
        return ;
    
    int mid=(left+right)>>1;
    build_tree(i<<1,left,mid);
    build_tree(i<<1|1,mid+1,right);
}

void push_down(int i)
{
    if(a[i].tag)
    {
        a[i<<1].v=a[i<<1|1].v=a[i<<1].tag=a[i<<1|1].tag=a[i].tag;//具体操作根据需求修改
        a[i].tag=0;
    }
}

void push_up(int i)
{
    a[i].v=a[i<<1].v|a[i<<1|1].v;//具体操作根据需求修改
}

void add(int i,int left,int right,int val)
{
    if(a[i].l>=left&&a[i].r<=right)
    {
        a[i].v=a[i].tag=val;
        return ;
    }
    
    push_down(i);
    if(a[i<<1].r>=left)
        add(i<<1,left,right,val);
    if(a[i<<1|1].l<=right)
        add(i<<1|1,left,right,val);
    push_up(i);
}

int query(int i,int left,int right)
{
    if(a[i].l>=left&&a[i].r<=right)
        return a[i].v;
    
    push_down(i);
    push_up(i);
    if(a[i<<1].r>=right)
        return query(i<<1,left,right);
    else if(a[i<<1|1].l<=left)
        return query(i<<1|1,left,right);
    else return query(i<<1,left,right)|query(i<<1|1,left,right);//具体操作根据需求修改
}
