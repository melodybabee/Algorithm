题意：
最少删除几个字符才能使两个字符串相等。
方法一：dp,类似072题
思路：
1.设置dp[i][j]表示word1中的前i位和word2中的前j位组成的两个单词，能使其变成相同的最小步数。
2.dp的有效值从dp[1][1]开始，那么把第一行第一列赋值，因为第一行和第一列对应的总有一个字符串是空串，于是转换步骤完全是另一个字符串的长度。
3.那么如果i-1位和j-1位相等，那么dp[i][j] = dp[i-1][j-1];不需要添加额外的步骤就可以匹配
否则在dp[i][j-1]或者dp[i-1][j]的基础之上删除一位，在两者之间取小
4.dp数组的尾部就是返回的最小步数。
class Solution {
public:
    int minDistance(string word1, string word2) {
        int m = word1.size();
        int n = word2.size();
        vector<vector<int>>dp(m+1,vector<int>(n+1,0));
        for(int i = 0; i <= m;++i){
            dp[i][0] = i;
        }
        for(int j = 0; j <= n;++j){
            dp[0][j] = j;
        }
        for(int i = 1; i <= word1.size();++i){
            for (int j = 1; j <= word2.size(); ++j){
                if(word1[i-1]==word2[j-1]) dp[i][j] = dp[i-1][j-1];
                else{
                     dp[i][j] = min(dp[i][j-1],dp[i-1][j])+1;
                }
            }
        }
        return dp[m][n];
        
    }
};
方法二：dp找最长公共子串的长度
思路：
1.本题中的dp[i][j]表示word1和word2中前i位和前j位的相同字符串长度
2.如果本位相等，那么dp[i][j]等于 dp[i-1][j-1]+1,为了把前面相等的长度也计算上
3.如果不等，那么看错位是否相等，取错位dp[i-1][j],dp[i][j-1]中的最大值。
4.最后返回两个字符串的长度减去2倍的公共长度。
class Solution {
public:
    int minDistance(string word1, string word2) {
        int m = word1.size();
        int n = word2.size();
        vector<vector<int>> dp(m+1,vector<int> (n+1, 0));
        for(int i = 1; i <= m;++i){
            for (int j = 1; j <= n; ++j){
                if(word1[i-1]==word2[j-1]) dp[i][j] = dp[i-1][j-1]+1;
                else{
                    dp[i][j] = max(dp[i-1][j],dp[i][j-1]);
                }
            }
        }
        return m+n - 2*dp[m][n];
    }
};