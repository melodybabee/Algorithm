题意：给出了匹配的pair，判断两个句子是否是相似的
思路：
1.如果两个句子长度不等，直接返回false.利用hashtable,把匹配的pair正反都插入到hashtable中
2.遍历目标句子，如果相等，跳过；如果没有，返回false;如果不匹配，返回false。最后返回true.
注意：
1.因为hashtable能覆盖，因此如果后面有相同的匹配对就会覆盖掉前面的，因此hashtable中的value需要时set,每次插入，再不断尽心查找
2.pair<>操作取first和second
3.set查找元素要用find()方法，判断是否到达了end()的位置
class Solution {
public:
    bool areSentencesSimilar(vector<string>& words1, vector<string>& words2, vector<pair<string, string>> pairs) {
        if(words1.size()!= words2.size()) return false;
        unordered_map<string,set<string>>map;
        for(auto p : pairs){
            map[p.first].insert(p.second);
            map[p.second].insert(p.first);
        }
        for(int i = 0; i < words1.size(); ++i){
            if(words1[i] == words2[i]) continue;
            if(!map.count(words1[i])) return false;
            if(map[words1[i]].find(words2[i]) == map[words1[i]].end()) return false;
        }
        return true;
    }
};