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