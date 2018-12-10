题意：找string中最长的substring
------------------------------
思路1:暴力拆解
首先用两个for循环枚举出string中包含的所有substring，再用一个for循环判断该subdtring中是否有重复的字符。
T(O) = n^3;
------------------------------
思路2；Sliding Window／尺取法／双指针法
T(O) = n;
1.用一个vector来记录字母出现的位置的映射，注意vector中存放的是该字母最近一次出现的位置。
也就是说，如果重复出现了某个字母，vector中放的是最新一次出现的位置。
2.创建一个滑动窗口，窗口的左边界是left,右边界是当前遍历到的字母的位置，窗口内存放的是没有重复的元素集合。
3.如果新遍历到的元素没有存在过，那么直接加入。
4.如果新遍历的元素存在，需要再判断这个元素是否在窗口内，如果不在，那么仍然直接加入；如果存在，需要将左边界移动到该元素的位置作为新的边界。
补充：
1.整型数组大小是256位，因为ASCII 码使用指定的7 位或8 位二进制数组合来表示128 或256 种可能的字符。最多只有256种可能。
class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        vector<int> vec(256,-1);
        int left = 0;
        int  ret = 0;
        for(int i = 0; i< s.size() ;++i){
            if(vec[s[i]] == -1 || left > vec[s[i]]){
                ret = max(i-left+1,ret);
            }else{
                left = vec[s[i]];
            }
            
            vec[s[i]] = i;
        }
        return ret;
    }
};

代码写法简化：
class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        vector<int> vec(256,-1);
        int left = 0;
        int  ret = 0;
        for(int i = 0; i< s.size() ;++i){
            left = max(vec[s[i]],left);//一直保持在重复元素最近的位置上
            vec[s[i]] = i;
            ret = max(i-left+1,ret);
        }
        return ret;
    }
};
运用hashmap:
class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        int res = 0, left = 0, i = 0, n = s.size();
        unordered_map<char, int> m;
        for (int i = 0; i < n; ++i) {
            left = max(left, m[s[i]]);
            m[s[i]] = i + 1;
            res = max(res, i - left + 1);
        }
        return res;
    }
};

12.10复习：
注意：
1.用一个left指针指向左边界，循环到的i指向右边界，每次的最长长度是i-left+1
2.用一个hashmap来记录下遍历到的字符在字符串中的位置，如果遇到重复的就及时更新。
注意每个字符的位置是它i遍历到的位置+1.
最开始的时候left会在0的位置，后面依次更新到遍历到的字符所在的位置坐标上。
class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        unordered_map<char,int>map;
        int left = 0;
        int ret = 0;
        for(int i = 0; i< s.size();++i){
            left = max(left,map[s[i]]);
            map[s[i]] = i+1;
            ret = max(ret,i-left+1);
        }
        return ret;
    }
};