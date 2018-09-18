class Solution {
public:
    int titleToNumber(string s) {
        int ans = 0;
        for(int i = 0; i < s.size(); ++i){
            ans = ans*26 + s[i]-'A'+1;
        }
        return ans;
    }
};
/*
是第168题的逆向
思路：
1.循环字符串，如果只有一个数字，s[i]-'A'+1
2.如果有多位数字，每多加一位乘一次26，因此要有一个初始值为0
注意：
1.26进制转为10进制的时候，s[i]-'A'直接相减就是数字结果，A要变为字符
2.不要忘了最后+1
*/