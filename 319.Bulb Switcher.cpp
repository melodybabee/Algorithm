 bulbs 灯泡
 toggle 开关触发器
 题意：一共n个灯泡，对灯泡进行n次操作，判断最后有几盏灯是亮着的
 思路：
 1.因为最后灯的状态是经过n次更新后得到的，因此如果数字不是完全平方数，比如12，它的因数有(1,12), (2,6), (3,4)那么它最后的状态一定是关闭的，因为一对数字前面打开后面就会关闭
 而如果数字是完全平方数，当n为36时，它的因数有(1,36), (2,18), (3,12), (4,9), (6,6)。那么它最后的状态就是亮的
 2.那么这道题求的就是在目标值范围内找到有几个完全平方数
class Solution {
public:
    int bulbSwitch(int n) {
        int ret = 1;
        while(ret * ret <= n) ++ret;
        return ret -1;
    }
};
简易写法：
class Solution {
public:
    int bulbSwitch(int n) {
        return sqrt(n);
    }
};