一定要认真审题，题目中写了at most k，表示从1-k都包括！

双重for循环，时间复杂度极高。
思路：
1.循环nums,再从1到k循环k,如果遇到相等的返回true,循环结束仍不相等返回false.
class Solution {
public:
    bool containsNearbyDuplicate(vector<int>& nums, int k) {
        for(int i = 0; i < nums.size();++i){
            for(int j = 1; j <= k && i+j < nums.size(); j++){
            if(nums[i] == nums[i+j]) return true;
            }
        }
        return false;
    }
};

改进：
利用散列表
思路：
1.hashtable中的key是nums中的值，value是这个值在nums中的位置
2.查找hashtable中是否有这个元素，如果有就比较这个值到已有位置的距离是否小于k,如果同时满足，返回true
3.如果没有查找到，把该值添加到map中
注意：
1.map.find(key)来找这个键对应的值在map中是否存在,如果不等于map.end()则表示存在，map.end()为map中的最有一个条目对应的迭代器地址
2.或者可以用map.count（）来判断该键值是否存在
class Solution {
public:
    bool containsNearbyDuplicate(vector<int>& nums, int k) {
        unordered_map<int,int>map;
        for(int i = 0; i<nums.size(); ++i){
            if(map.find(nums[i])!= map.end() && i-map[nums[i]] <= k) return true;
            else{
                map[nums[i]] = i;
            }
        }
        return false;
    }
};