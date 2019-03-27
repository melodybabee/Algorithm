题意：判断一个数字是否是完全平方数
方法一：暴力拆解
思路：
1.从0开始循环，因为不能用sqrt,所以循环到它本身，如果乘积相等，表示是平方数，否则不是
2.注意因为有可能数字非常大，所以乘积会超过int的范围，那么需要更改为long long
3.注意因为1也是完全平方数，所以需要循环的时候等于其本身
class Solution {
public:
    bool isPerfectSquare(int num) {
        for(long long i = 0 ;i <= num; ++i){
            if(i * i < num) continue;
            else if (i * i == num) return true;
            else return false;
        }
        return false;
    }
};
优化：
思路：
1.不让使用sqrt()可以直接相除，实现sqrt()的功能
2.注意因为涉及相除所以遍历要从1开始，题目中说了是正数所以也不用考虑0
class Solution {
public:
    bool isPerfectSquare(int num) {
        for(int i = 1 ;i <= num/i; ++i){
            if (i * i == num) return true;
        }
        return false;
    }
};

方法2:二分法
思路：
1.通过不断的找中点来判断是否是完全平方数
2.注意因为是完全平方数，所以while循环要判断相等，那么左右边界移动的时候就需要+1和-1
class Solution {
public:
    bool isPerfectSquare(int num) {
        int left = 0;
        int right = num;
        while(left <= right){
            long long mid = left + (right-left)/2;
            long long ret = mid * mid;
            if(ret == num) return true;
            else if(ret > num) right = mid-1;
            else left = mid + 1;
        }
        return false;
    }
};

方法3:所有的完全平方数可以由等差数列构成，因此判断是否是等差数列即可
class Solution {
public:
    bool isPerfectSquare(int num) {
        int i = 1;
        while(num > 0){
            num -= i;
            i += 2;
        }
        return num == 0;
    }
};