题意：
在一个数组中判断有无目标单词。
思路：
1.题目中过的含义是在数组中找到连续能够匹配单词的位置，因为匹配需要连续
2.首先声明一个与原定数组相同大小的新数组，用来记录数组中的某位置是否已经遍历过
3.从数组的头部开始进入递归，用一个index记录单词的位置,如果当单词的位置已经等于单词的长度，说明已经匹配上，返回true
4.如果i,j已经超过数组的范围，或者已经遍历过这个位置，或者不匹配，返回false
5.在把一个位置标记为true之后，从它的上下左右四个位置来递归查找，只有一个位置满足即可。
6.如果不满足，DFS回溯，重新进入递归。
注意：
1.if(i < 0 || j < 0 || i >= m || j >= n || visited[i][j])是对的
if(visited[i][j] || i < 0 || j < 0 || i >= m || j >= n)是错的
边界要在遍历之前判断。
class Solution {
public:
    bool exist(vector<vector<char>>& board, string word) {
        if (board.empty() || board[0].empty()) return false;
        int m = board.size();
        int n = board[0].size();
        vector<vector<bool>> visited(m,vector<bool>(n,false));
        for(int i = 0; i < m; ++i){
            for (int j = 0; j < n; ++j){
                if(findWord(word,0,board,i,j,visited)){
                    return true;
                }
            }
        }
        return false; 
    }
    
    bool findWord(string word,int index,vector<vector<char>> &board,int i,int j,vector<vector<bool>> &visited){
        if(index == word.size()) return true;
        int m = board.size();
        int n = board[0].size();
        if(i < 0 || j < 0 || i >= m || j >= n || visited[i][j] || board[i][j] != word[index]) return false;
        visited[i][j] = true;
        bool flag = findWord(word,index+1,board,i-1,j,visited) 
                    ||findWord(word,index+1,board,i+1,j,visited) 
                    || findWord(word,index+1,board,i,j-1,visited) 
                    ||findWord(word,index+1,board,i,j+1,visited);
        visited[i][j] = false;
        return flag;
    }
};
优化：
也可以不用声明一个新数组来进行标记，在原数组中把已经遍历到的位置标记为'#'即可，回溯后返回原字符。
class Solution {
public:
    bool exist(vector<vector<char>>& board, string word) {
        int m = board.size();
        int n = board[0].size();
        for(int i = 0; i< m; ++i){
            for (int j = 0; j<n; ++j){
                if(dfs(board,i,j,word,0)) return true;
            }
        }
        return false;
    }
    
    bool dfs(vector<vector<char>>& board,int i, int j,string word,int index){
        int m = board.size();
        int n = board[0].size();
        if(index == word.size()) return true;
        if(i < 0 || j < 0 || i >= m || j >= n || board[i][j] != word[index]) return false;
        char c = board[i][j];
        board[i][j] = '#';
        bool flag = dfs(board,i+1,j,word,index+1) || dfs(board,i-1,j,word,index+1) || dfs(board,i,j+1,word,index+1) ||dfs(board,i,j-1,word,index+1);
        board[i][j] = c;
        return flag;
    }
};
