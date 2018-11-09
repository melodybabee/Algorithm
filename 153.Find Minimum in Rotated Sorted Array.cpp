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