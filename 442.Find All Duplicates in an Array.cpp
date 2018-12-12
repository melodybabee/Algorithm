题意：
找到数组中出现2次的数字。
方法一:unordered_map
思路：
1.首先用hashmap对数组中的数字进行计数。
2.清空数组，开始遍历map,如果在map中value为2，push进去第一位的值
class Solution {
public:
    vector<int> findDuplicates(vector<int>& nums) {
        unordered_map<int,int>map;
        for(auto a:nums) ++map[a];
        nums.clear();
        for(auto it : map){
            if(it.second == 2) nums.push_back(it.first);
        }
        return nums;
    }
};

方法2:交换
思路：
1.每个数字应该与数组坐标的位置+1的位置上，从头开始循环，如果不在，那么交换。
2.交换到数组结尾之后如果再次循环判断是否是在对应位置上，如果不是就是重复元素，输入到返回数组中。
class Solution {
public:
    vector<int> findDuplicates(vector<int>& nums) {
        vector<int>ret;
        for(int i = 0; i < nums.size();++i){
            if(nums[i] != nums[nums[i]-1]){
                swap(nums[i],nums[nums[i]-1]);
                --i;
            }
        }
        
        for(int i = 0;i < nums.size();++i){
            if(nums[i] != i+1) ret.push_back(nums[i]);
        }
        
        return ret;
    }
};