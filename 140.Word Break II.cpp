题意：
输出所有字符串匹配字典中字符串的情况，139 follow up
memorized DFS 【需要复习】
思路：
1.要求求出是否能满足XX条件的题目，直接用递归或者DP可以轻松做。但是如果要求求出所有可能的情况，DFS／backtracking更加合适。
2.整体思路与139类似，用递归依次向后在字典中寻找对应的单词。
不同之处在于139存储的是是否可以匹配，本题为了提高效率如果一个字符串可以匹配上字典中的值，那么需要记录下这个字符串，后面再遇到直接输出不需要再次进行递归。
如果在递归中不进行结果存储，那么和暴力拆解没有区别。
3.建立一个hashmap用于存储，key是可以匹配上的string，value是匹配上的值。因为最后输出的结果是一个vector<string>类型的数据，所以value需要与其一致。
4.进入递归之后开始在字典中进行遍历，找到字符串中第一个与字典中匹配的单词，用一个临时数组再记录下其后面字符串递归得到的结果。
5.如果s到达末尾，因为还需要处理空格问题，为了区分是最后一位，s到达末尾之后标记为""
6.开始处理结果数组，如果不为空，即不是最后一位，那么直接在后面加上空格，如果为空，那么置为空即可
7.在每次内部循环结束之后，在map中更新对应关系，存入map
class Solution {
public:
    vector<string> wordBreak(string s, vector<string>& wordDict) {
        unordered_map<string,vector<string>> m;
        return helper(s,wordDict,m);
    }
    
    vector<string> helper(string s,vector<string>& wordDict, unordered_map<string,vector<string>>&m){
        if(m.count(s)) return m[s];
        if(s.empty()) return {""};
        vector<string> res;
        for(auto w : wordDict){
            if(s.substr(0,w.size()) != w) continue;
            vector<string> temp = helper(s.substr(w.size()),wordDict,m);
            for(auto str: temp){
                res.push_back(w + (str.empty() ? "" : " ") + str);
            }
        }
        m[s] = res;
        return res;
    }
};

