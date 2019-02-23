题意：找一个数组中两个字符串之间的最短距离
思路：是两个for循环暴力拆解的优化，O（n）
1.首先想到的是用hashtable,但是数组中有重复的元素，如果把hashtable中的value设置为set，后面的比较会更加繁琐
2.好的方法就是遇到第一个单词记录下来，如果也遇到了第二个单词，那么立刻比较
同理如果遇到了第二个单词也记录下来，如果第一个单词出现过那么立刻比较，随时取过程中的较小值
class Solution {
public:
    int shortestDistance(vector<string>& words, string word1, string word2) {
        int p = -1;
        int q = -1;
        int ret = INT_MAX;
        for(int i= 0; i < words.size(); ++i){
            if(words[i] == word1){
                p = i;
                if(q != -1){
                    ret = min(ret,i-q);
                }
            }else if(words[i] == word2){
                q = i;
                if(p != -1){
                    ret = min(ret,i-p);
                }
            }
        }
        return ret;
    }
};