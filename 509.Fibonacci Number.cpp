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