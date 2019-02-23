题意：243 follow up，设计一个程序实现243
class WordDistance {
private:
    vector<string> result;
public:
    WordDistance(vector<string> words) {
        result = words;
    }
    
    int shortest(string word1, string word2) {
        int ret = INT_MAX;
        int p = -1;
        int q = -1;
        for(int i = 0; i < result.size(); ++i){
            if(result[i] == word1){
                p = i;
                if(q != -1){
                    ret = min(ret,i-q);
                }
            }else if(result[i] == word2){
                q = i;
                if(p != -1){
                    ret = min(ret,i-p);
                }
            }
        }
        return ret;
    }
};

/**
 * Your WordDistance object will be instantiated and called as such:
 * WordDistance obj = new WordDistance(words);
 * int param_1 = obj.shortest(word1,word2);
 */

优化：利用hashtable
思路：
1.建立一个map首先把所有单词存储进去，value放入单词的位置，是vector<int>形式
2.判断的时候从vector的头部开始判断，不断取距离差，哪边小哪边向右移动，这样会使两个数字的值越来越接近
class WordDistance {
private:
    unordered_map<string,vector<int>>map;
public:
    WordDistance(vector<string> words) {
        for(int i = 0; i < words.size(); ++i){
            map[words[i]].push_back(i);
        }
    }
    
    int shortest(string word1, string word2) {
        int ret = INT_MAX;
        int i = 0;
        int j = 0;
        while(i < map[word1].size() && j < map[word2].size()){
            ret = min(ret,abs(map[word1][i] - map[word2][j]));
            map[word1][i] < map[word2][j] ? ++i : ++j;
        }
        return ret;
    }
};

/**
 * Your WordDistance object will be instantiated and called as such:
 * WordDistance obj = new WordDistance(words);
 * int param_1 = obj.shortest(word1,word2);
 */