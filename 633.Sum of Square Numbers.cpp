题意：判断两个数字是否可以由两个完全平方数组成
方法一： 二分查找
1.设置两个指针，如果等于返回true,如果大了向右移动小的，如果小了向左移动大的
2.注意两个指针相等的时候也需要判断
3.因为对原数字取平方根，再加上另外一个平方根，所以乘积需要用long long
class Solution {
public:
    bool judgeSquareSum(int c) {
        long long left = 0;
        long long right = sqrt(c);
        while(left <= right){
            if(left * left + right *right == c) return true;
            else if(left * left + right *right < c) ++left;
            else --right;
        }
        return false;
    }
};

方法2:不断相减判断
思路
1.先取平方根，再乘积判断是否得到原值，如果是返回true
2.如果不等，取差值，取平方根，判断差值是否是完全平方数，如果是，那么返回true
3.直到减到0，如果没有返回true,那么返回false
class Solution {
public:
    bool judgeSquareSum(int c) {
        for(int i = sqrt(c); i >= 0; --i){
            if(i * i == c) return true;
            int diff = c - i*i;
            int cur = sqrt(diff);
            if(cur * cur == diff) return true;
        }
        return false;
    }
};