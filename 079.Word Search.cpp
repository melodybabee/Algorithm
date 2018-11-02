题意：
在一个数组中判断有无目标单词。
思路：
注意：
1.if(i < 0 || j < 0 || i >= m || j >= n || visited[i][j])是对的
if(visited[i][j] || i < 0 || j < 0 || i >= m || j >= n)是错的
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