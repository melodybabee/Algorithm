思路：
1.本题想找出大于10的各位数字之和，如果仍大于0，则继续相加，直到为个位数为止
2.首先内层循环，对原数取余相加，再除以10，即将现有的数字的各个个位数相加。因为最后小于10的数字仍需要相加，此while循环的条件时>0
3.外层循环需要判断这个数字是不是大于等于10（或除以10大于0），需要重新进入内循环，把内循环的结果再赋值给num
4.最后输出num
class Solution {
public:
    int addDigits(int num) {
        while(num >= 10){
            int temp = 0;
            while(num > 0){
                temp += num%10;
                num /= 10;
            }
            num = temp;
        }
        return num;
    }
};

本题巧解：
1.通过观察发现
1    1
2    2
3    3
4    4
5    5
6    6
7    7
8    8    
9    9    
10    1
11    2
12    3    
13    4
14    5
15    6
16    7
17    8
18    9
19    1
20    2
所有大于9的数字都是对9取余，如果是9的倍数则为9，可以得到规律表达式为(n-1)%9+1
class Solution {
public:
    int addDigits(int num) {
        return (num - 1) % 9 + 1;
    }
};