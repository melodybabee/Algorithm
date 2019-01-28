题意：提供三种票价找到最合适的买票方案
思路：
1.因为后面的状态都需要根据前面的状态进行更新，所以用到的是DP的思路。
2.那么建立一个DP数组，dp[i]表示在第i天能够买到的最低票价，因为需要判断每一天，所以数组的长度就是天数
3.动态转移方程是dp[i] = min(dp[i-1]+costs[0]，dp[i-7]+costs[1]，dp[i-30]+costs[2])的最小值，不断更新
注意：
1.因为天数的数组和其坐标不是对应的，而DP数组是基于坐标进行更新的，因此需要提前用一个新的数组重新处理一下所有的天数，如果有这一天为1，没有就是0
2.初始化DP数组需要让其等于一天一天买票的价格，如果不存在这一天，那么更新为与前一天相同
class Solution {
public:
    int mincostTickets(vector<int>& days, vector<int>& costs) {
        vector<int>dp(days.back()+1,0);
        vector<int>day(days.back()+1,0);
        for(auto d : days) day[d] = 1;
        for(int i = 1; i < dp.size(); ++i){
            if(day[i] == 0){
                dp[i] = dp[i-1];
                continue;
            }
            dp[i] = dp[i-1]+costs[0]，;
            dp[i] = min(dp[i],dp[max(0,i-7)]+costs[1]);
            dp[i] = min(dp[i],dp[max(0,i-30)]+costs[2]);
        }
        return dp.back();
    }
};