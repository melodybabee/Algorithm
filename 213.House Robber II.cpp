题意：198 follow up,环状房子求最大抢劫值
方法一：标准DP
思路：
1.因为头尾连接起来的说明不能同时抢第一个和最后一个，那么对分别去掉第一个和最后一个的数组调用递归函数
2.其余思路和198相同，找到指定范围内的最大值，最后返回两组递归中的较大值
注意：
1.要特别注意当数组长度为0，1，2时候的情况，长度为0返回0，长度为1返回1，长度为2分别调用递归返回左侧的值进行判断
class Solution {
public:
    int rob(vector<int>& nums) {
        if(nums.size() <= 1) return nums.empty() ? 0 : nums[0];
        return max(helper(nums,0,nums.size()-1),helper(nums,1,nums.size()));
    }
    
    int helper(vector<int>& nums,int left, int right){
        if(right - left <= 1)return nums[left];
        vector<int>dp(right,0);
        dp[left] = nums[left];
        dp[left+1] = max(nums[left],nums[left+1]);
        for(int i = left + 2; i < right ;++i){
            dp[i] = max(dp[i-2] + nums[i], dp[i-1]);
        }
        return dp.back();
    }
};
方法2:DP优化
思路：
1.同样分为抢和不抢进行判断，抢是抢当前的和之前不抢的，不抢是之前抢和不抢之间的较大值
2.最后返回抢和不抢之间的较大值
class Solution {
public:
    int rob(vector<int>& nums) {
        if(nums.size() <= 1) return nums.empty() ? 0 : nums[0];
        return max(helper(nums,0,nums.size()-1),helper(nums,1,nums.size()));
    }
    
    int helper(vector<int>& nums,int left, int right){
        int rob = 0;
        int notrob = 0;
        for(int i = left; i < right; ++i){
            int prerob = rob;
            int prenot = notrob;
            rob = prenot + nums[i];
            notrob = max(prerob,prenot);
        }
        return max(rob,notrob);
    }
};