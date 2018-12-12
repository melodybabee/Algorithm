题意：找出数组中的第一个山峰的值
方法一：遍历
1.从头开始遍历，如果该位比前一位和后一位都大，那么返回其坐标位置。
2.注意判断越界问题，如果超出范围的不能返回，还要考虑山峰在最后一位时的情况，直接返回最后一位。
3.其他情况比如第一位最大或者只有一个元素那么就返回0。
class Solution {
public:
    int findPeakElement(vector<int>& nums) {
        for(int i = 1; i < nums.size();++i){
            if(nums[i]>nums[i-1] && nums[i] > nums[i+1] && i+1 < nums.size()) return i;
            else if(nums[i]>nums[i-1]&& i+1 ==nums.size()) return nums.size()-1;
            
        }
        return 0;
    }
};
优化：
找到波谷即可，如果没有找到那么返回最后一位。
class Solution {
public:
    int findPeakElement(vector<int>& nums) {
        for(int i = 1; i < nums.size();++i){
            if(nums[i]<nums[i-1]) return i-1;
        }
        return nums.size()-1;
    }
};

方法2:二叉搜索
思路：
1.注意中点找其中一边判断条件即可，满足就移动当前边，不满足就移动另一边的条件。
2.最后返回重合点。
class Solution {
public:
    int findPeakElement(vector<int>& nums) {
        int left = 0;
        int right = nums.size()-1;
        while(left < right){
            int mid = left + (right -left)/2;
            if(nums[mid] < nums[mid+1])left = mid+1;
            else right = mid;
        }
        return left;
    }
};