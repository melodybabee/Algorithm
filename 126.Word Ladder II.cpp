题意：
127 follow up,输出所有单词可能变换的路径。
思路：
1.因为寻找的是最短路径，所以还是基于BFS的思想，在BFS核心部分和127相似，但是注意本题queue中输入的是每条路径，不单单是单词。
2.首先在queue中放入第一个单词，当栈不为空的时候弹出第一个路径。取路径中最后一个单词。
开始对随后一个单词进行深度搜索，从第一位开始，依次改变每一位上的字母。
更改后的单词如果在字典中不存在，那么continue；
如果存在，因为后面还有其他更改成功过的情况，因此复制当前路径，在当前路径的后面加入新的单词。如果新的单词等于尾部单词，在输出数组中push进入该路径；如果不等，那么在queue中输入新的路径。
3.注意为了提高搜索的效率，需要一个值来记录满足条件的路径长度，如果后面的长度再大于该长度，说明不是最短路径，需要舍弃。
4.同时如果在路径中存在重复的单词，那么肯定不是最短路径，因此如果已经更新为新的长度，那么对于所有已经存在的单词，都要从字典中删除。
清空记录存在的单词的set,后面如果再找到满足条件的单词，insert到set中。更新新的长度为当前路径长度。
5.注意BFS的核心在于一层一层更新路径，在上一层没有完全更新完成之前，不会重新进入while循环。
6.如果是同等长度的路径，每次从queue中取出的时候不会重新判断长度。
class Solution {
public:
    vector<vector<string>> findLadders(string beginWord, string endWord, vector<string>& wordList) {
        unordered_set<string>word(wordList.begin(),wordList.end());
        vector<vector<string>> ret;
        queue<vector<string>> q;
        vector<string>ans{beginWord};
        unordered_set<string>existword;
        q.push(ans);
        int level = 1;
        int minlength = INT_MAX;
        while(!q.empty()){
            vector<string> temp = q.front();
            q.pop();
            if(temp.size() > level){
                for(string w : existword) word.erase(w);
                existword.clear();
                level = temp.size();
                if(level > minlength) break;
            }
            string last = temp.back();
            for(int i = 0; i < last.size(); ++i){
                string newlast = last;
                for(char c = 'a' ; c <= 'z' ;++c){
                    newlast[i] = c;
                    if(!word.count(newlast)) continue;
                    existword.insert(newlast);
                    vector<string>newtemp = temp;
                    newtemp.push_back(newlast);
                    if(newlast == endWord){
                        ret.push_back(newtemp);
                        minlength = level;
                    }else{
                        q.push(newtemp);
                    }
                }
            }
        }
        return ret;
    }
};