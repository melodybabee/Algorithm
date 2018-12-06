题意：
在旋转的array中找到目标元素的index
T(n) = O(logn),有log的想二分法
思路：
1.与常规的二叉搜索不同，因为array在旋转，不知道应该在哪半边继续查找target,所以需要多加一层判断。
通过观察发现：
（1）如果target==A[m]，那么m就是结果，直接返回；
（2）如果A[m]<A[r]，那么说明从m到r一定是有序的（没有受到rotate的影响），那么我们只需要判断target是不是在m到r之间，如果是则把左边缘移到m+1，否则就target在另一半，即把右边缘移到m-1。
（3）如果A[m]>=A[r]，那么说明从l到m一定是有序的，同样只需要判断target是否在这个范围内，相应的移动边缘即可。
注意：
1.找中值要用mid= l + (r-l)/2;避免溢出
class Solution {
public:
    int search(vector<int>& nums, int target) {
        int l = 0;
        int r = nums.size()-1;
        while(l <= r){
            int mid= l + (r-l)/2;
            if(nums[mid] == target) return mid;
            else if(nums[mid] < nums[r]){
                if(nums[mid] < target && nums[r] >= target) l = mid+1;
                else{
                    r= mid-1;
                }
            }else{
                if(nums[mid] > target && nums[l] <= target) r = mid-1;
                else{
                    l= mid+1;
                }
            }
        }
        return -1;
    }
};

12.5复习
注意：
1.如果是不旋转的数组从中间开始查找逐渐缩小范围。
2.那么旋转数组的问题在于查找完中间元素之后不知道应该往哪一侧移动，因此需要判断移动方向。
从中点开始，如果中点的值小于右边界的值，说明有半侧是增序的，那么判断target是否在这个范围内，如果在左边界移动，如果不在右边界移动。
同理，如果中点值小于右边界的值，说明数组的前半部分有序，头结点的位置已经过半，那么看target是否在左半侧的范围内，如果在，移动右边界，如果不在移动左边界。
3.如果找不到最后返回-1
4.在while循环里，最后的条件是左右相等，当左右相等的时候需要判断当前元素是否等于目标值，处理只有一个元素的情况
class Solution {
public:
    int search(vector<int>& nums, int target) {
        int left = 0;
        int right = nums.size()-1;
        while(left <= right){
            int mid = left + (right-left)/2;
            if(nums[mid] == target) return mid;
            if(nums[mid] < nums[right]){
                if(target <= nums[right] && target > nums[mid]){
                    left = mid+1;
                }else{
                    right = mid-1;
                }
            }else{
                if(target < nums[mid] && target >= nums[left]){
                    right = mid-1;
                }else{
                    left = mid +1;
                }
            }
        }
        return -1;
    }
};