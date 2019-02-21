题意：找到两个数字二进制下不同的位数
思路：
1.用^对两个数字进行异或操作，相同为0，不同为1
2，因为int最多有32位，所以分别对数字进行右移，判断新的数字中有几个1，有1的话计数器+1
class Solution {
public:
    int hammingDistance(int x, int y) {
        int count = 0;
        int cur = x^y;
        for(int i = 0; i < 32;++i){
            count += (cur >> i)&1;
        }
        return count;
    }
};

优化：cur &= (cur-1);用来快速移除最右边的1
class Solution {
public:
    int hammingDistance(int x, int y) {
        int count = 0;
        int cur = x^y;
        while(cur){
            ++count;
            cur &= (cur-1);
        }
        return count;
    }
};

补充：
(x ^ y) % 2相当于检查最低位是否相同
x/2相当于将x向右移动一位