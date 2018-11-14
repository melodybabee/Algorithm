题意：
找到一个数组中和等于目标值有多少种情况。
方法一：backtracking
MLE
思路：
1.当target很大的时候会超出内存范围，如果要求输出每一种情况，那么回溯的方法合适，如果只求出有多少种情况，直接DP即可

class Solution {
public:
    int combinationSum4(vector<int>& nums, int target) {
        vector<vector<int>> ret;
        vector<int> temp;
        helper(ret,temp,nums,target);
        return ret.size();
    }
    
    void helper(vector<vector<int>> &ret,vector<int> &temp,vector<int>& nums, int target){
        if(target == 0) {ret.push_back(temp); return;}
        if(target < 0) return;
        for(int i = 0; i < nums.size(); ++i){
            temp.push_back(nums[i]);
            helper(ret,temp,nums,target-nums[i]);
            temp.pop_back();
        }  
    }
};
方法二：DP
思路：
用一个DP[i]数组来表示第i位上的情况总和，其值等于其本身+减去某个数字后数字的情况总和。
class Solution {
public:
    int combinationSum4(vector<int>& nums, int target) {
        vector<int> dp(target+1,0);
        dp[0] = 1;
        for(int i = 1; i <= target; ++i){
            for(auto &a : nums){
                if(i-a >= 0)
                dp[i] += dp[i- a];
            }
        }
        return dp.back();
    }
};