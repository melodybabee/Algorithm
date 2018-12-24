题意：256 follow up,可以涂多个颜色
T(n) = O(nk);
思路：
1.涂多个颜色的时候需要找到两个较小值进行比较，如果当前列等于最小值，那么加上第二小值；否则就用当前列上的值加上最小值。
2.因此循环要从第一行开始，在最小值不存在（即小于0）的时候不添加到新的值上，原数值加上0。遇到新的较小值后先更新min1,再更新min2
3.每次重新进入循环之后，用新的两个值替换为最小值和较小值，再把最小值和较小值重新置为-1便于后面找到本行中的最小值和较小值。
4.最后返回最后一行中的最小值列上的值。
class Solution {
public:
    int minCostII(vector<vector<int>>& costs) {
        if(costs.empty()) return 0;
        vector<vector<int>>dp = costs;
        int min1 = -1;
        int min2 = -1;
        for(int i = 0; i < dp.size();++i){
            int last1 = min1, last2 = min2;
            min1 = -1, min2 = -1;
            for(int j = 0; j < dp[i].size();++j){
                if(j != last1){
                    dp[i][j] += last1 < 0 ? 0 : dp[i-1][last1];
                }else{
                    dp[i][j] += last2 < 0 ? 0 : dp[i-1][last2];
                }
                
                if(min1 < 0 || dp[i][j] < dp[i][min1]){
                    min2 = min1;
                    min1 = j;
                }else if(min2 < 0 || dp[i][j] < dp[i][min2]){
                    min2 = j;
                }
            }
        }
        return dp.back()[min1];
    }
};