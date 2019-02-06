题意：每次知道猜中的字符个数，最多10次机会判断是否猜中了单词。
方法：贪心策略，逐步筛选
思路：
1.因为需要从单词库中随机选一个单词，因此首先确认这个单词，用random()方法来取单词。
2.因为系统默认最多10次机会，因此设定一个10的机会的值，用while循环来进行倒数，每次的次数-1.
3.题目中给出了猜有几个匹配字符的API，那么确认一个值表示每次猜中了几个，用master.guess来进行匹配调用
4.对字符库中的每个单词进行遍历，把所有与现有的单词匹配的字符个数相等的单词输入到一个新的单词库中，再把单词库进行更新。因为如果目标单词一定在相匹配的所有单词的范围内。
5.一次while循环结束之后，随机更新另一个单词再次进入循环遍历。
/**
 * // This is the Master's API interface.
 * // You should not implement it, or speculate about its implementation
 * class Master {
 *   public:
 *     int guess(string word);
 * };
 */
class Solution {
public:
    void findSecretWord(vector<string>& wordlist, Master& master) {
        string word = wordlist[random() % wordlist.size()];
        int count = 10;
        while(count--){
            int match = master.guess(word);
            findother(wordlist, word,match);
            word = wordlist[random() % wordlist.size()];
        }
    }
    
    void findother(vector<string>& wordlist, string word, int num){
        vector<string>temp;
        for(auto w : wordlist){
            int mat = match(w, word);
            if(mat == num) temp.push_back(w);
        }
        wordlist = temp;
    }
    
    int match(string w, string word){
        int ret = 0;
        for(int i = 0; i < w.size(); ++i){
            if(w[i] == word[i]){
                ++ret;
            }
        }
        return ret;
    }
};