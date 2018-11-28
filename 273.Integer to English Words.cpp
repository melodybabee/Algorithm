题意：
根据整数把它转换为英文表达
思路：
1.题目中给出的范围是0-2^31-1 = 2147483647，每三位三位判断，最多判断4组即可。
2.从整数的尾部开始，做1000的取余操作，每次处理3个数字。
进入递归函数汇总百位表示为／100，后两位是%100，最后一位对后两位数字做%10操作。
3.当后两位小于20的时候直接输出，对应位置是自定义0-19的数组中的位置。如果大于20，做／10的操作，再在0-90中找对应位置。
当个位数字存在的时候在0-19的数组中找对应的个位数字。如果不存在置空。
4.再处理百位数字，如果百位存在，那么在百位后面添加hundred再加上处理好的后两位数字。
5.在主方法中对原数组进行／1000操作，再依次三位三位的处理后面的数字。当%1000存在的时候调用递归同时在后面加上千／百万／十亿的计量单位+已经转换好的字符串
如果%1000不存在那么直接返回结果字符串
6.最后检查结尾，如果有空格的话删除空格
7.如果结果为空返回zero,不为空返回结果字符串
class Solution {
public:
    string numberToWords(int num) {
        string ret = helper(num %1000);
        vector<string>v = {"Thousand","Million","Billion"};
        for(int i = 0; i < 3; ++i){
            num /= 1000;
            ret = num %1000 ? helper(num%1000) + " " + v[i] + " " + ret: ret;
        }
        if(ret.back() == ' ') ret.pop_back();
        return ret.empty()? "Zero" : ret;
    }
    
    string helper(int num){
        string res;
        vector<string> vec1 ={"","One","Two","Three","Four","Five","Six","Seven","Eight","Nine","Ten","Eleven","Twelve","Thirteen","Fourteen","Fifteen","Sixteen","Seventeen","Eighteen","Nineteen"};
        vector<string> vec2 = {"","","Twenty","Thirty","Forty","Fifty","Sixty","Seventy","Eighty","Ninety"};
        int a = num/100;
        int b = num%100;
        int c = num%10;
        res = b < 20? vec1[b] : vec2[b/10] + (c ? " " + vec1[c] : "");
        if(a > 0) res = vec1[a] + " Hundred" + (b ? " "+ res : "");
        return res;
    }
};