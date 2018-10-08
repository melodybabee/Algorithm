题意：
本题为字符匹配，判断s和p两个字符串是否可以匹配
在p中可以出现.或者*，.可以表示任何单个元素，*可以表示0-多个*之前的那个元素
必须全部匹配不可以部分匹配
*********************************************
法1:递归
思路：
1.用p来匹配s,如果p为空，返回看s是否为空
2.如果p的长度为1，看s的长度是否为1同时匹配第一个字符是否为相同或者是.
3.如果p的第二个字符不是*，如果s为空，false，否则匹配第一个字符的同时递归s,p的第二个字符
4.如果p的第二个字符是*,首先看s是否为空同时第一个字符是否匹配，再递归去掉前两个字符的p和s
若匹配返回true,否则s去掉首字母
5.如果s不为空但是首字母不匹配，递归去掉前两个字符的p和s
举例：
s = "aab"
p = "c*a*b"
在p第二个字母是*的情况下，如果不等于s的第一个字符，直接去掉前两个字符，因为*是重复前一位的字符，那么无论*重复多少位仍然不等于s的第一位
目的是首先找到第一位与s匹配的，再判断后面字符
如果只有第一位匹配而后面都不匹配，那么把s去掉首字母再与p比较
isMatch(s,p.substr(2));是*代表的前面的数字为0的情况
class Solution {
public:
    bool isMatch(string s, string p) {
        if(p.empty()) return s.empty();
        if(p.size() == 1)
            return (s.size() == 1 && (s[0] == p[0] || p[0] =='.'));
        if(p[1] != '*'){
            if(s.empty()) return false;
            return (s[0] == p[0] || p[0] =='.') && isMatch(s.substr(1),p.substr(1));
        }
        while (!s.empty() && (s[0] == p[0] || p[0] =='.')){
            if(isMatch(s,p.substr(2))) return true;
            s = s.substr(1);
        }
        return isMatch(s,p.substr(2));
    }
};
简单写法：
class Solution {
public:
    bool isMatch(string s, string p) {
        if (p.empty()) return s.empty();
        if (p.size() > 1 && p[1] == '*') {
            return isMatch(s, p.substr(2)) || (!s.empty() && (s[0] == p[0] || p[0] == '.') && isMatch(s.substr(1), p));
        } else {
            return !s.empty() && (s[0] == p[0] || p[0] == '.') && isMatch(s.substr(1), p.substr(1));//第二个字符不是*
        }
    }
};
*********************************************
方法2:DP
思路：
1
