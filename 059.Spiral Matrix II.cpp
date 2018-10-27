题意：
创建给一个空数组，螺旋输入数字，054逆过程
思路：
1.和054一样，设立上下左右四个边，只不过需要一个初始值每次循环后都相加
2.因为输出肯定是正方形，因此不需要在循环内做判断
class Solution {
public:
    vector<vector<int>> generateMatrix(int n) {
        vector<vector<int>> ret(n,vector<int>(n));
        int input = 1;
        int left = 0;
        int right = n-1;
        int top = 0;
        int down = n-1;
        while(top <= down && left <= right){
            for(int i = left; i <= right;++i){
                ret[top][i] = input;
                ++input;
            }
            ++top;
            for(int i = top; i <= down;++i){
                ret[i][right] = input;
                ++input;
            }
            --right;
            for(int i = right; i >= left; --i){
                ret[down][i] = input;
                ++input;
                }
                --down;
            for(int i = down; i >= top;--i){
                ret[i][left] = input;
                ++input;
                }
            ++left;
        }
        return ret;
    }
};