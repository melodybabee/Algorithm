题意：找出旋转的数组*其坐标位置所有情况中最大的结果
思路：
1.找规律的题目，对于有明确规律化的问题如果没有很好的办法解决，可以考虑列举找规律
2.设置a,b,c,d四个数字作为举例
F(0) = 0a + 1b + 2c + 3d;
F(1) = 0d + 1a + 2b + 3c;
F(2) = 0c + 1d + 2a + 3b;
F(3) = 0d + 1c + 2d + 3a;
所有数字的和等于a+b+c+d
那么F(1) = F(0)+b +c +a -3d = F(0) + sum -4d
F(1) = F(0) + sum - 4d
F(2) = F(1) + sum - 4c
F(3) = F(2) + sum - 4b
以此类推， F(i) = F(i-1) + sum - n*A[n-i]
3.首先计算出总和以及F(1)的值，不断遍历数字进行更新，取其中较大的一个，注意因为F(0)已经求过了，所以要从1开始循环
class Solution {
public:
    int maxRotateFunction(vector<int>& A) {
        int sum = accumulate(A.begin(),A.end(),0);
        int res = 0;
        for(int i = 0 ; i < A.size(); ++i){
            res += i * A[i];
        }
        int temp = res;
        for(int i = 1 ; i < A.size(); ++i){
            temp = temp + sum-A.size()*A[A.size()-i];
            res = max(temp,res);
        }
        return res;
    }
};