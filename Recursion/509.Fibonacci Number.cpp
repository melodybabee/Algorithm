题意：斐波那契递归
方法一：递归
T(n) = O(2^n);
思路：
1.判断递归的临界条件，等于0和1的时候return
2.再进行递归调用
class Solution {
public:
    int fib(int N) {
        if(N == 1) return 1;
        if(N == 0) return 0;
        return fib(N-1) + fib(N-2);
    }
};

方法2:DP+记忆数组
注意：C++中也可以用[]来声明数组，用int memo[N+1]表示。
class Solution {
public:
    int fib(int N) {
        if(N < 2) return N;
        vector<int>vec(N+1);
        vec[0] = 0;
        vec[1] = 1;
        for(int i = 2; i <= N; ++i){
            vec[i] = vec[i-1] + vec[i-2];
        }
        return vec.back();
    }
};

3.17复习
注意：递归方法注意边界条件，一般就是动态转移方程中的corner cases
class Solution {
    public int fib(int N) {
        if(N == 0) return 0;
        if(N == 1) return 1;
        return fib(N-1) + fib(N-2);
    }
}
递归方法的弊端在于每次进入递归之后都需要重复计算当前值到0的所有值，因此会有大量重复计算的过程，记忆数组记录已经计算出来的结果避免重复计算
注意：
1.如果N为0的时候不存在vec[1] = 1;因此还需要特别判断
class Solution {
public:
    int fib(int N) {
        if(N < 2) return N;
        vector<int>vec(N+1,0);
        vec[0] = 0;
        vec[1] = 1;
        for(int i = 2; i <= N; ++i){
            vec[i] = vec[i-1] + vec[i-2];
        }
        return vec.back();
    }
};