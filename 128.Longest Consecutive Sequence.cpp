题意：
找到数组中最长的连续子串长度。
方法一：unordered_set
思路：
1.首先建立一个set存入所有的数字
2.开始循环数字，如果没有找到这个数字，那么直接continue跳过。
如果找到了，那么在set中删除掉这个数字，同时对它左右两边的数字进行查找。
用while循环，每查找到一个就继续向前或者向后查找，同时删除掉当前的元素在set中的位置。
3.返回right和left之间最长的长度。
class Solution {
public:
    int longestConsecutive(vector<int>& nums) {
        unordered_set<int>s(nums.begin(),nums.end());
        int ret = 0;
        for(auto n:nums){
            if(!s.count(n)) continue;
            s.erase(n);
            int left = n-1;
            int right = n+1;
            while(s.count(left)) {
                s.erase(left);
                --left;
            }
            while(s.count(right)){
                s.erase(right);
                ++right;
            }
            ret = max(right-left-1,ret);
        }
        return ret;
    }
};