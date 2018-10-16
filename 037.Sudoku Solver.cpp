题意：
求数独是否有解
思路：
1.从每行开始，循环每一列，对于每一个需要填入数字的位置从1-9进行填入，判断是否有效。如果合法就进入下一次递归，不合法就标记为'.'
2.当找到不合法的数字之后，会把它的位置重新置为'.'
注意：
1.在递归函数中，每个return表示当前递归函数终止，如果直接调用方法表示调用的方法运行之后还要回到当前函数。
2.深入理解递归和回溯思想
class Solution {
public:
    void solveSudoku(vector<vector<char>> &board) {
        if(board.size() != 9 && board[0].size() != 9) return;
        dfs(board,0,0);
    }
    
    bool dfs(vector<vector<char>>&board,int i,int j){
        if(i == 9) return true;//超过行数范围
        if(j == 9) return dfs(board,i+1,0);//超过列数范围，转到下一行
        if(board[i][j] == '.'){
            for(int p = 1; p <= 9; ++p){
                board[i][j] = p+'0';
                if(isValid(board,i,j)){
                    if(dfs(board, i, j+1)) return true;
                }
                board[i][j] = '.';
            }
        }else{
            return dfs(board,i,j+1);//填充下一个格子
        }
        return false;
    }
    
    bool isValid(vector<vector<char>>&board,int i, int j){
        for(int col = 0; col < 9;++col){
            if(col != j && board[i][j] == board[i][col]) return false;
        }
        for(int row = 0; row < 9;++row){
            if(row != i && board[i][j] == board[row][j]) return false;
        }
        for (int row = i / 3 * 3; row < i / 3 * 3 + 3; ++row) {//判断小格子起始位置的公式
            for (int col = j / 3 * 3; col < j / 3 * 3 + 3; ++col) {
                if ((row != i || col != j) && board[i][j] == board[row][col]) return false;
            }
        }
        return true;
    }
};