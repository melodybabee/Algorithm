题意：判断数组中的数字是否能分成两个非空数组的集合
方法一：遍历
TLE。
方法二：DP
思路：
1.首先用accumulate()来计算数组中所有数字的和，如果是奇数，那么直接返回false
2.创建目标值，建立dp数组dp[i]表示数字i是否是原数组的任意个子集合之和，最后返回dp[数组总和的一半]
3.开始遍历数字，从目标位置开始向前遍历，如果dp[i-当前遍历到的数字]为真，那么dp[i]就也为真
4.最后到数字循环结束之后，返回dp[数组总和的一半]的性质
class Solution {
public:
    bool canPartition(vector<int>& nums) {
        int total = accumulate(nums.begin(),nums.end(),0);
        if(total %2 == 1) return false;
        int temp = total/2;
        vector<bool>dp(temp+1,false);
        dp[0] = true;
        for(auto n : nums){
            for(int i = temp; i >= n; --i){
                dp[i] = dp[i] || dp[i-n];
            }
        }
        return dp[temp];
    }
};
方法3:bitset
思路：
1.注意bitset只不过是set的一种，其中10001表示的是set的容量，1是初始值
2.首先计算数组的和，注意accumulate(）函数需要有一个初始的求和值0
3.遍历所有数字，bits的值是每次移动当前遍历到的数组个距离，再与之前的bits作或运算,set中的每一位上如果为0就表示数组可以相加得到该坐标值
4.最后返回和是否是偶数，以及在set中的总和一半的位置是否是true
class Solution {
public:
    bool canPartition(vector<int>& nums) {
        bitset<10001>bits(1);
        int total = accumulate(nums.begin(),nums.end(),0);
        for(auto n : nums)bits |= bits << n;
        return total %2 == 0 && bits[total/2];
    }
};