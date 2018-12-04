题意：
把两个形式为string的数字相加为新的字符串。
思路：
1.设置两个指针从尾部开始循环，当其中一个大于等于0的时候就进入循环，当短的一方到达头部的时候设置值为0.
2.进入循环之后把每一个字符转换为数字，相加，设置一个数字当作进位。
3.在结果字符串的头部插入和对10取余的数字，注意此处要转换为字符形式，进位值记录下和／10
4.当结束循环的时候判断进位值是否为1，为1增加在头部，不为1直接返回。
注意：
字符转换为数字-'0'
数组转换为字符+'0'
class Solution {
public:
    string addStrings(string num1, string num2) {
        int m = num1.size()-1;
        int n = num2.size()-1;
        int carry = 0;
        string ret;
        while(m >= 0 || n >= 0){
            int i = m >= 0 ? num1[m] -'0' : 0;
            --m;
            int j = n >= 0 ? num2[n] -'0' : 0;
            --n;
            int sum =  i + j + carry;
            ret.insert(ret.begin(),sum%10 +'0');
            carry = sum/10;
        }
        return carry >= 1? "1" + ret : ret;
    }
};