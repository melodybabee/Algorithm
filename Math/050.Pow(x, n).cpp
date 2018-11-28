题意：
求出一个数的幂值。
思路一：for循环，会TLE
class Solution {
public:
    double myPow(double x, int n) {
        double ret = 1.0;
        if(n == 0) return ret;
        bool flag = false;
        if(n < 0) {
            flag = true;
            n = -n;
        }
        while(n >= 1){
            ret *= x;
            --n;
        }
        if(flag == true) return 1/ret;
        else return ret;
            
    }
};
改进：运用位运算,快速幂,基本思想是二分法
T(n) = logn/log2 = O(logn);
1.思路和下面两种相同，但是写法上更简单
2.p & 1表示p和1取位与，都是1才为1，表示如果是奇数的话；p >>= 1;p向右移动一位，再次判断奇偶。
注意：
题目中给出的范围是n is a 32-bit signed integer, within the range [−2^31, 2^31 − 1],所以可能最小值int不超范围，但是反转之后会超。
所以在开始声明一个long long类型的p来替代n,便于反转。
class Solution {
public:
    double myPow(double x, int n) {
        double ret = 1.0;
        if(n == 0) return ret;
        long long p = n;
        bool flag = false;
        if(p < 0) {
            flag = true;
            p = -p;
        }
        while (p) {
            if (p & 1) ret *= x;
            p >>= 1;
            x = x * x;
        }
        if (flag) ret = 1 / ret;
        return ret;
    }
};
方法一：折半递归
思路：
1.首先判断正负，如果是负数需要输出倒数
2.进入递归，边界条件是n为0的时候返回1
3.每次取一半进行相乘，如果n是奇数，还需要结果子相乘还需要乘上本身，如果n是偶数，那么在原结果的基础上自相乘即可
class Solution {
public:
    double myPow(double x, int n) {
        if(n < 0) return 1/Pow(x,-n);
        return Pow(x,n);
    }
    double Pow(double x, int n){
        if(n == 0) return 1;
        double half = Pow(x,n/2);
        if(n%2 == 0) return half *half;
        return x*half*half;
    }
};
方法二：迭代
思路：
1.和递归类似，i从n开始折半，如果为奇数，还要再乘上一个自身，如果是偶数，子相乘即可。
2.最后判断如果n小于0,那么返回结果的倒数。
class Solution {
public:
    double myPow(double x, int n) {
        double res = 1.0;
        for (int i = n; i != 0; i /= 2) {
            if (i % 2 != 0) res *= x;
            x *= x;
        }
        return n < 0 ? 1 / res : res;
    }
};

二刷：
快速幂求解不熟，仍然想到暴力拆解的方法：
注意：
1.快速幂的核心就是奇数次乘上原数字一次，偶数次使两个原数字相乘，
如果是奇数先赋给结果1次的值，不断两两相乘。如果是偶数，直接两两相乘，最后到1的时候赋给结果值。
用p&1来判断是奇数还是偶数。
2.每进入一次循环，对次数减半，使原数字翻为2倍。
用p>>1来除以2.向右移动一位表示除以2,向右移动两位表示除以2的平方。
3.注意n的范围是[−231, 231 − 1]，因此有可能负数在范围内而取反之后超出int范围，所以需要更改为long long 
class Solution {
public:
    double myPow(double x, int n) {
        if(n == 0) return 1;
        double ret = 1;
        long long p = n;
        bool flag = false;
        if(p < 0){
            p = -p;
            flag = true;
        }
        
        while(p){
            if(p&1) ret *= x;
            p >>= 1;
            x = x*x;
        }
        
       if(flag) ret = 1/ret;
           return ret;
    }
};