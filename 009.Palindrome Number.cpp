设计思路：（满足不对原数字进行string转换的follow up）
1.如果原数等于0，return true;
2.如果原数是负数，return false;
3.先用一个数保存下x的值，对x进行取余、除10的操作，只要不为0就一直循环，再设置一个变量乘10与新变量相加
4.比较新的数值与原x是否相等。

注意：
1.区分while循环和if循环
2.也可以新建一个vector，每次计算后进行push_back操作，再用for循环依次读出
3.还有的方法是转换为string, 用到reverse方法对string进行反转

T(O) = O(log10(n)), S(O) = 1;
class Solution {
public:
    bool isPalindrome(int x) {
        int newx = x;
        if(newx < 0) return false;
        int ret = 0;
        while(newx!= 0){
            ret = 10*ret + newx%10;
            newx /= 10;
        }
        if(ret == x) 
            return true;
        return false;
    }
};


