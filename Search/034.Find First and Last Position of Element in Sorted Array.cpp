题意：
在一个已经排序的数组里面找到目标元素的index.如果有多个，返回[起始坐标，结束坐标]。如果没有返回[-1,-1].
T(n) = O(logn);
思路：
1.时间复杂度为logn，那么用到二分的方法
2.首先跟常规二分法一样找到一个目标元素，把它设置为返回数组的左边界结点
3.再用一次二分查找找右边界，得到的结果放到返回数组的右边界结点
注意：
1.在找右边界结点的时候注意r的新取值范围,和找到target值时左边界的位置，以及返回到vector中的左边界的位置。
因为需要这一步if(nums[mid] <= target) l = mid+1;来找到左边界，所以如果l不加1那么永远会落到这个循环中，因此加1。
那么这点的坐标就是mid的下一位，因此在返回到ret的时候需要-1；
即然-1了，那么如果一开始找到的左边界就是唯一的目标值且在数组的最后一位的话，那么返回的index就会少一位，因此需要把r的新的范围定在r = nums.size();这样一定会进入while循环
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

12.11复习：
注意：分别找到左边界和右边界再更新。需要提前判断为空或者不存在的情况。
class Solution {
public:
    vector<int> searchRange(vector<int>& nums, int target) {
        int left= 0;
        int right = nums.size();
        vector<int> ret{-1,-1};
        if(nums.empty()) return ret;
        if(target > nums[nums.size()-1] || target < nums[0]) return ret;
        while(left < right){
            int mid = left + (right - left)/2;
            if(nums[mid] < target) left = mid+1;
            else right = mid;
        }
        if(nums[left] != target) return ret;
        ret[0] = left;
        right = nums.size();
        while(left < right){
            int mid = left +(right -left)/2;
            if(nums[mid] > target) right = mid;
            else left = mid+1;
        }
        ret[1] = right-1;
        return ret;
    }
};
