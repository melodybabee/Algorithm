题意：
给出两个字符串，可以增，删，替换，问最少多少步可以实现从第一个字符串转换为第二个字符串
思路：
1.状态dp[i+1][j+1]表示word1[0:i]到word2[0:j]需要的步数
2.状态转移方程：
考虑最后一次操作word1[0:i] -> word2[0:j]，会有三种情况：
(1）插入一个字符：word1[0:i] -> word2[0:j-1],然后在word1[0:i]后插入word2[j].
dp[i+1][j+1] = dp[i+1][j]+1
(2) 删除一个字符：word1[0:i-1] -> word2[0:j]，然后删除word1[i]
DP[i+1][j+1] = DP[i][j+1]+1
(3) 替换一个字符：word1[0:i-1] -> word2[0:j-1]
word1[i] != word2[j]时，word1[i] -> word2[j]：DP[i+1][j+1] = DP[i][j] + 1
word1[i] == word2[j]时：DP[i+1][j+1] = DP[i][j] 
计算方向：
replace (i, j)     delete (i, j+1)
insert (i+1, j)    (i+1, j+1)
3.初始状态：
DP[0][i] = i： word1为空，要转化到word2[0:i-1]，需要添加i个字符。
DP[i][0] = i： word2为空，要从word1转化到空字符串，需要删除i个字符。
class Solution {
public:
    int minDistance(string word1, string word2) {
        int m = word1.size();
        int n = word2.size();
        vector<vector<int>> vec(m+1,vector<int>(n+1,0));
        for(int i = 0; i<= m; ++i){
            vec[i][0] = i;
        }
        for(int j = 0; j <= n; ++j){
            vec[0][j] = j;
        }
        for(int i = 1; i <= m; ++i){
            for(int j = 1; j <= n;++j){
               if(word1[i-1] == word2[j-1]){
                   vec[i][j] = vec[i-1][j-1];
               }else{
                   vec[i][j]= min(min(vec[i-1][j],vec[i][j-1]),vec[i-1][j-1])+1;
               }
            }
        }
        return vec[m][n];
    }
};

2.4复习
注意：
1.首先DP需要先声明dp[i][j]的含义，本题的意义是表示word1(0,i)与word2(0,j)之间最少有几步才能匹配上
2.因为坐标从0开始，所以在过程中要注意坐标的变化
（1）初始化的时候从0开始
（2）但是双层遍历的时候从1开始遍历，但是比较要从字符串的第一位开始，因此是word1[i-1] == word2[j-1]
（3）因为从1开始，因此判断条件需要等于单词的长度
（4）最后返回的时候要返回单词的长度，才是DP数组的最后一位，或者直接返回back().back()
class Solution {
public:
    int minDistance(string word1, string word2) {
        vector<vector<int>>dp(word1.size()+1,vector<int>(word2.size()+1));
        for(int i = 0; i <= word1.size();++i){
            dp[i][0] = i;
        }
        for(int i = 0; i <= word2.size(); ++i){
            dp[0][i] = i;
        }
        for(int i = 1; i <= word1.size(); ++i){
            for(int j = 1; j <= word2.size(); ++j){
                if(word1[i-1] == word2[j-1]){
                    dp[i][j] = dp[i-1][j-1];
                }else{
                    dp[i][j] = min(min(dp[i-1][j-1],dp[i-1][j]),dp[i][j-1])+1;
                }
            }
        }
        return dp.back().back();
    }
};