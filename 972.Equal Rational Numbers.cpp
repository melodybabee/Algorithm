Rational Numbers 有理数
题意：
判断两个可能有无限循环部分的字符串是否完全相等
思路：
1.因为是字符串，那么首先需要把他们转换为double类型进行比较。如果相等那就是相等
2.判断字符串中是否有不断重复的部分，如果没有，那么直接转换为double类型
3.如果有，那么把字符串分为前半部分，和后半部分的重复部分，因为重复部分的一定在字符串的尾部，因此也容易找他的长度。
接着用前半部分不断加上后半部分，多次循环，因为本题中的字符串长度不大，最长为4，会有1，2，3，4四种可能，因此循环20次左右一定能判断出时候相等。
4.最后把新形成的字符串转换为double类型返回进行比较即可。
注意：
1.c++ stod()方法可以直接将字符串转换为double类型
2.string::npos中的npos表示字符串的结尾，如果不等于结尾，说明在中间部分找到了括号，那么就需要截取
3."0.9(9)"和"1."在不断循环之后会趋于相等，本题数据规模小，因此循环20次左右后即可近似于相等，直接回返回true
class Solution {
public:
    bool isRationalEqual(string S, string T) {
        return f(S) == f(T);
    }
    
    double f(string s){
        auto i = s.find('(');
        if(i != string::npos){
            string front = s.substr(0,i);
            string end = s.substr(i+1,s.size()-i-2);
            for(int i= 0; i <= 20; ++i){
                front += end;
            }
            return stod(front);
        }
        return stod(s);
    }
};