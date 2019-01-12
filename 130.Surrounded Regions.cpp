题意：把所有非边界的包围区域都统一成边界上的值
思路：DFS
1.通过分析题目可以知道，所有非边界或者不连着边界的被包围的值都应该改成其边界值，类似围棋中的做法
所有连着边界的值都不会被更改。
那么就应该从四个边入手，进行遍历边，对边上等于目标值的值进行DFS遍历，把这些所有连着边界的值暂时更改为一个临时值。
2.对所有连着边界的值进行DFS遍历之后，那么就会把这些连着边界的都更改为临时值，那么没有被更改的就可以变成边界值
3.最后再把这些更改为临时值的值改回边界值即可
注意：
1.在DFS的过程中一定要注意边界问题，判断其上下左右是否存在之后，在进行DFS递归。
但是因为需要左右或者上下移动+1或者-1，需要提前判断是否超出边界。
class Solution {
public:
    void solve(vector<vector<char>>& board) {
        for(int i = 0; i < board.size(); ++i){
            for(int j = 0; j < board[0].size(); ++j){
                if((i == 0 || j == 0 || i == board.size()-1 || j == board[0].size()-1) && board[i][j] == 'O'){
                    dfs(board,i,j);
                }
            }
        }
        
        for(int i = 0; i < board.size(); ++i){
            for(int j = 0; j < board[0].size(); ++j){
                if(board[i][j] == 'O') board[i][j] = 'X';
                if(board[i][j] == 'S') board[i][j] = 'O';
            }
        }
    }
    
    void dfs(vector<vector<char>>& board, int i, int j){
        if(board[i][j] = 'O'){
            board[i][j] = 'S';
            if(i > 0 && board[i-1][j] == 'O')dfs(board,i-1,j);
            if(j > 0 && board[i][j-1] == 'O')dfs(board,i,j-1);
            if(i < board.size()-1 && board[i+1][j] == 'O')dfs(board,i+1,j);
            if(j < board[0].size()-1 && board[i][j+1] == 'O')dfs(board,i,j+1);
        }
    }
};