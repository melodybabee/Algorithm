题意：
找到数组中和大于等于目标值的最小子数组。
方法一：滑动窗口
思路：
1.用i作为数组的right边界循环数组，设置一个左边界。每次进入循环求和。
2.当和大于等于目标值且左边界小于右边界的时候，记录此时的长度，每次取小。
此时从和中减去左边界的值，再向右移动左边界，直到与右边界重合或者和小于目标值的时候停止。
3.最后当右边界到达边界的时候，如果长度不变仍为INT_MAX,说明没有找到这个值，返回0；否则返回count.
class Solution {
public:
    int minSubArrayLen(int s, vector<int>& nums) {
        int left = 0;
        int count = INT_MAX;
        int total = 0;
        for(int i = 0; i < nums.size();++i){
            total += nums[i];
            while(left <= i && total >= s){
                count = min(count,i-left+1);
                total -= nums[left];
                ++left;
            }
        }
        return count == INT_MAX? 0 : count;
    }
};
方法二：二分法待学习