题意：扎气球问题，找到最大的积分
思路：
1.因为这个问题需要不断借助之前的结果进行计算，因此用到的是DP的方法
2.那么建立dp数组。dp[i][j]表示的是从i到j位置上能得到的最大值
3.因为当左右没有数字的时候需要乘上1，因此首先需要在数组的最前面和最后面的位置插入数字1
4.从长度1开始不断更新区间长度，直到更新到原区间为止。建立区间内的左右边界left和right,更新区间dp[left][right]上面的最大值
5.设置一个k，用来表示在一个区间长度上最后一个被打爆的气球，既k为剩下的最后一个气球.dp[left][k-1]就是左边部分被打爆的最大值,dp[k+1][right]就是右边部分被打爆的最大值
注意此时：k作为最后一个被消除的元素，那么这个区间的连乘的最大值为nums[left-1]*nums[k]*nums[right+1]，此时的left和right都不存在了
6.最后返回dp数组中第一行所在的最后一个元素的位置。
class Solution {
public:
    int maxCoins(vector<int>& nums) {
        int m = nums.size();
        nums.insert(nums.begin(),1);
        nums.push_back(1);
        vector<vector<int>>dp(nums.size(),vector<int>(nums.size(),0));
        for(int len  = 1; len <= m; ++len){
            for(int left = 1; left <= m-len+1; ++left){
                int right = left + len -1;
                for(int k = left; k <= right; ++k){
                    dp[left][right] = max(dp[left][right],nums[left-1]*nums[k]*nums[right+1]+dp[left][k-1]+dp[k+1][right]);
                }
            }
        }
        return dp[1][m];
    }
};