题意：
在一个已经排序的数组里面找到目标元素的index.如果有多个，返回[起始坐标，结束坐标]。如果没有返回[-1,-1].
T(n) = O(logn);
思路：
1.时间复杂度为logn，那么用到二分的方法
2.首先跟常规二分法一样找到一个目标元素，把它设置为返回数组的左边界结点
3.再用一次二分查找找右边界，得到的结果放到返回数组的右边界结点
注意：
1.在找右边界结点的时候注意r的新取值范围,和找到target值时左边界的位置，以及返回到vector中的左边界的位置。
class Solution {
public:
    vector<int> searchRange(vector<int>& nums, int target) {
        vector<int> ret(2,-1);
        if(nums.empty()) return ret;
        if(target > nums[nums.size()-1] || target < nums[0]) return ret;
        int l = 0;
        int r = nums.size()-1;
        while(l < r){
            int mid = l + (r-l)/2;
            if(nums[mid] < target) l = mid+1;
            else{r = mid;}
        }
        if(nums[l] != target) return ret;
        ret[0] = l;
        r = nums.size();
        while(l < r){
            int mid = l + (r-l)/2;
            if(nums[mid] <= target) l = mid+1;
            else{r = mid;}
        }
        ret[1] = l-1;
        return ret;
    }
};