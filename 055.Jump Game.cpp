题意：
从头部开始遇到的数字可以跳跃1到此数字步，判断能否跳到数组尾部。
方法一：递归回溯，会TLE
T(n)= 2^n, S(n) = O(n);
思路：
1.从头结点开始递归，如果等于数组长度，返回true
2.如果不等，就从当前位置开始相加1-n位，再在过程中进行递归。遇到等于数组长度的时候返回true,循环结束仍没有找到返回false
class Solution {
public:
    bool canJump(vector<int>& nums) {
        return Jump(nums,0);
    }
    bool Jump(vector<int>&nums, int position){
        if(position == nums.size()-1) return true;
        for(int i = 1; i<= nums[position];++i){
            if(Jump(nums,position+i)) return true;
        }
        return false;
    }
};
方法二：DP
T(n)= O(n), S(n) = O(n)；
思路：
1.建立一个数组存入当前位置还剩余的步数，如果剩余的步数小于0，那么直接返回false
2.剩余的步数是前一位的值和前一位nums中的值中较大的一个再减去1
3.最后循环结束判断新数组的最后一位是否大于等于0，如果是，返回true
class Solution {
public:
    bool canJump(vector<int>& nums) {
        vector<int> dp(nums.size(),0);
        for(int i = 1; i< nums.size();++i){
            dp[i] = max(dp[i-1],nums[i-1])-1;
            if(dp[i] < 0) return false;
        }
        return dp.back() >= 0;
    }
};
方法三：greedy，贪心算法
T(n)= O(n), S(n) = O(1)；
思路：
1.其实基于方法二并不关心在每一步上还剩下多少步，只需要判断能否到达最远位置即可
2.设立一个变量g,初始值为0，表示可以到达的最远位置。如果遍历到的点大于g或者g已经超出数组范围，跳出循环。
遍历到的点大于g说明g不能到达这一步，结果是为false的。
3.一般情况下比较g和它循环到的位置的点的坐标+代表的值，表示能到达的最远距离。
4.最后判断最远距离能否大于等于数组长度。
class Solution {
public:
    bool canJump(vector<int>& nums) {
        int n = nums.size();
        int g = 0;
        for(int i = 0; i< nums.size();++i){
            if(i > g || g > n-1) break;
            g = max(nums[i]+i,g);
        }
        return g >= n-1 ? true: false;
    }
};