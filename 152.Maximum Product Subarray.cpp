题意：
求最大子数组乘积
方法一：DP
1.对于这种求极限／局部最优的问题通常通过DP解决，一开始想的是用一个二维数组dp[i][j]记录下[i,j]范围内的最大乘积。但是会出现两个问题：
(1)如果设置二维数组，那么i>j的情况是不存在数值的，等于使用的只有二分之一个二维数组。
同时初始值是对角线上的四个值，没有办法找到动态转移方程，因此不可行。后面再有类似的问题（之前还有类似的问题）要重新考虑DP数组的设置／换用别的方法。
(2)本题DP的思路没有问题，但是还有一个难点在于求乘积有0和负数的障碍。
如果当前的最大值乘上一个负数那么就会变成最小值。
2.因此解决本题需要两个DP数组，一个来更新最大值，一个来更新最小值，最后的结果取最大值的数组中的较大值。
3.更新数组的过程中需要再最大值数组，最小值数组和这个值本身三者之间比较。
注意：
返回的结果的初始值是第一个元素，不能是INT_MIN;
class Solution {
public:
    int maxProduct(vector<int>& nums) {
        vector<int> l(nums.size(),nums[0]);
        vector<int> r(nums.size(),nums[0]);
        int ret = nums[0];
        for(int i = 1; i < nums.size();++i){
            l[i] = max(max(l[i-1]*nums[i],r[i-1]*nums[i]),nums[i]);
            r[i] = min(min(l[i-1]*nums[i],r[i-1]*nums[i]),nums[i]);
            ret = max(ret,l[i]);
        }
        return ret;
    }
};
优化：
除了暴力比较三者意外，也可以通过遍历到的值的正负分情况讨论。
注意：
1.在遍历到的值小于0的时候，需要一个temp值来记录下Max的值，不然更新之后在min中使用的是更新之后的值。
class Solution {
public:
    int maxProduct(vector<int>& nums) {
        int l = nums[0];
        int r = nums[0];
        int ret = nums[0];
        for(int i  = 1; i < nums.size();++i){
            if(nums[i] > 0){
                l = max(l*nums[i],nums[i]);
                r = min(r*nums[i],nums[i]);
            }else{
                int temp = l;
                l = max(r*nums[i],nums[i]);
                r = min(temp*nums[i],nums[i]);
            }
            ret = max(ret,l);
        }
        return ret;
    }
};
优化：
上面分了正负的情况讨论，其实在负数的情况下直接交换当前值再进行操作即可。正数就正常更新。
class Solution {
public:
    int maxProduct(vector<int>& nums) {
        int l = nums[0];
        int r = nums[0];
        int ret = nums[0];
        for(int i  = 1; i < nums.size();++i){
            if(nums[i] < 0)swap(l,r);
            l = max(l*nums[i],nums[i]);
            r = min(r*nums[i],nums[i]);
            ret = max(ret,l);
        }
        return ret;
    }
};
方法二：正反两次遍历
思路：
1.本题容易出现问题的地方就是因为负数的存在，会导致奇数次负数相乘得不到最大值，会使最大值和最小值反转。
2.那么反向再次遍历一次会避免奇数次负数的存在。注意反向遍历不是建立在正向遍历的基础之上的，就是重新开始遍历。
目标是找到遍历过程中的最大值。
class Solution {
public:
    int maxProduct(vector<int>& nums) {
        int res = nums[0];
        int temp = 1;
        for(int i = 0; i < nums.size(); ++i){
            res = max(res, temp *=nums[i]);
            if(nums[i] == 0) temp =1;
        }
        temp = 1;
        for(int i = nums.size()-1; i >= 0; --i){
            res = max(res,temp *= nums[i]);
            if(nums[i] == 0) temp =1;
        }
        return res;
    }
};