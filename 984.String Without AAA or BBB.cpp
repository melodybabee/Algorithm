题意：避免出现AAA或者BBB的排列数字
思路：
1.本题题意如果在两个数组数量相等的时候交叉输入即可得到结果，所以目的就是让两个数字的差距尽可能的小，这样每次输出一个即可。
2.那么当两个数字大于0的时候，如果A大于0,那么即可输出一位，如果比B大，那么继续输出一位
B同理，A，B交叉进行输出操作
因为A，B最多两个相连就必须插入下一位数字，保证了局部最优。
3.而A，B的顺序也需要保证A大于B，不然还要重新判断B大于A的情况，那么提前判断一下A，B的大小，进行交换即可。
需要同时交换A，B与a,b
class Solution {
public:
    string strWithout3a3b(int A, int B) {
        string ret;
        char a = 'a';
        char b = 'b';
        if(A < B) swap(A,B),swap(a,b);
        while(A > 0 || B > 0){
            if(A > 0) ret += a,--A;
            if(A > B) ret += a,--A;
            if(B > 0) ret += b,--B;
            if(B > A) ret += b,--B;
        }
        return ret;
    }
};
补充：
什么时候是用贪心算法？
贪心算法保证了局部最优，但并不能保证得到最优解。
weekly Contest 121总结：
1.找到有关贪心思想和位计算相关的题是弱点，多练习几道类似的题目