题意：
找到数组中子数组和等于目标值的最长长度。
思路：
1.这种在数组中找子数组的问题首先想到用two pointers来解决问题。
本题不一样的是需要找子区间，那么正负数都存在，所以加和的结果不能确定，不能明确的知道什么时候移动左边界，因此换一种思路。
2.由于需要找子数组，那么同样设置一个变量计算所有数字的和，同时把这个和放入一个map中，map的value对应的是当前和所在的坐标。
3.每次遍历后，如果直接与目标值相等，那么直接返回坐标值+1，因为左边界一直不动，因此就是当前的长度
而如果不直接相等，而是在map中找到了当前和-目标值对应的key,那么返回此时的坐标-对应的数组中的坐标值，结果值取较大的一个
注意：
1.因为本题中最小值为0，所以结果值的初始值设置为0即可，不要一求较大久就盲目的设置为INT_MIN,因为不满足条件或者为空的时候是需要返回这个值的。
class Solution {
public:
    int maxSubArrayLen(vector<int>& nums, int k) {
        int ret = 0;
        int total = 0;
        unordered_map<int,int>map;
        for(int i = 0; i < nums.size(); ++i){
            total += nums[i];
            if(total == k) ret = i+1;
            else if(map.count(total-k)) ret = max(ret,i-map[total-k]);
            if(!map.count(total)) map[total] = i;
        }
        return ret;
    }
};