class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int pro = 0;
        for (int i = 1; i< prices.size(); ++ i){
            if(prices[i] > prices[i-1]){
                pro += (prices[i]-prices[i-1]);
            }
        }
        return pro;
    }
};
//T = O(n), S = O(1)
/*
思路：
1.通过观察发现，最大利润的实现方式是：
买入阶段：如果该位的后一位大于该位，买入；
卖出阶段：如果已经买入，高于买入价，而且后一位比此位低，则卖出
简化：即一有差价的时候就计算的时候利润最高
2.循环vector,只要后一位大于前一位，相加

注意：
1.在同一位上可以先卖出再买入
*/