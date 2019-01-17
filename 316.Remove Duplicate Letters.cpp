题意：删除字符串中重复的字母，同时对所有可能输出的结果按照字典序排列
思路：
1.因为要统计在字符串中每个字符出现的频次，那么首先建立一个哈希表来记录所有字符出现的次数
2.再次循环字符串，设置一个ASCII256位的数组，来记录当前循环的字符是否已经判断过。如果已经循环过，表示它已经在目标位置，不需要再次改变了。直接跳过。
3.如果遍历到的字符与结果值中的最后一位相比更小，同时最后一位在map中的个数不为0，表示后面还会出现这个字符，那么就把这个字符删除，同时visited数组更新为0
4.最后遍历到的字符更新visited字符为1，在结果中加上这个字符
注意：
1.字符串删除最后一个字符的方法是pop.back()
2.在结果字符串中先加入一个0，因为数字0的ASCII码要比所有的字母小，最后的时候删除掉这个0.
3.int visited[256]的建立是一个int类型的数组，大小为256，每一个输入进去的字符会存在对应的ASCII码位置。
class Solution {
public:
    string removeDuplicateLetters(string s) {
        unordered_map<char,int>map;
        int visited[256] = {0};
        string ret = "0";
        for(auto c : s){
            ++map[c];
        }
        for(auto c : s){
            --map[c];
            if(visited[c]) continue;
            while(c < ret.back() && map[ret.back()] != 0){
                visited[ret.back()] = 0;
                ret.pop_back();
            }
            visited[c] = 1;
            ret += c;
        }
        return ret.substr(1);
    }
};