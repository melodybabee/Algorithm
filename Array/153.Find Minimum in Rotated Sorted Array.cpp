题意：
在一个已经排序过的旋转数组中找到最小的元素。
方法一：暴力循环
思路：
1.循环数组，遇到后面比它小的直接输出，如果没有，输出第一个。
class Solution {
public:
    int findMin(vector<int>& nums) {
        for(int i = 0; i < nums.size();++i){
            if(i >=1 && nums[i] < nums[i-1]) return nums[i];
        }
        return nums[0];
    }
};
方法二：二叉搜索
思路：
1.因为数组已经被升序不重复排列好，因此如果头小于尾，说明头部就是最小的数字，直接返回即可。
2.如果头大于尾，那么直接找到中点，如果中点到头部是升序的，说明最小值在后半部分，否则最小值在前半部分。
class Solution {
public:
    int findMin(vector<int>& nums) {
        int start = 0;
        int end = nums.size()-1;
        while(start < end){
            if(nums[start] < nums[end]) return nums[start];
            
            int mid = start + (end - start)/2;
            if(nums[mid] >= nums[start]){
                start = mid +1;
            }else{
                end = mid;
            }
        }
        return nums[start];
    }
};

12.5复习：
1.一次二叉搜索+暴力拆解
class Solution {
public:
    int findMin(vector<int>& nums) {
        int ret = INT_MAX;
        int left = 0; 
        int right = nums.size()-1;
        int mid = left+ (right-left)/2;
        if(nums[mid] <= nums[right]){
            for(int i = left; i <= mid; ++i){
                ret = min(ret,nums[i]);
            }
        }else{
            for(int i = mid+1; i <= right;++i){
                ret = min(ret,nums[i]);
            }
        }
        return ret;
    }
};
2.方法2:
注意：
1.首先判断是否左小于右，如果是，直接输出第一个元素。所有被旋转过的数组头都会大于尾。
2.不断把范围缩小至包含较小值的一方，注意缩小时右边界的范围需要包含进来，不可跳过。
3.不断缩小，直到两个指针相遇时为最小值。
class Solution {
public:
    int findMin(vector<int>& nums) {
        int left = 0; 
        int right = nums.size()-1;
        while(left < right){
            if(nums[left] < nums[right]) return nums[left];
            int mid = left + (right-left)/2;
            if(nums[mid] < nums[right]){
                right = mid;
            }else{
                left = mid+1;
            }
        }
        return nums[left];
    }
};