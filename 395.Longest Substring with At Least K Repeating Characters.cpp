题意：找到字符串中至少重复过k此的最长子字符串长度
方法一：递归
思路：
1.因为满足要求的子字符串必须保证所有的字符都重复过K次，如果不满足那么需要返回0
2.因此需要一个hashmap首先统计下所有字符出现的次数。
3.再开始循环，如果循环到的位置的个数大于K次，那么继续循环。
如果不满足，当坐标到结尾的时候，返回总长度；
如果没有到结尾，那么调用递归，分别计算在当前位置左边和右边的长度，最后返回左右之中较大的值。
注意：
本题的思路即如果遇到不满足条件的字符，那么直接将其舍弃，尽量从它的左右找到最长的返回值。
class Solution {
public:
    int longestSubstring(string s, int k) {
        unordered_map<char,int>map;
        for(int i = 0; i < s.size(); ++i){
            ++map[s[i]];
        }
        int index = 0;
        while(index < s.size() && map[s[index]] >= k) ++index;
        if(index == s.size()) return s.size();
        
        int left = longestSubstring(s.substr(0,index),k);
        int right = longestSubstring(s.substr(index+1),k);
        return max(left,right);
    }
};
【优化方法待学习】