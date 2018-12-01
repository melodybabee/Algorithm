题意：
122 follow up，多次买卖，卖之后需要停一次才能买，求最大利润。
思路：
1.根据题意一定使用DP来解题，需要设置3的数组buy[i],sell[i],hold[i]来分别记录第i次买，卖和停的时候的最大利润。
2.当原数组中的数字小于2个的时候，不存在最大利润。
3.初始化数组，buy[0]表示在第0次买入，那么利润是负值，为-prices[0]；
sell[0]和hold[0]表示在第一位都没有行动，利润为0；
4.遍历，动态转移方程为：
当前次买等于前一次买，和前一次停+本次买入的较大值。
当前次卖等于前一次卖，和前一次买+本次卖的较大值。
当前次停等于前一次停，前一次买，和前一次卖中间的较大值。
5.最后返回卖的数组中的最后一位。
class Solution {
public:
    int maxProfit(vector<int>& prices) {
        if(prices.size() <2) return 0;
        vector<int>buy(prices.size(),0);
        vector<int>sell(prices.size(),0);
        vector<int>hold(prices.size(),0);
        buy[0]= -prices[0];
        sell[0] = 0;
        hold[0] = 0;
        for(int i = 1; i < prices.size();++i){
            buy[i] = max(buy[i-1],hold[i-1]-prices[i]);
            sell[i] = max(sell[i-1], buy[i-1]+prices[i]);
            hold[i] = max(max(hold[i-1],sell[i-1]),buy[i-1]);
        }
        return sell.back();
    }
};
优化：
因为hold[i] == sell[i-1];所以可以精简上述3个动态转移方程为2个。因初始值要更麻烦一些，代码部分待更新。