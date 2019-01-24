题意：同时找到满足数值范围和数值下标范围的数字。
方法一：unordered_map遍历
TLE
思路：分别判断k和t,当数据量过大的时候一个一个遍历会TLE。
class Solution {
public:
    bool containsNearbyAlmostDuplicate(vector<int>& nums, int k, int t) {
        unordered_map<int,int>map;
        for(int i = 0; i < nums.size(); ++i){
            for(int j = -t; j <= t; ++j){
                if(map.count(nums[i] +j)){
                    if(i-map[nums[i]+j] <= k) return true;
                }
            }
            map[nums[i]] = i;
        }
        return false;
    }
};
方法2:set+截取
思路：
1.用一个set来存取遍历到的数字，开始遍历数组。每当遍历到的位置大于指定的K的之后，就把set中在K及以前的数组删除。
2.用lower_bound()函数来找到set中第一个大于等于遍历到的数字-t的值，如果可以找到这个值，同时这个值还小于遍历到的数组+t,那么返回true
3.在set中插入当前遍历到的值。
4.如果到最后没有找到，返回false
注意：
1.lower_bound()是找到大于等于当前元素的值的位置，是一个指针形式的变量。
如果想取该变量的值，要对指针做取值计算，为*it
2.只有map和set有lower_bound(),upper_bound()函数(严格大于),因为是由BST构成的，哈希表不可以有这个函数
3.因为有INT_MIN和INT_MAX等边界条件，需要换成long long类型的。set中写成long long或者long都可以
class Solution {
public:
    bool containsNearbyAlmostDuplicate(vector<int>& nums, int k, int t) {
        set<long>set;
        for(int i = 0; i < nums.size();++i){
            if(i > k) set.erase(nums[i-k-1]);
            auto it = set.lower_bound((long)nums[i]-t);
            if(it != set.end() && *it <= (long)nums[i]+(long)t) return true;
            set.insert(nums[i]);
        }
        return false;
    }
};