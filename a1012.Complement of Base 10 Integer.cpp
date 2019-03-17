题意：找到一个数字的二进制数字，0，1对调再转换为10进制的数字
方法一：暴力拆解
思路：
1.首先用一个字符串记录下来将数字转换为的二进制字符串，因为新加入的字符是在尾部的，因此需要对它进行反转
2.遍历。进行0，1对调。
3.再从后向前对字符串进行十进制转换，输出结果即可。
class Solution {
public:
    int bitwiseComplement(int N) {
        string s = "";
        if(N == 0) s = to_string(N);
        while(N != 0){
            int temp = N%2;
            s += to_string(temp);
            N /= 2;
        }
        
        reverse(s.begin(),s.end());
        //cout << s << endl;
        for(int i = 0; i < s.size(); ++i){
            if(s[i] == '0') s[i] = '1';
            else s[i] = '0';
        }
        
        //cout << s << endl;
        int count = 0;
        int ret = 0;
        for(int i = s.size()-1; i >= 0; --i){
            ret += (s[i]-'0') * pow(2,count);
            ++count;
        }
        return ret;
    }
};


方法2:位运算
思路：
1.因为需要找到一个数字二进制表示的相反数，转换为十进制
2.那么可以找到大于等于N的各个位上都是1的二进制数字，这样直接相减就是等于其补码对应的数字
比如5，二进制为101，大于等于他的都是1的二进制数字是111，相减后为010，就是结果
3.那么首先初始化这个值为1，每次添加一位1的方法就是将数字*2+1
class Solution {
public:
    int bitwiseComplement(int N) {
        int x = 1;
        while(x < N) x = x*2 +1;
        return x-N;
    }
};