class Solution {
public:
    string countAndSay(int n) {
        if(n == 1) return "1";
        string ret;
        string s = countAndSay(n-1);
        //stop at this step
        
        int count = 1;
        for(int i = 0; i < s.size();++i){
            if(i+1 >= s.size() || s[i]!= s[i+1]){
                ret += to_string(count)+s[i];
                count = 1;
            }
            else{
                ++count;
            }
            
        }
        return ret;
        
       
    }
};
/*
设计思路：
1.分析整个问题，如果想求n,需要求n-1,....直到求1.从上到下解决问题，因此需要用到递归
2.处理字符串的思路是：如果s的i+1个字符和第i个不等，或者大于s的长度，就把出现的次数和该字符添加到新串中
3.如果相等，在出现的次数上加1
4.for循环结束后返回新的字符串

注意：
1.区分"=="和"="!求你了！！
2.递归的原则是会使程序停留在再次调用函数本身的一步，收到return值之后再继续向下运行
3.注意调用countAndSay函数之后，返回值可以赋给新的值，countAndSay(n-1)的返回数据类型也是string,但注意返回的和新声名的数据类型要保持一致
4.注意count的位置，在每次输出到新的字符串之后，需要将count的值归0
5.在leetcode的代码可以进行本机调试，点击控制台右侧有一个按钮会显示全部的代码
如果想在本机运行添加上头文件即可
#include <iostream>
#include <string>

using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::to_string;

class Solution {
public:
    string countAndSay(int n) {
        if(n == 1) return "1";
        string ret;
        string s = countAndSay(n-1);
        //stop at this step
        int count = 1;
       
        for(int i = 0; i < s.size();++i){
            cout << "this line"<< endl;
            if(i+1 >= s.size() || s[i]!= s[i+1]){
                ret += to_string(count)+s[i];
                count = 1;
                cout << "this"<< endl;
            }
            else{
                ++count;
            }
            
        }
        return ret;
        
       
    }
};

int stringToInteger(string input) {
    return stoi(input);
}

int main() {
    string line;
    while (getline(cin, line)) {
        int n = stringToInteger(line);
        
        string ret = Solution().countAndSay(n);

        string out = (ret);
        cout << out << endl;
    }
    return 0;
}

*/