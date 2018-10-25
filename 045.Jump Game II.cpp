题意：
找到最少几步可以从数组的头部跳到尾部。055follow up.
思路：
1.利用贪心算法，记录下某点的最远距离。比较这个最远距离是否大于等于数组长度，如果大于等于，就跳出。
2.但是与055不同的是，g记录了最远长度，还需要设置一个数值记录下当前的g值，从当前位置开始循环g个长度，来判断此轮是否能到达尾部。
3.每次新进入一轮循环就把count+1，满足条件时直接输出。
注意：
因为题目中说明了肯定能到达尾部，因此不需要这一步进行判断。正常情况下还需要判断是否能到达尾部。
class Solution {
public:
    int jump(vector<int>& nums) {
        int n = nums.size();
        int g = 0;
        int count = 0;
        int i = 0;
        while(g < n-1){
            ++count;
            int pre = g;
            for(i; i <= pre;++i){
                g = max(g,nums[i]+i); 
            }
            if (pre == g) return -1; //判断是否能到达末尾，如果进入循环而g没有长度的增加，那么不能到达末尾。
        }
        return count;
    }
};