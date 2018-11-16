题意：
在按字母顺序无限循环的字符串中，找到目标子串中有多少无限字符串的子串。
思路：
1.首先需要理解题意，题目中给出的无限循环字符串是由A到Z按字母顺序无限循环的，如果想从一个给定的字符串中找到无限字符串的子串，要不就是按字母顺序排列的，要不就是单个的字符。
2.因此只要建立一个dp数组，dp[i]表示以i为结尾的子串有多少个。
开始循环目标字符串，如果后一位是前一位+1或者后一位是前一位+25，那么长度++，把长度更新在dp数组的相应位置，注意数组是int形式，需要从字符转换为整数形
3.如果不满足，那么长度为1。
4.最后返回dp数组上每一位的和即可。
补充：
1.c++ accumulate()函数表示ccumulate(vec.begin() , vec.end() , 0)，数组的头部，数组的尾部和求和的起始值
2.在计算字符串的时候，如果是按照字典顺序的，那么直接+1判断是否连续即可。但是更新在dp数组中需要转换为数字，对应减去'a'
class Solution {
public:
    int findSubstringInWraproundString(string p) {
        vector<int> dp(26,0);
        int len = 0;
        for(int i = 0; i < p.size(); ++i){
            if(i > 0 && (p[i-1] +1 == p[i] || p[i-1] == p[i] + 25))
                ++len;
            else{
                len = 1;
            }
            dp[p[i] - 'a'] = max(dp[p[i]-'a'], len);
        }
        return accumulate(dp.begin(),dp.end(),0);
    }
};


