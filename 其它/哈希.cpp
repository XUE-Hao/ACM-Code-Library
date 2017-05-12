/*
 *哈希函数
 *用来保存一个比较复杂的状态，可以实现比较快速的比较
 */

struct Node//保存需要保存到状态
{
    int G[4][8];//状态（根据题意修改）
};
struct Hash
{
    int v,nid,next;//v是哈希值，nid是指对应的节点下标，next是指向下一个Hash节点，初始化时置为-1
};

const int MAXN=500005;//自己估计大小
const int MOD=100000+7;//自己估计大小（最好是素数）
int hash_id;//开全局，用于增加Hash节点，初始化值可置为mod-1
Hash ha[MOD+MAXN];
Node node[MAXN];//状态数组并用数组模拟队列或栈

void hash_init()//哈希初始化
{
    for(int i=0;i<MOD;++i)
        ha[i].next=-1;
    hash_id=MOD-1;
}

int get_hash(int A[][8])//得到哈希值（具体参数自行修改）
{
    int ret=0,k=1;  //ret是哈希值,k是系数
    for(int i=0;i<4;i++)//根据状态的大小修改
        for(int j=0;j<8;j++)
        {
            ret+=A[i][j]*k;
            //k*=2;          //每次扩大2倍
            k+=131;  //或者每次加131
        }
    return ret;
}
//可能哈希值会爆int,写的时候注意就是了

bool check(int a,int b)//自己写比较函数，a,b为结构体数组下标
{
    return false;
}

bool insert_hash(int v,int nid)//v是要插入状态的哈希值，nid是要插入的结构体下标
{
    int a=v%MOD;
    int p=ha[a].next;
    while(p!=-1)//一直找到末尾
    {
        if(ha[p].v==v&&check(ha[p].nid,nid))
            return false;
        //有完全相同的状态
        p=ha[p].next;//下一个Hash节点
    }
    p=++hash_id;      //增加新节点
    ha[p].v=v; ha[p].nid=nid;
    ha[p].next=ha[a].next; ha[a].next=p;//前插法
    return true;
}
