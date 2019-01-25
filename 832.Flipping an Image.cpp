题意：反转，再0，1反转数组
思路：
1.首先循环到新的一列之后用reverse()进行反转
2.再循环每一行中的数字，把0和1对换
class Solution {
public:
    vector<vector<int>> flipAndInvertImage(vector<vector<int>>& A) {
        for(int i = 0;i < A.size();++i){
            reverse(A[i].begin(),A[i].end());
            for(int j = 0; j < A[0].size();++j){
                if(A[i][j] == 0) A[i][j] = 1;
                else A[i][j] = 0;
            }
        }
        return A;
    }
};
位运算写法，0，1对换取非^即可
class Solution {
public:
    vector<vector<int>> flipAndInvertImage(vector<vector<int>>& A) {
        for(int i = 0;i < A.size();++i){
            reverse(A[i].begin(),A[i].end());
            for(int j = 0; j < A[0].size();++j){
                A[i][j] ^= 1;
            }
        }
        return A;
    }
};