题意：
在字符串中找到包含目标子串的字符的最短字符串。
方法1:DP
思路：
1.建立一个二维的DP数组，dp[i][j]表示T中的第j位与S中的字符匹配的第一个位置。
2.二维数组默认为-1，因为二维数组需要有初始化的过程，那么首先在每一行的第一个位置改变对应数值，更换为相应的行数，表示T中第一位与S对应的位置（根据后面的动态转移方程原则）。
3.动态转移方程是如果T的当前位置等于S的当前位置，那么更新此时的dp为其左上角的元素，表示此位的起始位置和它之前元素的起始位置相同。因为需要找连续的T的匹配。
如果位置不同，dp更新为其前一行同一列的位置，表示匹配位置的头部位置，如果后面仍有更新，那么更新为再靠后的位置，更加接近题目中想要找的最短长度。
开始依次遍历两个字符串，更新二维数组。
每当更新完一行，判断最后一位是否为-1，如果是-1，说明没有完全匹配上，那么进入下一行循环。
如果最后一个数字不为-1，说明已经完全匹配上，那么判断长度是否比当前小，如果小，更新长度。更新起始位置／
4.起始位置就是每行最后一个位置记录的坐标，长度就是当前的行数减去起始位置。
5.最后判断长度是否为默认值，如果为默认值，说明没有找到，那么返回空。如果找到了，返回子串。
注意：
1.在DP的题目中，首先确认dp数组分别表示什么含义，其次确认动态转移方程，最后确认如何设置初始值。
确认状态转移方程的难度较大，可以先自定义一个小数组模拟情况从而找到动态转移方程和初始状态。
2.注意坐标！！
class Solution {
public:
    string minWindow(string S, string T) {
        int m = S.size();
        int n = T.size();
        int len = INT_MAX;
        int start = -1;
        vector<vector<int>> dp(m+1,vector<int>(n+1,-1));
        for(int i = 0; i <= m; ++i){
            dp[i][0] = i;
        }
        for(int i = 1 ; i <= m ;++i){
            for(int j = 1; j <= min(i,n); ++j){
                if(T[j-1] == S[i-1]) dp[i][j] = dp[i-1][j-1];
                else dp[i][j] = dp[i-1][j];
            }
            if(dp[i][n] != -1){
                int length = i - dp[i][n];
                if(length < len){
                    len = length;
                    start = dp[i][n];
                }
            }
        }
        return len == INT_MAX ? "" :S.substr(start,len);
        
    }
};
方法二：遍历优化
思路：
1.是讨论区看到的优化思路。参考一下，个人认为不如DP的方法更有系统性。
2.设置两个指针分别循环两个字符串，当目标字符串到末尾的时候，记录下当前位置便于求这次匹配的长度。
倒退j到起点位置，只要当i与j不匹配的时候就同时倒退i。
这样会保证i会跳过重复的第一个元素，到达最近的一个，从而找到最短的长度。
注意：
1.这种方法需要区分--i和i--，引起注意。
class Solution {
public:
    string minWindow(string S, string T) {
        int m = S.size();
        int n = T.size();
        int i = 0;
        int j = 0;
        int start = -1;
        int len = INT_MAX;
        while(i < m){
            if(S[i] == T[j]){
                if(++j == n){
                    int end = i+1;
                    while(--j >= 0){
                        while(S[i--] != T[j]){
                        }
                    }
                    ++i;
                    ++j;
                    if(end - i < len){
                        len = end -i;
                        start = i;
                    }
                }
            }
            ++i;
        }
        return (start != -1) ? S.substr(start,len) : "";
    }
};
