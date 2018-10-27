题意：
螺旋输出一个矩阵
思路：
1.给这个矩阵设立上下左右四个边界，从左至右，从上到下依次遍历，每次遍历后对应的层或者列相加／相减
2.注意有时会出现上下已经不满足对应关系但是左右还处在循环中的情况，因此需要在进入左右的时候再单独判断一下
比如：
[1, 2, 3, 4]
[5, 6, 7, 8]
[9,10,11,12]
如果不加以判断会输出1,2,3,4,8,12,11,10,9,5,6,7,6
多输出一个6，就是因为在进入循环到7之后top已经大于down,而left仍然小于right还可以继续循环
class Solution {
public:
    vector<int> spiralOrder(vector<vector<int>>& matrix) {
        vector<int> vec;
        if(matrix.empty()) return vec;
        int m = matrix.size();
        int n = matrix[0].size();
        int left = 0;
        int right = n-1;
        int top = 0; 
        int down = m-1;
        while(left <= right && top <= down){
            for(int i = left; i <= right; ++i){
                vec.push_back(matrix[top][i]);
            }
            ++top;
            for (int i = top; i <= down;++i){
                vec.push_back(matrix[i][right]);
            }
            --right;
            if(top <= down){
                for(int i = right; i>= left;--i){
                vec.push_back(matrix[down][i]);
                }
                --down;
            }
            if(left <= right){
                for(int i = down; i >= top; --i){
                vec.push_back(matrix[i][left]);
                }
                ++left;
            }
        }
        return vec;
    }
};