题意：相邻不超过2个颜色相同的篱笆，问涂篱笆的方法有多少种。
思路：
1.题目中的含义是不能超过有2个相同颜色的篱笆，那么可以分成两种情况：
一个是后一位与前一位颜色不同，那么涂色方式有之前所有的涂色方法*(k-1)种
一个是后一位与前一位的颜色相同，那么一共有之前涂色方法个
2.最后总的涂色方法是颜色不同的个数+颜色相同的个数的总和
注意：
其中上一轮中颜色不同的个数可以在下一轮中重新涂上相同的颜色，因此same是等于上一轮中的diff
而不同的颜色可以自由涂色，只要与当前的一种颜色不同即可。
class Solution {
public:
    int numWays(int n, int k) {
        if(n == 0) return 0;
        int diff = k;
        int same = 0;
        for(int i = 2;i <= n ;++i){
            int temp = diff;
            diff = (same + diff) * (k-1);
            same = temp;
        }
        return diff + same;
    }
};