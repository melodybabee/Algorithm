题意：
在旋转的有重复元素的数组中找到最小值。153 follow up and 081 follow up.
思路：
1.就是081和153的结合，081是用来处理重复元素，那么只要中间值和尾部元素值相等，把右指针向前移动一位重新进入循环。
2.再结合153找最小元素，如果一开始左就小于右，那么直接输出左指针指向的元素。
用二分法每次向有较小值的一侧不断缩小范围，最后返回左指针与右指针重合位置的值。
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
            }else if(nums[mid] > nums[right]){
                left = mid +1;
            }else{
                --right;
            }
        }
        return nums[left];
    }
};
