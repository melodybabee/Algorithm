题意：
将随机产生1-7数字的方法改为随机产生1-10数字的方法。
思路：
1.如果单独对rand7()扩大或者缩小，那么随机产生的新数字不是等概率的。因为不同数字可能会产生相同的组合，所以不行。
比如 (rand2() - 1) + rand2()取rand3()就不是等概率的。
那么需要把所有数字上升一个维度，乘上一个数字，那么就是等概率的了。
比如(rand2() - 1) * 2 + rand2() = rand4();
如果想用rand4()来产生rand2(),那么可以反过来，rand2() = rand4() % 2 + 1 ;
rand6() % 2 + 1也能生成rand2();
2.那么如果我们想求出rand10()，需要先找到一个rand10*N()的数字，将rand()转化也需要等概率
(rand7() -1)*7 + rand7();这样得到了rand49();
3.需要去除大于40的部分，因此如果得到的数字大于40，那么直接舍弃。此处用到的是拒绝采样Rejection Sampling，即随机到需要的数字就接受，不是需要的就拒绝，并重新采样。
// The rand7() API is already defined for you.
// int rand7();
// @return a random integer in the range 1 to 7

class Solution {
public:
    int rand10() {
        while(true){
            int num = (rand7()-1)*7+rand7();
            if(num <= 40) return num%10 +1;
        }
    }
};