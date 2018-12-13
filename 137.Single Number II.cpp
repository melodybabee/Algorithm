题意：136 follow up，一个数字出现3次剩下的出现1次，找出出现一次的元素
方法一：HashTable
class Solution {
public:
    int singleNumber(vector<int>& nums) {
        unordered_map<int,int>map;
        for(auto a:nums)++map[a];
        for(auto it :map){
            if(it.second == 1) return it.first;
        }
    }
};
方法2:位运算
【待学习】