题意：在单词数组中找到与匹配的字符串模式相同的单词。
思路：
1.循环数组中的单词，如果数组中的单词的长度与相匹配的长度不同，那么直接跳过
2.每循环到一个单词，对这个单词和目标单词之间建立双向映射
建立双向映射的原因是因为需要完全匹配，即比如abb形式的单词要去匹配abb形式的单词，但是如果是单向映射的话，那么def也可以去匹配abb,对abb也需要建立一个反向映射
建立两张表是因为哈希表如果遇到相同的元素会覆盖掉之前的匹配，因此需要两张表来记录进行分别查找
3.开始遍历循环到的单词，如果在两张表中都没有记录，那么插入
如果都有记录且匹配，跳过
其他情况标记位更改为false
4.某一个单词循环结束之后判断是否为false,如果是false那么跳过表示不能匹配，如果是ture输入到结果数组中
class Solution {
public:
    vector<string> findAndReplacePattern(vector<string>& words, string pattern) {
        vector<string>ans;
        for(auto word : words){
            if(word.size() != pattern.size()) continue;
            unordered_map<char,char>map1;
            unordered_map<char,char>map2;
            bool flag = true;
            for(int i = 0; i < word.size(); ++i){
                if(!map1.count(word[i]) && !map2.count(pattern[i])){
                    map1[word[i]] = pattern[i];
                    map2[pattern[i]] = word[i];
                }else if(map1[word[i]] == pattern[i] && map2[pattern[i]] == word[i]){
                    continue;
                }else{
                    flag = false;
                    break;
                }
            }
            if(flag) ans.push_back(word);
        }
        return ans;
    }
};