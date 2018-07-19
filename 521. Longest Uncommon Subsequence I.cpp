/*个人思路
class Solution {
public:
    int findLUSlength(string a, string b) {
        int ret1 = 0;
        int ret2 = 0;
        int ret = 0
        vector<int> ans;
        if(a==b) return -1;
        for(int i=0; i < a.size() && i < b.size();++i){
            if(a[i] ！= b[i])
                ret1 = i;
            else{
                ret2 = i;
                ret = ret2-ret1;
                ans.push_back(ret);
            }
        }
        return ret;
    }
};*/

//标准解法
class Solution {
public:
    int findLUSlength(string a, string b) {
        if(a==b) return -1;
        if(a.size() >= b.size()) return a.size();
        else return b.size();
    }
};


/*
本题思路和标准的有出入，我的思路是：
1.最大的非子串是两个string中不同部分最长的子串长度
e.g. asdfbbbbbasdf 和 abcfbbbbabcde 
开始部分虽然不同，但不是最长的子串，长度为3
最后部分的长度是5，因此返回5

2.但是上述想法的问题在于不应该去判断字符，应该去比较字符串
而且当长度不同、或者有不同小段的长度时还需要再次比较从而取最大值
如果设立双指针的话，一旦字符不同将第一个指针设立为初始位置，字符相同的时候放置第二个指针，所求的长度相减，再依次放到vector中进行比较
但是如果先出现相同的值实现起来会比较复杂，需要进一步思考更好的解法。

3.因此直接考虑最简单的情况，如果两个string相同，返回-1
如果不同，直接返回较长长度的string
*/