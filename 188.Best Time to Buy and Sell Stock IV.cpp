题意：
123follow up,限制最多K次，求最大利润。
1.把123中的两次限制更改为k次就可以。
2.注意如果K的次数过大，大于数组的长度，那么不需要建立一个长度为K的数组，会因为内存原因报错。
需要先比较一下，如果过大，转换为122题目，交易的次数无法起到限制的作用。直接取每次交易的正差值就可以。
class Solution {
public:
    int maxProfit(int k, vector<int>& prices) {
        if(prices.empty()) return 0;
        if(k >= prices.size()) return max2(prices);
        vector<vector<int>> global(prices.size(),vector<int>(k+1,0));
        vector<vector<int>> local(prices.size(),vector<int>(k+1,0));
        for(int i = 1; i< prices.size();++i){
            int diff = prices[i] - prices[i-1];
            for(int j = 1; j <= k; ++j){
                local[i][j] = max(global[i-1][j-1]+max(diff,0),local[i-1][j]+diff);
                global[i][j] = max(local[i][j],global[i-1][j]);
            }
        }
        return global[prices.size()-1][k];
    }
    
    int max2(vector<int>& prices){
        int ret = 0;
        for(int i = 1; i< prices.size(); ++i){
            if(prices[i] > prices[i-1]){
                ret += prices[i]-prices[i-1];
            }
        }
        return ret;
    }
};