题意：
从给定的数组中不破坏原来的子串，找到指定个数的0和1，返回找到的子串个数。
思路：
1.设置一个dp数组表示dp[i][j]中有i个0，j个1的时候能组成的最多的字符串个数。
2.开始遍历字符串，遍历每个字符串上的字符，计算每个字符串上0和1的个数出现的次数，从规定位置向出现的次数循环，在dp数组中更新该位置和减去0，1个数的位置+1中的较大值。
注意：
1.因为每个单词中的0，1是不可拆的，因此状态转移方程每次减的都是当前循环到的单词的0和1的个数。
2.本题不能用greedy的思路，比如先给字符串数组排个序，让长度小的字符串在前面，然后遍历每个字符串，遇到0或者1就将对应的m和n的值减小，这种方法在有的时候是不对的。
比如对于{"11", "01", "10"}，m=2，n=2这个例子，遍历完“11”的时候，把1用完了，那么对于后面两个字符串就没法处理了，而其实正确的答案是应该组成后面两个字符串才对。
class Solution {
public:
    int findMaxForm(vector<string>& strs, int m, int n) {
        vector<vector<int>> dp(m+1, vector<int>(n+1, 0));
        for(auto & s : strs){
            int zero = 0;
            int one = 0;
            for(auto & c : s){
                if(c == '0') ++ zero;
                else ++one;
            }
            for(int i = m; i >= zero; --i){
                for(int j = n; j >= one; --j){
                    dp[i][j] = max(dp[i][j],dp[i-zero][j-one]+1);
                }
            }
        }
        return dp[m][n];
    }
};