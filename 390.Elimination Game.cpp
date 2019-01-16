Elimination 淘汰
题意：
从左到右从右至左分别轮流删除数字，求出最后一个剩下的数字是多少。
方法一：找数字的镜像
思路：
1.每次删除之后，剩下的数字的个数都是之前的二分之一，那么返回的结果应该是对n/2进行递归后值的2倍
2.通过观察发现，以9为例
123456789
第一个删除后是2468，折半反向后是8642，按照正序的去除规则，去除了8，4，得到62
第二次删除后是62，按照上一步反向26，去除第一位2，得到最终结果6
那么每次进入递归之后得到的结果是对n/2进行递归的值再进行镜像处理即可
将其镜像对折为一个子问题，当前状态可以推出的下一个状态的结果，但是相反
3.镜像处理规则，1+数列最后一个数字-当前数字 = 当前数字的镜像，即以中轴对称的数字
class Solution {
public:
    int lastRemaining(int n) {
        return n == 1 ? 1 : 2*(1+n/2 -lastRemaining(n/2));
    }
};