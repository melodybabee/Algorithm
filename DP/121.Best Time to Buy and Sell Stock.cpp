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
//T(n) = O(n), 一次遍历即可，无需两个loop
/*
动态规划的思想：
1.如果想找到最大利润，就是用后i天内最高的卖出价格减去前i天内最低的买入价格
买入：prices[i]= min{prices[k]}, k <= i;
卖出：prices[j]= max{prices[k]}, k >= j;
2.l[i]表示前i天内的最低价，逐天遍历，直到prices.size()
状态转移方程，p[i]=max(p[i-1],prices[i]-L[i]); vector p用于存储每一天的最大利润，单调非递减
3.所求的最大利润是p[prices.size()-1],即单调递减vector中的最后一位
*/

二刷：
DP：
注意：
1.DP的思路不仅仅是在一个DP数组中就能得到结果，不要单纯追求通过一个数组得到最优解，重点在于思想
2.本题想得到最大利润，最大利润=最高单价-最低单价，同时满足卖在买之后
3.那么用一个值来记录最小的花费，用一个值来记录当前值与最小值之间的差，即利润，不断更新
class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int minprice = INT_MAX;
        int maxpro = 0;
        for(int i = 0; i < prices.size();++i){
            minprice = min(minprice,prices[i]);
            maxpro = max(maxpro,prices[i]-minprice);
        }
        return maxpro;
    }
};