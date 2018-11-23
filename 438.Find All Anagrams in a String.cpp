Anagrams 颠倒的字母
题意：
找到字符串中的所有变位词，返回变位词的第一个坐标位置。
方法一：暴力拆解（数组／hashtable）
思路：
1.用hashtable来写稍微熟练一点，但是会TLE。改为vector之后AC。
class Solution {
public:
    vector<int> findAnagrams(string s, string p) {
        unordered_map<char,int>map;
        vector<int>ret;
        for(auto c : p) ++map[c];
        for(int i = 0; i < s.size(); ++i){
            unordered_map<char,int>temp = map;
            bool flag = true;
            for(int j = i; j < i + p.size(); ++j){
                --temp[s[j]];
                if(temp[s[j]] < 0){
                    flag = false;
                    break;
                }
            }
            if(flag)
            ret.push_back(i);
        }
        return ret;
    }
};
优化：
思路：
1.首先把目标子串的字符输入到vector中进行计数。
2.从头部开始循环s，每次循环p个长度，用一个临时的vector复制原有的vector来对每个字符相应递减
3.一旦字符的个数小于0，那么直接break进入下一层，如果到尾部一直匹配，用一个标记位记录下来，返回的vector中push进去第一位所在的位置。
4.最后返回vector
class Solution {
public:
    vector<int> findAnagrams(string s, string p) {
        vector<int>cnt(128, 0);
        vector<int>ret;
        for(auto c : p) ++cnt[c];
        for(int i = 0; i < s.size(); ++i){
            vector<int> temp = cnt;
            bool flag = true;
            for(int j = i; j < i + p.size(); ++j){
                --temp[s[j]];
                if(temp[s[j]] < 0){
                    flag = false;
                    break;
                }
            }
            if(flag)
            ret.push_back(i);
        }
        return ret;
    }
};
方法二：建立两个vector哈希表，sliding window
思路：
1.用两个vector分别记录下两个字符串中的字符频数。
2.如果在p到末尾时两个vector相等，那么把0push到需要返回的vector中。
3.开始在s的vector中更新s的频数，每新加入一个字符，就减去最前面的那个字符，使在vector中的字符长度一直等于p的长度。
4.每次输入后都比较是否与p的相等，相等的话返回第一个元素的坐标。
注意：
1.两个unordered_map不能直接进行比较是否相等，因此需要设置一个vector类型的哈希表
2.vector中如果放字符的频数的话，根据要求可以创建128或者256大小的vector,那么每个vector对应着一个字符。如果遇到这个字符，那么直接在相应位置+1.
如果是256字符的版本，那么可以在声明的时候就直接创建。
如果是是26个字母的版本，也可以把字符转换为数字即可。
class Solution {
public:
    vector<int> findAnagrams(string s, string p) {
        if(s.empty()) return {};
        vector<int>p1(256,0);
        vector<int>s1(256,0);
        vector<int> ret;
        for(int i = 0; i< p.size();++i){
            ++p1[p[i]];
            ++s1[s[i]];
        }
        if(p1 == s1) ret.push_back(0);
        for(int i = p.size(); i < s.size();++i){
            ++s1[s[i]];
            --s1[s[i-p.size()]];
            if(s1 == p1) ret.push_back(i-p.size()+1);
        }
        return ret;
    }
};
26个字母需要转换成数字的写法。
class Solution {
public:
    vector<int> findAnagrams(string s, string p) {
        vector<int>s1(26,0);
        vector<int>p1(26,0);
        vector<int>ret;
        for(int i = 0; i < p.size() ; ++i){
            ++p1[p[i]-'a'];
            ++s1[s[i]-'a'];
        }
        if(s1 == p1) ret.push_back(0);
        for(int j = p.size(); j < s.size(); ++j){
            ++s1[s[j]-'a'];
            --s1[s[j-p.size()]-'a'];
            if(s1 == p1) ret.push_back(j-p.size()+1);
        }
        return ret;
    }
};

