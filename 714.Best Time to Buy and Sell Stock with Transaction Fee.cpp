题意：
122 follow up，多次买卖，每次卖出后有一笔手续费，求最大利润。
思路：
1.根据题意一定使用DP来解题，需要设置buy[i],sell[i]来分别记录第i次买，卖时候的最大利润。
2.当原数组中的数字小于2个的时候，不存在最大利润。
3.初始化数组，buy[0]表示在第0次买入，那么利润是负值，为-prices[0]；
sell[0]表示在第一位没有行动，利润为0；
4.遍历，动态转移方程为：
当前次买等于前一次买，和前一次卖+本次买入的较大值。
当前次卖等于前一次卖，和前一次买+本次卖-费用的较大值。
5.最后返回卖的数组中的最后一位。
注意：
因为是DP数组，求出的是前面状态的结果，不等于每次都需要买或卖。
class Solution {
public:
    int maxProfit(vector<int>& prices, int fee) {
        if(prices.size() < 2) return 0;
        vector<int>buy(prices.size(),0);
        vector<int>sell(prices.size(),0);
        buy[0] = -prices[0];
        sell[0] = 0;
        for(int i = 1; i < prices.size();++i){
            buy[i] = max(sell[i-1]-prices[i],buy[i-1]);
            sell[i] = max(buy[i-1]+prices[i]-fee,sell[i-1]);
        }
        return sell.back();
    }
};
优化：
也可以用两个变量来存储。
注意设置一个临时变量存储没有改变之前的sell值。
class Solution {
public:
    int maxProfit(vector<int>& prices, int fee) {
        int buy = -prices[0];
        int sell = 0;
        for(int price : prices){
           int temp = sell;
           sell = max(buy+price-fee,sell);
           buy = max(buy,temp-price);
        }
        return sell;
    }
};