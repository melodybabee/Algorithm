题意：
两个string匹配，如果pattern是？，可以匹配所有单字符，如果是*，可以匹配所有字符串，包括空字符串
类似第10题正则匹配
方法一：遍历，贪心算法
思路：
1.依次遍历s和p两个字符串，当p中含有*的时候，分别在两个字符串中记录下*的位置（即各自当时的i,j)，s回到前一位重新等待匹配
2.当p中的字符与s匹配上或者为?的时候，重新进入循环
3.如果不满足匹配上的条件，此时的p也不等于*，那么看sstar的位置是否存在，如果存在，i回溯到sstar被标记的这一位，sstar相加，j回到pstar位置等待进入下一轮匹配
如果不存在已经被标记的*位置，那么直接返回false
注意如果是aaaa,aa的情况，为了防止越界，如果j的位置已经大于plen,那么也要判断是否有*存在
4.当i循环到末尾之后，要判断p是否到末尾，如果尾巴还有*可以忽略，直到不为*的字符或者等于字符串长度
补充：
1.【需要理解】本题用到了贪心算法，贪心的思路是：只对最后一个‘*’号进行回溯。每当失配时，只回溯到最近的一个‘*’号，令该‘*’号多匹配一个字符，重新进行匹配。
class Solution {
public:
    bool isMatch(string s, string p) {
        int slen = s.size();
        int plen = p.size();
        int sstar = -1;
        int pstar = -1;
        int i = 0;
        int j = 0;
        for(i,j; i < slen; ++i,++j){
            if(p[j] == '*'){
                pstar = j;
                sstar = i;
                --i;
            }else if(j >= plen || (p[j] != s[i] && p[j] != '?')){
                if(sstar >= 0){
                    i = sstar;
                    ++sstar;
                    j = pstar;
                } 
                else return false;
            }
        }
        while(j< plen && p[j] == '*') ++j;
        return j == plen;
    }
};
方法2:DP
思路：
1.首先建立一个二维数组来存储true还是false的结果，注意二维数组是从0开始的，为了使string便于对应上，在初始化的时候要建立s.size()和p.size()大小的false
在循环的时候从1开始循环，但是判断的时候需要判断i-1，因此循环边界条件是字符串的大小；
这样在最后返回的时候dp[m][n]的结果就是字符串最后一位的结果。
dp[i][j]表示字符串s从0到i的的子字符串能否匹配p从0到j的子字符串
2.dp[i][]i为第几行表示对s的第i位是否匹配。
所以在初始阶段，先扫描一遍p的长度，为了处理p第一位为*的情况。
3.【重点复习】开始循环，如果遇到*位，p.charAt(j)=='*'，'*'可以选择匹配0个字符，此时dp[i][j]=dp[i][j-1];可以选择匹配1个字符，此时dp[i][j]=dp[i-1][j-1];
以此类推，还可以是2,3,4,...n个，dp[i][j]=dp[i][j-1]||dp[i-1][j-1]||……||dp[0][j-1]。
但是上面的公式可以化简，当p.charAt(j)=='*'时,有
dp[i-1][j]=dp[i-1][j-1]||dp[i-2][j-1]||……||dp[0][j-1]
所以dp[i][j]==dp[i-1][j]||dp[i][j-1]
4.如果不是*，判断当前位置s，p是否相等或者p等于？，以及他们的前一位是否匹配
5.最后返回第m,n位的真值
class Solution {
public:
    bool isMatch(string s, string p) {
        int m = s.size();
        int n = p.size();
        vector<vector<bool>> dp (m+1,vector<bool>(n+1,false));
        dp[0][0] = true;
        for(int i = 1; i <= n;++i){//处理第一位是*的情况
            if(p[i-1] == '*') dp[0][i] = dp[0][i-1];
        }
        for(int i = 1; i <= m; ++i){
            for(int j = 1; j <= n; ++j){
                if(p[j-1] == '*') dp[i][j] = dp[i-1][j] || dp[i][j-1];
                else dp[i][j] = (p[j-1] == s[i-1] || p[j-1] == '?') && dp[i-1][j-1];
            }
        }
        return dp[m][n];
    }
};