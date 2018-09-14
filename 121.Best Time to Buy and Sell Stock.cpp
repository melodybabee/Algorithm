class Solution {
public:
    int maxProfit(vector<int>& prices) {
        if(prices.size() <= 1) return 0;
        int ans;
        int ret = 0;
        for(int i = 0; i< prices.size()-1; ++i){
            for (int j = i+1; j < prices.size();++j){
                ans = prices[j] - prices[i];
                ret = max(ans, ret);
            }
        }
        return ret;
    }
};
/*
思路：
1.用两个for循环分别使vector后面的元素减去前面的元素
2.用ret取差值最大的数值，注意如果为负，则取0，因此需要初始化一个变量等于0；
T(n) = O(n*2), S(n) = O(1), 只声明了两个变量
*/
//DP
class Solution {
public:
    int maxProfit(vector<int>& prices) {
        vector<int> min_price(prices.size());
        vector<int> max_pro(prices.size());
        if(prices.size() < 1) return 0;
        min_price[0] = prices[0];
        for(int i = 1; i < prices.size(); ++i){
            min_price[i] = min(min_price[i-1], prices[i]);
            max_pro[i] = max(prices[i]-min_price[i-1],max_pro[i-1]);
        }
        return max_pro[prices.size()-1];
    }
};
/*
动态规划的思想：
1.如果想找到最大利润，就是用后i天内最高的卖出价格减去前i天内最低的买入价格
买入：prices[i]= min{prices[k]}, k <= i;
卖出：prices[j]= max{prices[k]}, k >= j;
2.l[i]表示前i天内的最低价，逐天遍历，直到prices.size()
状态转移方程，p[i]=max(p[i-1],prices[i]-L[i]); vector p用于存储每一天的最大利润，单调非递减
3.所求的最大利润是p[prices.size()-1],即单调递减vector中的最后一位
*/