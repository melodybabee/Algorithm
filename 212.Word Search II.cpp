题意：
079的follow up，在数组中找到多个单词并输出。
方法一：如果使用079的方法加一层循环会TLE。因此要用到trie树。
class Solution {
public:
    vector<string> findWords(vector<vector<char>>& board, vector<string>& words) {
        int m = board.size();
        int n = board[0].size();
        int len = words.size();
        vector<string> ans;
        vector<string> ret;
        for(int i = 0; i < len; ++i){
            for(int p = 0; p < m; ++p){
                for (int q =0 ; q < n; ++q){
                    if(dfs(words[i],0,board,p,q)){ 
                        ans.push_back(words[i]);
                    }
                }
            }
        }
        for(int i = 0; i< ans.size();++i){
            if(i >= 1 && ans[i]==ans[i-1]) continue;
            ret.push_back(ans[i]);
        }
        return ret;
    }
    
    bool dfs(string word,int index,vector<vector<char>>& board,int i, int j){
        if(index == word.size()) return true;
        int m = board.size();
        int n = board[0].size();
        if(i < 0 || j < 0 || i >= m || j >= n || board[i][j] != word[index]) return false;
        char c = board[i][j];
        board[i][j] = '#';
        bool flag = dfs(word,index+1,board,i+1,j) || dfs(word,index+1,board,i-1,j) || dfs(word,index+1,board,i,j+1) || dfs(word,index+1,board,i,j-1);
        board[i][j] = c;
        return flag;
    }
};
方法二：Trie树
知识补充：
字典树：
又称单词查找树，Trie树，是一种树形结构，是一种哈希树的变种。典型应用是用于统计，排序和保存大量的字符串（但不仅限于字符串），所以经常被搜索引擎系统用于文本词频统计。
它的优点是：利用字符串的公共前缀来节约存储空间，最大限度地减少无谓的字符串比较，查询效率比哈希表高。
字典树的基本功能是用来查询某个单词（前缀）在所有单词中出现次数的一种数据结构，它的插入和查询复杂度都为O(len),Len为单词（前缀）长度，但是它的空间复杂度却非常高，如果字符集是26个字母，那每个节点的度就有26个，典型的以空间换时间结构。
思路：
1.首先把所有的单词存到一个trie树中，便于在多个前缀重复的情况下耗时过长。
2.进入数组循环后，先判断树中是否存在该字符，存在，调用dfs，不存在直接进入下一次循环。
3.在进入递归后，如果指针指向的位置的str不空，说明到了一个单词的尾部，直接push_back即可。避免重复计算，push_back之后要清空str标记。
4.分别判断指定位置的上下左右在树中是否存在，存在进入递归，不存在重新循环。DFS回溯递归。
注意：
在定义结构体的属性初始化的时候，一定要加括号。TrieNode() : 某属性(初始值)。为固定结构，记下来，【理论待学习】
class Solution {
public:
    struct TrieNode{
        TrieNode *child[26];
        string str;
        TrieNode() : str(""){
            for(auto &a : child) a = NULL;
        }
    };
    
    struct Trie{
        TrieNode *root;
        Trie(): root(new TrieNode()){};
        void insert(string s){
            TrieNode * p = root;
            for(auto &a : s){
                int i = a - 'a';
                if(!p -> child[i]) p -> child[i] = new TrieNode();
                p = p -> child[i];
            }
            p -> str = s;
        }
    };
    vector<string> findWords(vector<vector<char>>& board, vector<string>& words) {
        vector<string> ans;
        if (words.empty() || board.empty() || board[0].empty()) return ans;
        vector<vector<bool> > visit(board.size(), vector<bool>(board[0].size(), false));
        Trie t;
        for(auto & a : words) t.insert(a);
        for(int p = 0; p < board.size(); ++p){
            for (int q =0 ; q < board[p].size() ; ++q){
                if(t.root->child[board[p][q] - 'a']){ 
                   dfs(t.root -> child[board[p][q] - 'a'],board,p,q,ans,visit);
                }
            }
        }
        return ans;
    }
    void dfs(TrieNode *p,vector<vector<char>>& board,int i, int j,vector<string>&ans,vector<vector<bool> > &visit){
        if(!p->str.empty()){
            ans.push_back(p -> str);
            p -> str.clear();
        }
        int m = board.size();
        int n = board[0].size();
        visit[i][j] = true;
        int d[][2] = {{-1,0},{1,0},{0,-1},{0,1}};
        for(auto &a : d){
            int x = a[0] + i;
            int y = a[1] + j;
            if(x >= 0 && y >= 0 && x < m && y < n && !visit[x][y] && p -> child[board[x][y] - 'a'])
                dfs(p->child[board[x][y] - 'a'],board,x,y,ans,visit);
        }
        visit[i][j] = false;
    }
};
