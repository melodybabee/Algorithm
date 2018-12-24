题意：相邻的房子不能涂上相同的颜色，那么问涂房子的最小花费是多少
思路：
1.因为后面房子的花费需要依靠前面每一次涂房子的时候的花费，因此是典型的DP问题
2.创建一个二维数组等于原花费中的初始值。每行进行更新，因为只有3个房子，所以每一位上更新的值就是自己本身的价格加上上一行中不是这一列的另外两个元素中的较小值。
3.最后返回最后一行中的较小值。
注意：
题目中说明了只有3种颜色，因此只更新3次即可。
class Solution {
public:
    int minCost(vector<vector<int>>& costs) {
        if(costs.empty()) return 0;
        vector<vector<int>>dp = costs;
        for(int i = 1;i < dp.size();++i){
            dp[i][0] += min(dp[i-1][1],dp[i-1][2]);
            dp[i][1] += min(dp[i-1][0],dp[i-1][2]);
            dp[i][2] += min(dp[i-1][0],dp[i-1][1]);
        }
        return min(min(dp.back()[0],dp.back()[1]),dp.back()[2]);
    }
};
优化：
1.可以在循环dp数组的内部3个位置的数字，不用分别写3次。对每一位%3就可以保证不是自己当前列上的数字。
class Solution {
public:
    int minCost(vector<vector<int>>& costs) {
        if(costs.empty()) return 0;
        vector<vector<int>>dp = costs;
        for(int i = 1;i < dp.size();++i){
            for(int j =  0; j < 3; ++j){
                dp[i][j] += min(dp[i-1][(j+1)%3],dp[i-1][(j+2)%3]);
            }
        }
        return min(min(dp.back()[0],dp.back()[1]),dp.back()[2]);
    }
};