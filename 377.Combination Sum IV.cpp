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
follow up:
如果题目中的数组中允许负数，应该如何处理，会有什么变化？
If negative numbers are allowed in the given array, then there could be infinite solutions to the problem。
Because whenever the sum approaches target, I can add a negative number to make the sum less. 
To allow negative numbers, the length of the combinations needs to be limited.
因为只要有负数存在和就会越来越小，那么解会有无穷多个，因此需哟啊限制数组的长度。

有关combination的题目总结：
039 the Combination Sum 1 
040 the Combination Sum 2
216 the Combination Sum 3
377 the Combination Sum 4
Firstly, the Combination Sum 1 & 4 are similar, and Combination Sum 2 & 3 are similar.
Combination Sum 3 is the special case of Combination Sum 2, and the Combination Sum 4 return the count while Combination Sum 1 return all the combination !
k sum problem is a good extension for the combination sum problem, k-sum 1 is to return the count while k-sum 2 return all the possible results
*DP: when solve the problem return the count
*DFS : for return all the possible result