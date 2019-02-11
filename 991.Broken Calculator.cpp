题意：一个数字可以进行翻倍或者+1的操作，求出最少的变换次数。
思路：
1.因为尽可能使这个步骤减小，所以如果y小于x，那么结果只有对X一位一位相减才能得到
2.因此当Y大于X的时候，如果Y是偶数，将Y减半；如果Y是奇数，那么把Y把Y加上1再进行除以2操作。每次的操作都进行一次计数
3.当Y大于X的时候停止while循环，输出两者的差加上计数器的数量即可。
class Solution {
public:
    int brokenCalc(int X, int Y) {
        int ret = 0;
        while(Y > X){
            if(Y % 2 == 0){
                Y /= 2;
            }else{
                Y += 1;
            }
            ++ret;
        }
        return X- Y +ret;
    }
};