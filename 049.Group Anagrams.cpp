Anagram 回文构词法
题意：
给了一组单词，其中有的是错位词，把所有的错位词分成一组，输出到一个新的数组中。
思路：
1.因为错位词可以通过排序进行归位，因此对于每个单词进行排序，排序的结果作为map的key,map的value就是原单词。
2.map的key是string类型，value是一个vector类型，因此在遍历过所有的单词之后，直接将value中的vector去push到输出数组中即可。
class Solution {
public:
    vector<vector<string>> groupAnagrams(vector<string>& strs) {
        vector<vector<string>>ret;
        unordered_map<string,vector<string>>map;
        for(auto &str : strs){
            string s = str;
            sort(s.begin(),s.end());
            map[s].push_back(str);
        }
        for(auto &m : map){
            ret.push_back(m.second);
        }
        return ret;
    }
};