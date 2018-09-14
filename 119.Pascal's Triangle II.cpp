class Solution {
public:
    vector<int> getRow(int rowIndex) {
        vector<int> res(rowIndex+1,1);
        if(rowIndex <= 1) return res;
        
        for(int i = 2; i <= rowIndex; ++i){
            for(int j = i-1; j>0; j--){
                res[j] = res[j-1] + res[j];
            }
        }
        return res;
    }
};
/*
思路：
1.单独输出指定行，可以新建一个vector,都输入1
2.用i来进行行数循环，用j执行每一位的循环
e.g rowIndex = 3;1,1,1 -> 1,2,1
rowIndex = 4;1,1,1,1 -> 1,2,1,1 -> 1,3,3,1
rowIndec = 5;1,1,1,1,1 -> 1,2,1,1,1 -> 1,3,3,1,1 -> 1,4,6,4,1
模拟每一位相加的过程【需要复习】

优化：
1.杨辉三角的性质包括:
*第n行的数字和为pow(2,n-1);
*第n行的第m个数和第n-m+1个数相等，即C(n-1,m-1)=C(n-1,n-m)
2.应用组合数公式：C[n,k]=C[n,k-1]*(n+1-k)/k;【需要学习】
result[i]=result[i-1]*(rowIndex-i+1)/i

*/