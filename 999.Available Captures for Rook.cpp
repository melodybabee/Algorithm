题意：判断国际象棋能吃掉一个卒
思路：
1.首先找到车的位置，在分别四个方向遍历，遇到.继续，遇到象break，遇到卒吃了break
2.在吃卒的过程中进行计数，最后返回计数器的值
class Solution {
public:
    int numRookCaptures(vector<vector<char>>& board) {
        int count = 0;
        int h = board.size();
        int w = board.size();
        for(int i = 0; i < h; ++i){
            for(int j = 0; j < w; ++j){
                if(board[i][j] == 'R'){
                    int p = i;
                    int q = j;
                    for(q = j-1; q >= 0; --q){
                        if(board[p][q] == '.') continue;
                        else if(board[p][q] == 'B') break;
                        else if(board[p][q] == 'p'){
                            ++count;
                            break;
                        }
                    }
                    for(q = j+1; q < w; ++q){
                        if(board[p][q] == '.') continue;
                        else if(board[p][q] == 'B') break;
                        else if(board[p][q] == 'p'){
                            ++count;
                            break;
                        }
                    }
                    q = j;
                    for(p = i-1; p >= 0; --p){
                        if(board[p][q] == '.') continue;
                        else if(board[p][q] == 'B') break;
                        else if(board[p][q] == 'p'){
                            ++count;
                            break;
                        }
                    }
                    for(p = i+1; p < h; ++p){
                        if(board[p][q] == '.') continue;
                        else if(board[p][q] == 'B') break;
                        else if(board[p][q] == 'p'){
                            ++count;
                            break;
                        }
                    }
                }
            }
        }
        return count;
    }
};