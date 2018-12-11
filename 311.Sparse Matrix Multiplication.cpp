题意：计算稀疏矩阵乘积
方法一：两指针遍历
思路：
1.计算稀疏矩阵的原则是因为它有很多0，如果每一个0都计算那么会很耗时
2.因此先判断是否为0，不为0再进行相乘操作，如果为0直接跳过，在初始状态默认为0.
注意：
1.矩阵乘积中结果vec[i][i] = A[i][k] * B[k][j];结果是左矩阵的行数和右矩阵的列数
class Solution {
public:
    vector<vector<int>> multiply(vector<vector<int>>& A, vector<vector<int>>& B) {
        vector<vector<int>>vec(A.size(),vector<int>(B[0].size()));
        for(int i = 0; i < A.size();++i){
            for(int k = 0 ; k < A[0].size(); ++k){
                if(A[i][k] != 0){
                    for(int j = 0 ; j < B[0].size(); ++j){
                        if(B[k][j]!=0){
                            vec[i][j] += A[i][k] * B[k][j];
                        }
                    }
                }
            }
        }
        return vec;
    }
};
【其他方法待学习】