题意：734follow up,可传递地判断是否是相似的单词
方法一：graph + BFS
思路：
1.与734相同，首先用一个map对匹配的pair进行正反插入，设置一个队列，开始从第一个单词进行插入
2.当队列不为空的时候，取栈顶元素，如果能直接与目标单词对应上，那么直接返回true
3.否则更新visited数组，对第一个单词在map中对应的单词进行遍历，如果visited数组中没有，就把它重新放入队列中
当栈为空的时候如果标记为仍然是false,那么返回false
注意：
1.map中的value类型使用unordered_set的效率更高，而set是红黑树的平衡二叉检索树的数据结构,map是红黑树
class Solution {
public:
    bool areSentencesSimilarTwo(vector<string>& words1, vector<string>& words2, vector<pair<string, string>> pairs) {
        if(words1.size() != words2.size()) return false;
        unordered_map<string,unordered_set<string>>map;
        for(auto p : pairs){
            map[p.first].insert(p.second);
            map[p.second].insert(p.first);
        }
        for(int i = 0; i < words1.size(); ++i){
            if(words1[i] == words2[i]) continue;
            queue<string>q{{words1[i]}};
            set<string>visited;
            bool flag = false;
            while(!q.empty()){
                string temp = q.front();
                q.pop();
                if(map[temp].count(words2[i])){
                    flag = true;
                    break;
                }
                visited.insert(temp);
                for(auto m : map[temp]){
                    if(!visited.count(m))q.push(m);
                }
            }
            if(!flag) return false;
        }
        return true;
    }
};
方法2: graph + DFS
思路：
1.首先两次把单词放到map中，从第一个单词开始进行循环，DFS和BFS遍历都需要建立一个set来表示是否被循环过。
2.开始从第一个单词开始循环，进行DFS遍历，同样是不满足条件的时候，即返回false的时候，直接返回false,循环结束没有返回false的话返回true
3.在DFS递归中，如果两个单词相等，那么直接返回true
在visited数组汇总插入循环到的单词，开始遍历这个单词在map中对应的单词，如果没有遍历过，同时继续调用递归返回true,那么返回true,否则返回false
因为一定只要找到一组满足条件的DFS即可，因此不需要在visited数组中再撤回当前单词
class Solution {
public:
    bool areSentencesSimilarTwo(vector<string>& words1, vector<string>& words2, vector<pair<string, string>> pairs) {
        if(words1.size() != words2.size()) return false;
        unordered_map<string,unordered_set<string>>map;
        for(auto p : pairs){
            map[p.first].insert(p.second);
            map[p.second].insert(p.first);
        }
        for(int i = 0; i < words1.size(); ++i){
            unordered_set<string>visited;
            if(!dfs(map,words1[i],words2[i],visited)) return false;
        }
        return true;
    }
        
    bool dfs(unordered_map<string,unordered_set<string>>&map,string word1,string word2,unordered_set<string> &visited){
        if(word1 == word2) return true;
        visited.insert(word1);
        for(auto m : map[word1]){
            if(!visited.count(m) && dfs(map,m,word2,visited)) return true;
        }
        return false;
    }
};
方法3:union find
思路：
1.首先处理pair对，对每一对数找到根的值，如果不同，那么在map中形成一个匹配对
这时候所有的单词都会连接着它的根结点
2.开始循环第一个单词集数组，如果第一个数组和第二个数组中的根结点不同的话，直接返回false
3.连接根结点，如果在map中没有，那么直接插入。
根结点的特征是key与value相等，返回的值如果相等，那么直接返回，如果不等，调用递归进行返回，直到找到key和value相等的时候的值
class Solution {
public:
    bool areSentencesSimilarTwo(vector<string>& words1, vector<string>& words2, vector<pair<string, string>> pairs) {
        if(words1.size() != words2.size()) return false;
        unordered_map<string,string>map;
        for(auto p : pairs){
            string x = getroot(p.first,map);
            string y = getroot(p.second,map);
            if(x != y) map[x] = y;
        }
        for(int i = 0; i < words1.size(); ++i){
            if(getroot(words1[i],map) != getroot(words2[i],map)) return false;
        }
        return true;
    }
    
    string getroot(string s,unordered_map<string,string>&map){
        if(!map.count(s)) map[s] = s;
        return s == map[s] ? s : getroot(map[s],map);
    }
};