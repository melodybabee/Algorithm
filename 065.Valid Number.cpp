题意：
判断是否是有效数字
思路：
1.循环整个字符串，共需要讨论6种不同的情况，每种情况设立一个标志位。
(1)如果是0-9之间的数组,num标志位true,numaftere标志位true
(2)如果是e,如果之前出现过e，或者e之前没有出现过数字，false;其他情况e的标志位为true,numaftere标志为false,因为e后面的必须要跟数字。
(3)如果是正负号，如果前一位不等于e和空格,那么返回false,把sign的标志位标为true
(4)如果是.,如果之前已经存在过.或者之前已经存在过e,那么返回false，把dot的标志位标为true
(5)如果是空格，空格只能出现在头部或者尾部，那么如果空格后面不等于空格且之前存在过上述任何一种标记位，即为false
(6)出现其余的任何符号直接返回false
class Solution {
public:
    bool isNumber(string s) {
        int n = s.size();
        bool num = false;
        bool numaftere = true;
        bool exp = false;
        bool sign = false;
        bool dot = false;
        for(int i = 0; i< n;++i){
            if(s[i] >= '0' && s[i] <= '9'){
                num = true;
                numaftere = true;
            }
            else if(s[i] == 'e'){
                if(!num || exp) return false;
                exp = true;
                numaftere = false;
            }
            else if(s[i] == '+' || s[i] == '-'){
                if(i>0 && s[i-1] != 'e'&& s[i-1] != ' ') return false;
                sign = true;
            }
            else if(s[i] == '.'){
                if(dot || exp ) return false;
                dot = true;
            }
            else if(s[i] == ' '){
                if(i< n-1 && s[i+1] != ' ' && (exp || dot || num || sign)) return false;
            }else return false;
        }
        return num && numaftere;
    }
};