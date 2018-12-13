题意：判断两个字符串是否能够通过一次编辑由一个变成另一个
思路：
1.分情况讨论，如果两个字符串的长度差大于2，那么肯定不能，直接返回false
2.如果字符串长度差等于1，那么开始循环，如果找到不同的元素，判断长的字符串剩下部分是否与短的相等。
注意为了便于循环，在最开始需要知道那个长，把长的字符串交换到第一位的位置。
3.如果长度相等，最多允许一位不同，那么设置一个计数器，如果不同+1，最后判断计数器是否等于1。
class Solution {
public:
    bool isOneEditDistance(string s, string t) {
        if(s.size() < t.size()) swap(s,t);
        int diff = s.size()-t.size();
        if(diff >= 2) return false;
        else if(diff == 1){
            for(int i = 0; i < s.size();++i){
                if(s[i] != t[i]) return s.substr(i+1) == t.substr(i);
            }
        }else{
            int count = 0;
            for(int i = 0; i < s.size();++i){
                if(s[i] != t[i]) ++ count;
            }
            return count ==1;
        }
    } 
};