题意：
不改变数组找到数组中重复的元素。
方法一：Pigeonhole principle，抽屉原理
思路：【重点复习】
1.因为题目中说明了数字是1-N，共有N+1个数字，那么必有一个重复。因为是从1开始的，所以可以巧妙的运用数组的坐标进行判断。
2.从1开始到结束位置的坐标，左右指针找到中点。遍历数组，找到比小于等于中点坐标值的所有数字的个数。
如果数量大于中点坐标值，表明在1-中点的范围内有重复的数字，才会使个数大于中点值，那么right移动到中点，再次循环。
如果数量小于等于中点坐标值，说明中点-末尾的范围内有重复的数字，把left移动到中点+1，再次循环。
class Solution {
public:
    int findDuplicate(vector<int>& nums) {
        int left = 1;
        int right = nums.size()-1;
        while(left < right){
            int mid = left + (right - left)/2;
            int count = 0;
            for(int i = 0 ; i < nums.size();++i){
                if(nums[i] <= mid) ++count;
            }
            if(count > mid) right = mid;
            else left = mid+1;
        }
        return right;
    }
};
方法二：快慢指针成环判断,类似142题
思路：
1.设置快慢指针，快一次走两步，慢一次走一步，因为存在环，所以一定会相遇。
注意在数组里面走一步还是两步是用借助坐标完成的。
2.再把其中一个指针设置成原点，两个指针一步一步走，再次相遇位置即为环的起点。
3.数值只会在坐标值的范围内，因为相遇与否指的是坐标值，所以最后返回的是坐标值。
class Solution {
public:
    int findDuplicate(vector<int>& nums) {
        int low = 0; 
        int fast = 0;
        while(true){
            low = nums[low];
            fast = nums[nums[fast]];
            if(fast == low) break;
        }
        low = 0;
        while(low != fast){
            low = nums[low];
            fast = nums[fast];
        }
        return low;
    }
};