题意：判断一个字符串中有多少个回文的子字符串
方法一：暴力求解
T(n) = O(n^2);
思路：
1.首先用两个for循环遍历出所有的子串，再判断这个子串是否是回文的。
如果是，那么计数器+1；如果不是跳过。
2.在判断是否是回文的方法中，设立首尾两个指针来进行while循环，如果相等，指针向中间移动，如果不等就返回false
class Solution {
public:
    int countSubstrings(string s) {
        int count = 0;
        for(int i = 0; i < s.size();++i){
            for(int j = i; j < s.size();++j){
                if(ispal(s.substr(i,j-i+1))) ++count;
            }
        }
        return count;
    }
    
    bool ispal(string str){
        int left = 0;
        int right = str.size()-1;
        while(left < right){
            if(str[left] == str[right]){
                ++left;
                --right;
            }else{
                return false;
            }
        }
        return true;
    }
};
暴力求解优化：
思路：
1.依然从头部开始循环，每循环到一个位置分别判断以它为中心的的奇数字符串和偶数字符串是否是回文的
j遍历的是每次需要相加上的长度，只要头部大于0，尾部小于长度，同时两个字符相等的话就是回文的，计数器+1
class Solution {
public:
    int countSubstrings(string s) {
        int count = 0;
        for(int i = 0; i < s.size();++i){
            for(int j = 0; i-j >= 0 && i+j < s.size() && s[i-j] == s[i+j];++j) ++count;
            for(int j = 0; i-1-j >= 0 && i+j < s.size() && s[i-1-j] == s[i+j]; ++j) ++count;
        }
        return count;
    }
};