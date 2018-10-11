truncate 截短
quotient 商
题意：
不能用乘除或者取余操作，来求出一个数的商
思路：
1.不能用乘除的话可以换作加减，但是加减的效率比较低，因此可以用位操作
一个数字向左移动一位，扩大两倍，移动2位，扩大2^2=4倍
一个数字向右移动1位，缩小2倍，移动2位，缩小4倍
举例：
	int i = 2;
	cout << (i<<4) << endl; // 二进制左移4位，扩大2^4倍，即2*2^4
	int i = 32;             
	cout << (i>>4) << endl; // 二进制右移4位，缩小了2^4倍，即32/(2^4)
2.应用二分法，如果被除数大于除数的2倍，除数扩大为原来的2倍，商扩大为初始值（1）的2倍，被除数减去扩大以后的除数
直到不能大于两倍，仍然比除数大，那么为一倍，再相减
3.注意边界条件，因为被除数是-2147483648，在int范围内，当除数是-1时，结果就超出了int范围，需要返回INT_MAX
4.其他所有变量需要声明为long long,因为在二分过程中有可能会超出int范围
5.正负判断：
需要首先把被除数和除数都取绝对值进行判断，^操作同号为0，异号为1，真为1假为0
sign = ((dividend < 0) ^ (divisor < 0 )) ? -1 : 1;
（1）如果dividend正，divisor负，dividend < 0 == 0，divisor < 0 ==1，((dividend < 0) ^ (divisor < 0 )) == 1， 是真因此结果为-1
（2）如果dividend正，divisor正，dividend < 0 == 0，divisor < 0 ==0，((dividend < 0) ^ (divisor < 0 )) == 0， 是假因此结果为1
（3）如果dividend负，divisor负，dividend < 0 == 1，divisor < 0 ==1，((dividend < 0) ^ (divisor < 0 )) == 0， 是假因此结果为1
（4）如果dividend负，divisor正，dividend < 0 == 1，divisor < 0 ==0，((dividend < 0) ^ (divisor < 0 )) == 1， 是真因此结果为-1
class Solution {
public:
    int divide(int dividend, int divisor) {
        if(divisor == 0 || (dividend == INT_MIN && divisor == -1)) return INT_MAX;
        long long m = abs((long long)dividend);
        long long n = abs((long long)divisor);
        long long res = 0;
        int sign = ((dividend < 0) ^ (divisor < 0 )) ? -1 : 1;
        if(n == 1) return sign == 1 ? m : -m;
        while(m >= n){
            long long temp = n, p = 1;
            while(m >= (temp << 1)){
                temp <<= 1;
                p <<= 1;
            }
            res += p;
            m -= temp;
        }
        return sign == 1? res: -res;
    }
};