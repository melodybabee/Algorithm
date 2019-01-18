题意：
找到当前数组中的每一个数字在对应的数组右侧比当前数值大的最近的值。
方法一：hashtable
思路：
1.先用比较数组更新map，找到当前值中在它右侧比它大的值，作为value.如果没有找到比它大的值，那么对应为-1
2.再遍历原数组，找到对应的数字比自己大的值。
注意：
1.要分别讨论两个数组为空的情况
class Solution {
public:
    vector<int> nextGreaterElement(vector<int>& findNums, vector<int>& nums) {
        if(findNums.empty()) return findNums;
        if(nums.empty()) return vector<int>(findNums.size(),-1);
        unordered_map<int,int>map{{nums.back(),-1}};
        for(int i = nums.size()-2; i >= 0; --i){
            for(int j = i+1; j < nums.size(); ++j){
                if(nums[j] > nums[i]){
                    map[nums[i]] = nums[j];
                    break;
                }
            }
            if(!map.count(nums[i])) map[nums[i]] = -1;
        }
        
        for(int i = 0; i < findNums.size(); ++i){
            findNums[i] = map[findNums[i]];
        }
        return findNums;
    }
};
优化：
在更新原数组到map的时候可以构建一个栈，如果此时栈不为空，且栈顶元素小于当前数字，说明当前数字就是栈顶元素的右边第一个较大数，那么建立二者的映射，并且去除当前栈顶元素。
最后将当前遍历到的数字压入栈进行下一次的比较。