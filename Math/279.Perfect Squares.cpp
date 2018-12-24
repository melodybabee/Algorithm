题意：
找到一个整数最少可以由几个完全平方数组成。类似322换币问题。
方法一：DP
思路：
1.首先设置一个数组记录下完全平方数，把它看作换币问题中的硬币。
2.建立DP数组，初始值位置为0的地方设置为0，从1开始循环到n结束，不断更新dp中的值。
3.内部循环完全平方数，新的值等于当前位置-循环到的完全平方数的位置的值+1，取较小。
4.最后返回dp的最后一个位置。
class Solution {
public:
    int numSquares(int n) {
        vector<int> square;
        for(int i = 1; i * i <= n; ++i){
            square.push_back(i*i);
        }
        vector<int>dp(n+1,INT_MAX);
        dp[0] = 0;
        for(int i = 1; i <= n ;++i){
            for(int j = 0; j < square.size(); ++j){
                if(i-square[j] >= 0)
                dp[i] = min(dp[i],dp[i-square[j]]+1);
                }
        }
        return dp[n];
    }
};
方法2:把完全平方数的构造放在DP更新循环的内部
1.内部的循环的判断条件是去j的平方，只要小于给定的目标值即可。
2.注意在DP中如果想返回DP的最后一个元素而准确的位置易错的话，可以直接返回dp.back()
class Solution {
public:
    int numSquares(int n) {
        vector<int>dp(n+1,INT_MAX);
        dp[0] = 0;
        for(int i = 0; i <= n ;++i){
            for(int j = 1; i+ j*j <= n; ++j){
                dp[i+j*j] = min(dp[i+j*j],dp[i]+1);
                }
        }
        return dp.back();
    }
};
方法3:不断增加DP的长度知道达到目标值
思路：
1.首先给DP进行初始化，设置一个值为0的值。
2.当DP的大小小于目标值的时候，内部循环完全平方数，取小于等于当前DP长度大小的的完全平方数中，较小的值，更新到DP尾部
3.最后返回dp的最后一个位置。
class Solution {
public:
    int numSquares(int n) {
        vector<int>dp(1,0);
        while(dp.size() <= n){
            int m = dp.size();
            int val = INT_MAX;
            for(int i = 1; i*i <= m; ++i){
                val = min(val,dp[m-i*i]+1);
            }
            dp.push_back(val);
        }
        return dp.back();
    }
};
方法4:递归写法
1.首先设置一个返回值res,从2开始循环完全平方数，因为当小于4的时候直接返回原数字即可。
2.得出的商a表示目前的个数，b等于不能被整除的部分，那么对这部分数字进行递归，重新查找最少的完全平方数构成
3.返回a与调用后的b的结果的和与原结果的较小值，完全平方数+1
4.最后返回结果
class Solution {
public:
    int numSquares(int n) {
        int res = n, num = 2;
        while (num * num <= n) {
            int a = n / (num * num), b = n % (num * num);
            res = min(res, a + numSquares(b));
            ++num;
        }
        return res;
    }
};
方法5：四平方和定理
Lagranges four-square theorem：任意一个正整数均可表示为4个整数的平方和，其实是可以表示为4个以内的平方数之和，那么就是说返回结果只有1,2,3或4其中的一个
思路：
1.根据定理，所有的数字都可以用最多4个平方数来表示，那么4个为一组，如果可以整除的话可以先把原来的数字缩小4倍
2.如果对8取余等于7的话，那么直接返回4。
3.从0开始判断，设置另一个整数值结算剩下的数的平方根，如果两者的平方和等于n的话那么返回a和b
感叹号!表示逻辑取反，那么一个正整数逻辑取反为0，再取反为1
所以用两个感叹号!!的作用就是看a和b是否为正整数，都为正整数的话返回2，只有一个是正整数的话返回1
4.如果都不满足的话返回3
class Solution {
public:
    int numSquares(int n) {
        while (n % 4 == 0) n /= 4;
        if (n % 8 == 7) return 4;
        for(int a = 0; a*a < n ;++a){
            int b = sqrt(n-a*a);
            if(a*a + b*b == n)
                return !!a + !!b;
        }
        return 3;
    }
};

12.24复习：
DP基本方法
注意：
1.一共需要解决两个问题，首先是如何表示完全平方数进行表示：
那么先建立一个数组，里面放所有小于目标值的完全平方数
2.第二个问题：如何更新成新的完全平方式：
建立DP数组，在外层循环目标数字，内层对完全平方数的数组进行循环，如果当前数字减去完全平方数大于0，那么说明可以进行更新，更新为之前DP数组上的位置+1
dp[i]表示为当前坐标位置表示的数字那一位最少可以由几个完全平方数表示
class Solution {
public:
    int numSquares(int n) {
        vector<int>square;
        vector<int>dp(n+1,INT_MAX);
        for(int i = 1 ; i * i <= n; ++i){
            square.push_back(i*i);
        }
        dp[0] = 0;
        for(int i = 1; i <= n; ++i){
            for(int j = 0 ; j < square.size(); ++j){
                if(i - square[j] >= 0){
                    dp[i] = min(dp[i],dp[i-square[j]]+1);
                }
            }
        }
        return dp.back();
    }
};
