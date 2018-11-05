题意：
用后面数字替换数组中重复大于两次的数字，返回替换后的结果。
思路：
1.因为数组是被排序好的，因此只要某个元素不大于其前面第二位元素，说明此位应该被后面数字替换。
2.因此循环数组，如果i小于1或者循环到的位置大于其前面第二位数字，那么就从头部更新数组，index+1；
3.如果其等于前面第二位数字，跳过。最后返回index。
注意：
因为index每次更新后都会指向数组下一位待更新的位置，因此返回的时候直接返回index即可。
同时原数组中和前面第二位比较，比较的是新数组的前两位，即index-2;
class Solution {
public:
    int removeDuplicates(vector<int>& nums) {
        int index = 0;
        for(int i = 0; i< nums.size();++i){
            if(i <= 1 || nums[i] > nums[index-2]){
                nums[index] = nums[i];
                ++index;
            }
        }
        return index;
    }
};

