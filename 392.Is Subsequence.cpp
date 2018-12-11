题意：判断一个字串中是否包含另一个字符串。
方法一：分别遍历
思路：
1.设置两个指针分别循环两个字符串，能找到，目标字符串+1，没有找到跳过。
2.返回目标字符串的指针是否到了末尾。
class Solution {
public:
    bool isSubsequence(string s, string t) {
        int i = 0;
        int j = 0;
        for(i = 0 ; i < t.size();++i){
            if(s[j] == t[i]){
                ++j;
            }
        }
        return j == s.size();
    }
};
【follow up待思考】