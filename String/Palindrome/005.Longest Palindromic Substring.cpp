题意：找到string中最大的回文子串
----------------------------
方法1:纯暴力计算
两次for循环找到string中所有的子串，再依次循环子串看它是否是回文的。
T（N） = n^3;
----------------------------
方法2:普通算法，找到每个结点的偶数长度的最大回文字符串和奇数长度的最大回文字符串
T（N） = n^2; S（N） = 1；
思路：
1.循环到每个结点，分别求出以该结点为中心的奇偶回文子串，如果是偶数为左中心。设置左右边界，左不小于0，右不大于size（），且左右相等的时候即为回文
2.如果回文的长度大于初始值，则记录下来。同时记录下这个回文串的起点start
3.循环结束后输出从start起点的长度为maxlen的子串
注意：
1.因为left和right是满足while循环后进行++，--的，因此不满足while条件的时候已经被加1，或者-1
因此计算start的时候求left的位置需要+1；求长度的时候需要尾部-头部+1-2；
2.string操作：string.substr(子串起点，子串长度)；
class Solution {
public:
    string longestPalindrome(string s) {
        int maxlen = 0;
        int start = 0;
        for(int i = 0; i < s.size(); ++i){
            
            //even
            int left = i;
            int right = i+1;
            while(left >= 0 && right < s.size() && s[left] == s[right]){
                --left;
                ++right;
            }
            if(right-left-1 > maxlen){
                maxlen = right - left -1;
                start = left+1;
            }
            
            //odd
            left = i-1;
            right = i+1;
            while(left >= 0 && right < s.size() && s[left] == s[right]){
                --left;
                ++right;
            }
            if(right - left -1 > maxlen){
                maxlen = right - left -1;
                start = left +1;
            }
        }
        return s.substr(start,maxlen);
    }
};
----------------------------
方法3:DP
T（N） = n^2; S（N） = n^2；
思路：
1.dp[i][j] 表示子串s[i…j]是否是回文
初始化：dp[i][i] = true (0 <= i <= n-1); 
dp[i][i-1] = true (1 <= i <= n-1);
动态转移方程：
如果s[i] == s[j] 且它们的内部元素也是回文数字的话,则当前位置是回文的
dp[i][j] = (s[i] == s[j] && dp[i+1][j-1] == true);
class Solution {
public:
    string longestPalindrome(string s) {
        const int len = s.size();
        if(len <= 1)return s;
        bool dp[len][len];//dp[i][j]表示s[i..j]是否是回文
        memset(dp, 0, sizeof(dp));//对于dp,将dp的所有大小置为0
        int resLeft = 0, resRight = 0;
        dp[0][0] = true;
        for(int i = 1; i < len; i++)
        {
            dp[i][i] = true;
            dp[i][i-1] = true;//这个初始化容易忽略，当k=2时要用到
        }
        for(int k = 2; k <= len; k++)//枚举子串长度
            for(int i = 0; i <= len-k; i++)//枚举子串起始位置
            {
                if(s[i] == s[i+k-1] && dp[i+1][i+k-2])
                {
                    dp[i][i+k-1] = true;
                    if(resRight-resLeft+1 < k)
                    {
                        resLeft = i;
                        resRight = i+k-1;
                    }
                }
            }
        return s.substr(resLeft, resRight-resLeft+1);
    }
};
----------------------------
方法4:Manacher‘s Algorithm 马拉车算法
（讲的比较好的：https://blog.csdn.net/xingyeyongheng/article/details/9310555）
T（N） = n; S（N） = n;
思路：
1.通过观察发现，为了减少对原字符串奇偶性的判断，从头部开始，对原string进行插入#操作，到string的结尾，这样不论奇偶得到的都是奇数个字符。
2.对原字符串建立一个数组p,p[i]用来记录每一位i上以i为中心的回文子串半径
3.通过观察发现，在原string的头部加上$,半径-1(p[i]-1)即为所求的最长回文子串的长度，最长回文长度出现的位置是（p[i]中的i-最长回文长度）／2
4.求p数组的过程中，设置两个新的变量，maxlen表示目前最长子串最右边的位置，maxlen=p[i]+i;c便是目前最长子串中点的位置
5.那么p[i+k]就会有两种情况
(1）i+k > maxlen, 那么初始化p[i+k] = 1;
(2) i+k < maxlen, 那么这个串与i-k对称，有以下三种情况
2.1 i-k回文串范围有一部分在i之外，p[i+k] = p[i]-k = maxlen -(i+k);
2.2 i-k回文串范围全部在i之内，p[i+k] = p[i-k];
2.3 i-k回文串与i重叠，p[i+k] = p[i-k],并有可能继续增加
6.按照上面的几种情况更新代码，如果maxlen更长，把maxlen = i +p[i], c更改为i
class Solution {
public:
    string longestPalindrome(string s) {
        string t = "$#";
        for(int i = 0; i< s.size(); ++i){
            t += s[i];
            t += "#";
        }
        vector<int>p(t.size(),0);
        int maxlen = 0;
        int c = 0;
        for(int i= 1 ; i < t.size(); ++i){
            int imirror = 2*c-i;
            if(maxlen > i){
                p[i] = min(p[imirror],maxlen-i);
            }else{
                p[i] = 1;
            }
            while(t[i+p[i]]==t[i-p[i]])
                p[i]++;
            if(i+p[i]>maxlen){
                maxlen = i + p[i];
                c = i;
            }
        }
        int max = 0, index = 0;
        for(int i = 1; i < t.size(); i++)
            if(p[i] > max)
            {
                max = p[i];
                index = i;
            }
        return s.substr((index - max)/2, max-1);
    }
};

2.13复习
遍历方法。
注意：
1.方法的核心是遍历每一个字符，同时分为奇偶对它进行遍历，找到最长的惠文序列。
2.要注意因为会先左右指针移动再判断是否满足while条件，因此最长的长度是右指针减去左指针的位置再减1
class Solution {
public:
    string longestPalindrome(string s) {
        int maxlength = 0;
        int start = 0;
        for(int i = 0;i < s.size(); ++i){
            //字符串为偶数长度
            int left = i;
            int right = i+1;
            while(left >= 0 && right < s.size() && s[left] == s[right]){
                --left;
                ++right;
            }
            if(right -left -1 > maxlength){
                maxlength = right - left -1;
                start = left +1;
            }
            //字符串为奇数长度
            left = i-1;
            right = i+1;
            while(left >= 0 && right < s.size() && s[left] == s[right]){
                --left;
                ++right;
            }
            if(right -left -1 > maxlength){
                maxlength = right - left -1;
                start = left +1;
            }
        }
        return s.substr(start,maxlength);
    }
};

马拉车算法：
注意：
1.首先为了不对奇偶做判断，把每个字符之间都插入#，头部加入#，这样得到的新的字符串一定是奇数个长度
2.用一个dp数组来记录到每一个位置上的最长半径，用maxlength来记录当前能够到达的最远距离，center表示以当前最远距离为中心的位置
3.如果新遍历到的点大于最远距离，那么更新为1
如果在最远距离的范围内，一种是其镜像也在范围内，那么就取镜像即可，dp[2*center-i]
一种是镜像超出了范围，那么该点的最长半径就是中心的半径-增加的长度dp[center]-i+center
4.如果当前的位置还能左右扩展，那么继续扩展，并且更新最远距离和中心位置
5.再次遍历找到最长半径和坐标位置
6.因为把字符串进行扩展了，因此实际上最长的回文字符串长度是dp[i]-1,起始位置是（当前坐标-最长长度）/2，但是如果是从第一个元素开始回文，那么减去最长长度会小于0，因此需要在头部加上$
class Solution {
public:
    string longestPalindrome(string s) {
        string str = "$#";
        for(int i = 0; i < s.size(); ++i){
            str +=s[i];
            str += '#';
        }
        vector<int>dp(str.size(),0);
        int maxlength = 0;
        int center = 0;
        for(int i = 1; i < str.size(); ++i){
            if(i > maxlength){
                dp[i] = 1;
            }else{
                dp[i] = min(dp[2*center-i],dp[center]-i+center);
            }
            while(str[i+dp[i]] == str[i-dp[i]]){
                ++dp[i];
            }
            if(i+dp[i] > maxlength){
                maxlength = i+dp[i];
                center = i;
            }
        }
        
        int max = 0;
        int index = 0;
        for(int i = 0; i < dp.size(); ++i){
            if(dp[i]>max){
                max = dp[i];
                index = i;
            }
        }
        
        return s.substr((index-max)/2,max-1);
    }
};
