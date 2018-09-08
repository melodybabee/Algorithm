//递归实现
class Solution {
public:
    int climbStairs(int n) {
        int ans = 0;
        if(n == 1) return 1;
        if(n == 2) return 2;
        ans = climbStairs(n-1) + climbStairs(n-2);
        
        return ans;
        
    }
};
//DP
class Solution {
public:
    int climbStairs(int n) {
        vector<int> ret(n,0);
        ret[0] = 1;
        ret[1] = 2;
        for(int i = 2; i < n ; ++i){
            ret[i] = ret[i-1] + ret[i-2];
        }
        
        return ret[n-1];
        
        
    }
};
/*
思路：
1.通过找规律(列举）可知，本题满足斐波那契数列，1，2，3，5...
细化的思路为第n个数的值 = 第n-1个数走一步 + 第n-2个数走两步得到
2.整体上是divide and conquer的思路，通过递归实现，但是递归的时间复杂度较高，斐波那契数列为2的n次幂，在n=40左右的时候时间将近为1秒，而动态规划时间复杂度为o(n) 
因此DP比递归往往更加适用

思考：
1.递归与DP的区别：
总的思想都是将大的问题分成小的问题进行解决后，再依次合并
递归：自上向下进行，常用于子问题相对对立的问题，不需要进行大量重复计算
DP：自上向下----递归的子集，递归求解的子问题会有交集，因此会有大量重复计算的部分，DP是将这些子问题存储起来，避免了重复运算
    自下向上----迭代

*/