题意：
在一个数组中可以在每个数字之前添加加号或者减号，求有多少种情况可以使得和等于目标值。
方法1:DFS递归
因为题目中给了20的数据规模，因此可以用这种方法AC，但是枚举出所有可能的情况，T(n)= 2^n.
思路：
1.对数组中每一个坐标上的数字，让目标和加上或者减去这个数字，分别调用递归。
2.如果递归到数组的结尾而目标和恰为0，那么说明找到满足条件的一种情况，计数器+1.
注意：
1.本题中求出的是满足题意的情况，按照下面的方法不能够找到对应每种情况是如何分配的。
比如（-1，1，1，1，1）= 3；
但是在题解中会是（1,-1,-1,-1,-1）= 0;
class Solution {
public:
    int findTargetSumWays(vector<int>& nums, int S) {
        int res = 0;
        helper(nums,S,0,res);
        return res;
    }
    
    void helper(vector<int>&nums, int S, int start, int &res){
        if(start == nums.size()){
            if(S == 0) ++res;
            return;
        }
        helper(nums,S+nums[start],start+1,res);
        helper(nums,S-nums[start],start+1,res);
    }
};
方法2：DP
上面递归的方法是有顶向下进行计算的，因此会有大量重复计算的部分，影响效率。
下面运用DP的方法记录了中间值，避免重复计算，提高效率。
1.创建一个数组中间存放hashtable,在递归过程中，如果循环到尾部，返回目标值是否等于0.
如果在循环到某一位时，hashtable中存在目标值，那么返回该位上的个数，避免再次计算。
2.hashtable中记录sum的值，它是+1或者-1递归形成的和。
class Solution {
public:
    int findTargetSumWays(vector<int>& nums, int S) {
        vector<unordered_map<int,int>> dp(nums.size());
        return helper(nums,S,0,dp);
    }
    
    int helper(vector<int>& nums,int sum, int start,vector<unordered_map<int,int>> &dp){
        if(start == nums.size()) return sum==0;
        if(dp[start].count(sum)) return dp[start][sum];
        int temp1 = helper(nums, sum+nums[start],start+1,dp);
        int temp2 = helper(nums, sum-nums[start],start+1,dp);
        return dp[start][sum] = temp1 + temp2;
    }
};
方法3:最优解
思路：
1.通过观察发现，如果想得到目标值，可以分成两部分计算，即正数的子集-负数的子集=目标值，找到一共有多少种这样的情况
2.sum(>0) - sum(<0) = target;
sum(>0) + sum(<0) + sum(>0) - sum(<0) = sum(>0) + sum (<0) + target;
2*sum(>0) = target + sum(total);
sum(>0) = (target + sum(total))/2
3.也就是说，找到数组中子集的个数，使得它等于（目标值+数组总和）／2
4.首先求出数组的总和，accumulate函数的最后一个是和的初始值。如果总和小于目标值返回0；如果总和+目标值不是偶数返回0；调用求子数组和的方法
5.在该方法中找到和等于子目标值，那么建立一个一维DP，dp[i]表示第i位一共有几种满足条件的情况。
初始值为0，状态转移方程是当前位置的值+（当前值-循环到的数字的位置）的值
6.最后返回DP的最后一位表示有多少种情况。
class Solution {
public:
    int findTargetSumWays(vector<int>& nums, int S) {
        int sum = accumulate(nums.begin(),nums.end(),0);
        return sum < S || (S+sum)%2 == 1 ? 0 : subsetSum(nums,(S+sum)/2);
    }
    
    int subsetSum(vector<int>& nums, int s){
        vector<int>dp(s+1);
        dp[0] = 1;
        for(auto n : nums){
            for(int i = s; i - n >= 0; --i){
                 dp[i] = dp[i] + dp[i-n];
            }
        }
        return dp[s];
    }
};
写成位运算的方式：
class Solution {
public:
    int findTargetSumWays(vector<int>& nums, int S) {
        int sum = accumulate(nums.begin(),nums.end(),0);
        return sum < S ||(S+sum)&1 ? 0 : subsetSum(nums,(S+sum) >> 1);
    }
    
    int subsetSum(vector<int>& nums, int s){
        vector<int>dp(s+1);
        dp[0] = 1;
        for(auto n : nums){
            for(int i = s; i - n >= 0; --i){
                 dp[i] = dp[i] + dp[i-n];
            }
        }
        return dp[s];
    }
};

12.11复习
1.DFS递归
注意：
1.需要在判断坐标是否等于数组长度的基础上判断S==0，不管是否满足都要return
2.S+-的是每一位上的值，所以不论数组中是什么值都适用
class Solution {
public:
    int findTargetSumWays(vector<int>& nums, int S) {
        int ans = 0;
        dfs(nums,0,S,ans);
        return ans;
    }
    
    void dfs(vector<int>& nums,int index, int S,int& ans){
        if(index == nums.size()){
            if(S==0) ++ans;
            return;
        }
        dfs(nums,index+1,S-nums[index],ans);
        dfs(nums,index+1,S+nums[index],ans);
    }
};