
int CaculateWeekDay(int y,int m,int d)
{
    if(m==1)
    {
        m=13;
        y--;
    }
    if(m==2)
    {
        m=14;
        y--;
    }
    int week=(d+2*m+3*(m+1)/5+y+y/4-y/100+y/400)%7;
    return week;//返回的0是星期一，后面递增。
}
//此外日期与星期400年一循环
