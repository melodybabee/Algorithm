题意：
在拨号键盘中只能走日字格，求给出的指定的数组数字有多少种不同的走法。
思路：
1.通过观察发现，对于0-9，分别有2，2，2，2，3，0，3，2，2，2种走法，题目中的input是指连续走N次有多少次走法，输出就是output
2.如果输入是1次，即为原数组默认为1的所有值求和。如果输入两次，即为每位数字可以走的下一位的和。如果输入三次，即为每位数组走两次可以走的下一位的和。
3.因此是明显的DP问题，给定一个初始数组默认为1，当输入值大于等于2时，用动态转移方程更新数组，注意每次更新后替换
4.最后输出最后一次更新后数组的和即为所求
5.注意求模运算，10^9+7 = 1000000007,所有的变量都需要设置为long long 
class Solution {
public:
    int knightDialer(int N) {
        vector<long long> dp(10,1);
        static const long mod = 1000000007;
        long long total = 0;
        for(int i = 2; i <= N; ++i){
            vector<long long>temp(10,0);
            temp[0] = (dp[4] + dp[6])% mod;
            temp[1] = (dp[6] + dp[8])% mod;
            temp[2] = (dp[7] + dp[9])% mod;
            temp[3] = (dp[4] + dp[8])% mod;
            temp[4] = (dp[0] + dp[3] + dp[9])% mod;
            temp[5] = 0;
            temp[6] = (dp[0] + dp[1]+dp[7])% mod;
            temp[7] = (dp[2] + dp[6])% mod;
            temp[8] = (dp[1] + dp[3])% mod;
            temp[9] = (dp[2] + dp[4])% mod;
            
            dp = temp;
        }
        for(int i = 0; i < dp.size();++i){
            total += dp[i];
        }
        return total%mod;
    }
};