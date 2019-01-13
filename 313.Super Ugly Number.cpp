题意：找到给定的质数序列中，不断对已有的质数进行质数更新后的第n个数字
思路：
1.264 ugly number的follow up
2.因为已经给出了一个质数序列，那么dp数组更新的就是在原有的质数序列的基础上，每次乘积最小值是被更新的dp[i]
3.需要设置一个坐标数组来记录更新到的位置，这个坐标表示dp数组中的循环到了哪一位
4.每次用坐标数组与质数数组进行乘积，找到最小值，把最小值在坐标位置上进行更新，更新到下一位，表示可以到dp的下一位进行计算
5.最后返回dp数组最后的数字
class Solution {
public:
    int nthSuperUglyNumber(int n, vector<int>& primes) {
        vector<int>dp(n,1);
        vector<int>index(primes.size(),0);
        for(int i = 1 ; i < dp.size();++i){
            dp[i] = INT_MAX;
            for(int j = 0; j < primes.size(); ++j){
                dp[i] = min(dp[i],dp[index[j]] * primes[j]);
            }
            for(int j = 0; j < primes.size(); ++j){
                if(dp[i] == dp[index[j]] * primes[j]){
                    ++index[j];
                }
            }
        }
        return dp.back();
    }
};