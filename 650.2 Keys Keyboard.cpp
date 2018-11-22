题意：
只能全部复制或者全部粘贴，问至少多少次可以得到目标值。
方法1:DP
思路：
1.因为所有的字母只能够全部复制或者全部粘贴，所以所有字母最多的可能性是一个一个粘贴，即为它本身个数可以得到。
2.但是如果一个数字有除了1以外的其他因子，那么可以通过复制该因子得到数字，复制的次数是所得的商。
3.那么就可以用一个dp[i]记录i位置上的最少次数，进入新的结点后如果可以整除，开始循环他的因子，取较小值。
class Solution {
public:
    int minSteps(int n) {
        vector<int>dp(n+1,0);
        for(int i = 2 ; i <= n; ++i){
            dp[i] = i;
            for(int j = i-1; j > 0; --j){
                if(i % j == 0)
                dp[i] = min(dp[i],dp[j]+i/j);
            }
        }
        return dp[n];
    }
};
方法2:递归
思路和DP方法一样，用一个递归实现。
注意递归在自己调用自己的时候不能对创建的变量进行初始化，需要借助方法后面的变量进行引用。
每次循环从因子开始循环，如果可以整除，那么调用递归，返回原数值和递归的值加商的和中的较小值。
class Solution {
public:
    int minSteps(int n) {
        if(n == 1) return 0;
        int res = n;
        for(int i = n-1; i > 1; --i){
            if(n % i == 0){
                res = min(res,minSteps(n/i)+i);
            }
        }
        return res;
    }
};
方法3:greedy
思路：
1.DP的思路是:如果n%k == 0;需要拷贝n/k次同时粘贴k-1次，所以dp[n] = min(dp[n/k]+k)对所有合理的k成立
2.greedy的方法是如果k不是一个质数，它能够被分解成k = ab, 那么可以拷贝n/k次同时粘贴a-1次；再拷贝n/b次，粘贴b-1次。
the total is dp[n/k]+a+b次
3.本道题事实上是将N分解为M个数字的乘积，且M个数字的和最小。
寻找一个因子d使能够做d次拷贝（n/d）来得到n，做d次拷贝需要采取d步（第一步全部复制，d-1次粘贴）
4.因此可以直接求n的因子有哪些，再相加即可。
class Solution {
public:
    int minSteps(int n) {
        int res = 0;
        for(int i = 2; i <= n; ++i){
            while(n % i == 0){
                res += i;
                n /=i;
            }
        }
        return res;
    }
};
优化：
T(n) = O(sqrt(n));
class Solution {
public:
    int minSteps(int n) {
        int res = 0;
        for(int i = 2; i <= sqrt(n); ++i){
            while(n % i == 0){
                res += i;
                n /=i;
            }
        }
        if(n > 1) res += n;
        return res;
    }
};