/*
 * 稳定婚姻问题 gale-shapley算法
 * 时间复杂度O(N^2)
 * 下标从1开始
 */
#include <queue>
using namespace std;

const int MAXN=500+3;
int couple[MAXN];//每个女生匹配的男生
queue<int> que;//存没有匹配的男生
int man_like_woman_rank[MAXN][MAXN];//代表i男对女生的喜欢排名
int woman_like_man_val[MAXN][MAXN];//代表i女对j男的喜欢程度
int N;//每边的人数

void gale_shapley()
{
    while(!que.empty())
        que.pop();
    for(int i=1;i<=N;++i)
        couple[i]=-1;
    for(int i=1;i<=N;++i)
        que.push(i);
    while(!que.empty())
    {
        int man=que.front(); que.pop();
        for(int i=1;i<=N;++i)
            if(man_like_woman_rank[man][i]!=-1)
            {
                //选择未被拒绝且最喜欢的女生
                int woman=man_like_woman_rank[man][i];
                man_like_woman_rank[man][i]=-1;
                int pre=couple[woman];
                if(pre==-1)//对方没有匹配，直接匹配
                {
                    couple[woman]=man;
                    break;
                }
                else
                {
                    if(woman_like_man_val[woman][man]>woman_like_man_val[woman][pre])//更换匹配
                    {
                        que.push(pre);
                        couple[woman]=man;
                        break;
                    }
                }
            }
    }
}
