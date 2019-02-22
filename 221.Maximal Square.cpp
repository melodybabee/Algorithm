题意：找数组中最大的正方形面积
方法一：暴力循环
思路：
1.如果要得到正方形，需要获得长==宽，那么需要一个i来记录宽的起始位置，j到i表示正方形的宽，k用来表示长度
2.建立一个数组来统计规定范围内1的数量，表示当前位置上有多少个1
3.每遍历过一次之后开始统计，宽度是j到i的距离+1,如果小于这个距离或者没有找到满意的条件，返回0.
否则遍历这个数组，找到连续的等于这个距离的值，只要不等就是0，如果最后计数器等于这个距离了，那么返回它的面积。
class Solution {
public:
    int maximalSquare(vector<vector<char>>& matrix) {
        int ret = 0;
        for(int i = 0; i < matrix.size(); ++i){
            vector<int>vec(matrix[i].size(),0);
            for(int j = i ; j < matrix.size(); ++j){
                for(int k = 0; k < matrix[j].size(); ++k){
                    if(matrix[j][k] == '1') ++vec[k];
                }
                ret = max(ret,getsum(vec,j-i+1));
            }
        }
        return ret;
    }
    
    int getsum(vector<int>&vec, int k){
        if(vec.size() < k) return 0;
        int count =0;
        for(int i = 0; i < vec.size();++i){
            if(vec[i] != k) count = 0;
            else ++count;
            if(count == k) return k*k;
        }
        return 0;
    }
};
方法2:DP
思路：
1.可以想到用dp[i][j]来记录正方形的状态，但是因为是正方形，长和宽都是相等的，所以dp数组中表示正方形的边长即可
2.那么初始状态就是如果j,i其中有一个为0，那么就直接更新为其本身
3.动态转移方程是取其左，左上，上三个方向上的较小值+1就是新的位置的值。
4.每结束一个判断之后更新一次较大值。
5.最后返回边长的平方。
class Solution {
public:
    int maximalSquare(vector<vector<char>>& matrix) {
        if(matrix.size() == 0 )return 0;
        int res = 0;
        vector<vector<int>>dp(matrix.size(),vector<int>(matrix[0].size(),0));
        for(int i= 0; i < matrix.size(); ++i){
            for(int j = 0; j < matrix[0].size(); ++j){
                if(i == 0 || j == 0) dp[i][j] = matrix[i][j]-'0';
                else if(matrix[i][j] == '1'){
                    dp[i][j] = min(min(dp[i-1][j],dp[i][j-1]), dp[i-1][j-1]) +1;
                }
                res = max(res,dp[i][j]);
            }
        }
        return res*res;
    }
};