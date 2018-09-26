思路：
1.取余不是0的返回false,不断用n = n/2,再取余
2.直到while循环结束之后仍然没有返回false,返回true
注意:
1.需要单独判断0
class Solution {
public:
    bool isPowerOfTwo(int n) {
        if(n == 0) return false;
        while(n!=1){
            if(n%2 != 0) return false;
            n = n/2;
        }
        return true;
    }
};

优化：
1.有关于数字的题目首先想到bit manipulation
2.通过观察发现
1 1
2 10
4 100
8 1000
因此可以每次判断最低位是不是1，再向右移动，最后统计1的个数即可。如果是2的平方数，只会有最后一个1.
class Solution{
public:
	bool isPowerOfTwo(int n){
		int count = 0;
		while(n >0){
			count += (n&1);//都是1才为1，否则为0
			n >>= 1;
		}
		return count == 1;
	}
}；
在上面的基础之上，可以进行改进，如果在原数上减1，会发现最高位降1位，其余为0的位都变成1，如果做&，就会为0
class Solution{
public:
	bool isPowerOfTwo(int n){
		return(n > 0) && (!(n &(n-1)));//0 is FALSE, 1 is TRUE.
	}
}；
