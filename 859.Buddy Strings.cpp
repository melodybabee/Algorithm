题意：
判断两个字符串能否值交换两个字符得到相等的字符串。
思路：
1.题目本身没有难度，但是有很多corner cases需要想清楚。注意需要交换，同时必须交换2个
2.首先A，B都为空或者其中一个为空的时候返回false
A，B长度不等的时候直接返回false
3.如果A，B相等需要判断在字符串中有至少2个相同过的字符，那么用一个set把字符串中的字符输入，利用set去重的性质，如果set的大小小于字符串，返回true
4.再同时遍历A和B，如果不等，那么用一个数组记录下他们的位置，最后判断数组的长度是否为2，同时交换两个字符串中该位置上的字符是否相等
class Solution {
public:
    bool buddyStrings(string A, string B) {
        if(A.empty() || B.empty()) return false;
        if(A.size() != B.size()) return false;
        if (A == B && set<char>(A.begin(), A.end()).size() < A.size()) return true;
        vector<int>temp;
        for(int i = 0; i < A.size(); ++i){
            if(A[i] != B[i]) temp.push_back(i);
        }
        return temp.size() == 2 && A[temp[0]] == B[temp[1]] && A[temp[1]] == B[temp[0]];
    }
};