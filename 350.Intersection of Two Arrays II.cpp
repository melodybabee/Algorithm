题意：
找到两个数组中相同的所有元素，在349的基础之上可以有重复
方法1:sort()+while循环
思路：
1.分别对两个数组排序，利用排序好由小到大的性质，分别用两个指针对数组进行while循环
2.循环过程中哪个小移动哪个，直到相等，push到新的数组中，再分别向前移动
class Solution {
public:
    vector<int> intersect(vector<int>& nums1, vector<int>& nums2) {
        vector<int> ret;
        sort(nums1.begin(),nums1.end());
        sort(nums2.begin(),nums2.end());
        int i = 0, j = 0;
        while(i < nums1.size() && j < nums2.size()){
            if(nums1[i] < nums2[j]) ++i;
            else if(nums1[i] > nums2[j]) ++j;
            else{
                ret.push_back(nums1[i]);
                ++i;
                ++j;
            }
        }
        return ret;
    }
};
方法2:unorderd_map
思路：
1.把第一个数组中的所有数字存在一个map中，那么map的key就是数字，value是这个数字的个数
2.再循环第二个数组，如果有这个数字,push进去，在map的相应位置减1
3.注意不能用set,因为无法同时记录数字和数字的个数
class Solution {
public:
    vector<int> intersect(vector<int>& nums1, vector<int>& nums2) {
        unordered_map<int,int>map;
        vector<int> ret;
        for(auto &i : nums1) ++map[i];
        for(int i = 0; i < nums2.size();++i){
            if(map[nums2[i]] > 0){
                ret.push_back(nums2[i]);
                --map[nums2[i]];
            }
        }
        return ret;
    }
};