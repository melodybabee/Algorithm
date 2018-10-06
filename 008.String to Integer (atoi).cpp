题意：把字符串反转为数字
数了一下，本题共WA了18次才AC，虽然题目含金量不高，但是所有的test cases需要完完全全想清楚，切忌边调试边提交。
要求：
1.遇到数字前所有的空格可以忽略，都是空格返回0
2.可以任选正号或者负号其一作为数字前面的数字
3.如果遇到数字前的字符不是空格，或者正负号其中之一，返回0
4.遇到数字后，如果遇到非数字的其他任何字符，可忽略，只返回数字部分
5.如果超过int范围，【-2147483648，2147483647】，则返回INT_MAX或者INT_MIN
思路：
1，按照上面的要求把所有情况考虑到就可以
注意：
1.while去空格和判断正负号应该放在for循环的外，预先处理字符串
2.注意判断正负后，后面可能会遇到提前输出或者超出范围的情况，不结束for循环便输出，那么都需要判断flag是否为真
3.注意超出范围的判断，因为需要在最后一次进入for循环之前判断是否超出范围，因此对INT_MAX除以10操作
同时进入最后一次for循环的数字不可以超过7，因此还需要加上str[i] - '0'>7，需要特别注意

class Solution {
public:
    int myAtoi(string str) {
        int ret = 0;
        bool flag = false;
        int i = 0;
        while(str[i] == ' ') ++i;
        if(str[i] == '-') {
                flag = true;
                ++i;
            }else if(str[i] == '+'){
                ++i;
            }
        for(i; i< str.size(); ++i){
            if(!isdigit(str[i])) {
                if(flag) return -ret;
                return ret;
            }
            if(ret > INT_MAX/10 || (ret == INT_MAX/10  && str[i] - '0'>7)) {
                if(flag) return INT_MIN;
                return INT_MAX;
            }
            ret = 10*ret + str[i]-'0';
            
        }
        if(flag) return -ret;
        return ret;
        
    }
};