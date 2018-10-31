题意：
最少删除几个字符才能使两个字符串相等，输出字符的ASCII码。583 follow up.
思路：DP找最少删除的位数
1.用DP找到最少删除元素个数，和583思路完全一样。但是本题需要加上删除元素的ASCII码，因此dp中放的是所有该位置删除最少元素的ASCII码和。
2.每删除一个就把所删除的元素的ASCII码加入到dp中，由于字符就是用ASCII表示的，所以我们不用转int，直接累加就可以。
注意：
1.dp从0开始，因此循环包括初始化都需要从1开始，而且循环的边界是<=
2.注意此类问题首先要有一个初始化的值，DP首先是初始化，其次是动态转移方程
补充：
ASCII码
在计算机中，所有的数据在存储和运算时都要使用二进制数表示（因为计算机用高电平和低电平分别表示1和0）。
例如，像a、b、c、d这样的52个字母（包括大写）以及0、1等数字还有一些常用的符号（例如*、#、@等）在计算机中存储时也要使用二进制数来表示。
具体用哪些二进制数字表示哪个符号，当然每个人都可以约定自己的一套（这就叫编码），而大家如果要想互相通信而不造成混乱，那么大家就必须使用相同的编码规则，于是美国有关的标准化组织就出台了ASCII编码，统一规定了上述常用符号用哪些二进制数来表示。
Bin(二进制) Oct(八进制)	Dec(十进制) Hex(十六进制)  缩写/字符      解释
0000 0000  0            0          00            NUT(null)     空字符
......符号们......
0011 0000  60           48         30            0             数字0
......数字们......
......符号们......
0100 0001  101          65         41            A             字母A
......字母们......
如果想把字符转为ASCII码的形式，那么直接读取即可，不用转换为int.
class Solution {
public:
    int minimumDeleteSum(string s1, string s2) {
        int m = s1.size();
        int n = s2.size();
        vector<vector<int>> dp(m+1,vector<int>(n+1,0));
        for(int i = 1; i<= m;++i){
            dp[i][0] = dp[i-1][0]+s1[i-1];
        }
        for(int j = 1; j<= n;++j){
            dp[0][j] = dp[0][j-1] + s2[j-1];
        }
        for(int i = 1; i <= m; ++i){
            for (int j = 1; j <= n; ++j){
                if(s1[i-1] == s2[j-1]) dp[i][j] = dp[i-1][j-1];
                else{
                    dp[i][j] = min(dp[i-1][j]+s1[i-1],dp[i][j-1]+s2[j-1]);
                }
            }
        }
        return dp[m][n];
    }
};
思路：DP找最长的公共子串
1.首先用DP找到最长的公共子串，注意如果相同需要加上相同位置的ASCII码
2.计算s1和s2所有字符的ASCII码和，可以用accumulate()方法
3.用所有的ASCII码和减去2倍的公共长度ASCII码即为所求。
class Solution {
public:
    int minimumDeleteSum(string s1, string s2) {
        int m = s1.size();
        int n = s2.size();
        vector<vector<int>> dp(m+1,vector<int>(n+1,0));
        for(int i = 1; i <= m; ++i){
            for (int j = 1; j <= n; ++j){
                if(s1[i-1] == s2[j-1]) dp[i][j] = dp[i-1][j-1] + s1[i-1];
                else{
                    dp[i][j] = max(dp[i-1][j],dp[i][j-1]);
                }
            }
        }
        int sum1 = accumulate(s1.begin(), s1.end(), 0);
        int sum2 = accumulate(s2.begin(), s2.end(), 0);
        return sum1 + sum2 - 2*dp[m][n];
    }
};