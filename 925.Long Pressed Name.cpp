题意：
给一个名字，一个匹配字符串，匹配的字符串中间的字符可以无限重复仍然是匹配的，判断是否匹配。
思路：
1.如果其中一方为空或者匹配串的长度小于名字，直接返回false
2.从匹配串开始循环，名字串从第0为开始，如果匹配，逐渐增加，不匹配，如果匹配串与前一位重复，继续循环否则名字串归0从头开始循环
3.如果在循环中或者循环结束名字串到达结尾，那么返回true,否则返回false
class Solution {
public:
    bool isLongPressedName(string name, string typed) {
        int j = 0;
        if(name.empty() || typed.empty()) return false;
        if(typed.size() < name.size()) return false;
        for(int i = 0; i < typed.size();++i){
            if(j == name.size()) return true;
            if(typed[i] == name[j]) {
                ++j;
                continue;
            }
            if( i >= 1 && typed[i] != name[j] && typed[i] == typed[i-1]) continue;
            else {
                j = 0;
                continue;
            }
        }
        if(j == name.size()) return true;
        else return false;
    }
};
总结：
周赛107，第三次打，AC了一道easy题，easy题只要认真想，想清楚corner cases就没问题。
第二道题思路不正确，没有想清楚。讨论区两次循环的方法比较巧妙，需要学习。DP没有思路，需大量练习。
太嫩了，继续修炼吧。