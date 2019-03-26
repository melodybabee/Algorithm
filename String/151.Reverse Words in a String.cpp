题意：
不改变单词的顺序，反转字符串。
方法一：stack
思路：
1.没有满足题目要求的线性复杂度，但是是最直接的思路
2.因为通过空格区分单词，那么从头开始遍历把每个单词都依次push到栈中，再依次拿出，满足栈后进先出的特点。因此可以实现反转。
3.直接暴力循环我认为也是可以的，但是此处引入istringstream和ostringstream更为快捷。
4.用一个istringstream作为输入流，is中的内容是原字符串，依次一个个读取string类型的单词
stream流每次以空格作为读取结束的标识。如果含有非空格字符，那么每次>>操作就会提取连在一起的非空格字符，读取一个push到栈中一个
5.当栈不为空的时候，输出流中依次输入栈顶元素，并在后面加入空格。
6.因为是void方法，最后把原先的字符串替换为输出流中的字符串，去掉最后一个空格即可。
class Solution {
public:
    void reverseWords(string &s) {
        stack<string> st;
        istringstream is(s);
        ostringstream os;
        string word;
        
        while(is >> word){
            st.push(word);
        }
        
        while(!st.empty()){
            os << st.top() << " ";
            st.pop();
        }
        
        s = os.str();//从输出流中读取所有字符串
        s.pop_back();
    }
};
方法2:不用stack，直接stringstream
思路：
1.首先把字符串输入到字符流中，设置一个string类型的变量依次读取
2.首先把第一个元素赋值给s,后面的单词就加在s的前面
3.如果s为空，那么不会进入while循环；如果s为都是空字符的字符串，那么会清空s
class Solution {
public:
    void reverseWords(string &s) {
        istringstream is(s);
        string temp;
        is >> s;
        while (is >> temp) s = temp + ' ' + s;
        if(s != "" && s[0] == ' ') s = "";
    }
};
方法3:getline
思路：
1.getline()函数
istream& getline (istream&  is, string& str, char delim);
作用是： 从istream中读取至多n个字符(包含结束标记符)保存在str对应的数组中,遇到delim的时候停止。
is    ：表示一个输入流，例如cin。
str   ：string类型的引用，用来存储输入流中的流信息。
delim ：char类型的变量，所设置的截断字符；在不自定义设置的情况下，遇到’\n’，则终止输入。
2.如果有多个空格字符连在一起，那么t会赋值为空字符串，因此需要判断一下t是否为空，如果为空那么不连在s上
class Solution {
public:
    void reverseWords(string &s) {
        istringstream is(s);
        string temp;
        s = "";
        is >> s;
        while(getline(is,temp,' ')){
            if(temp.empty()) continue;
            s = s.empty() ? temp : temp + ' ' + s;
        }
    }
};
方法4:两次反转
思路：
1.先反转字符串，再依次反转每个单词
2.用一个cur
坐标记录下当前所在的位置，以及是否需要加入空格隔断
3.遍历反转以后的字符串，如果为0跳过，不为0的时候用一个指针向后查找到空格的位置，反转，注意反转的起始位置和结束位置
用cur来表示新的坐标从而替换掉旧的字符串。
4.最后用resize()方法把字符串截取到cur指针的位置。
class Solution {
public:
    void reverseWords(string &s) {
        int cur = 0;
        reverse(s.begin(),s.end());
        for(int i = 0; i< s.size(); ++i){
            if(s[i] != ' '){
                if(cur != 0) {
                    s[cur] = ' ';
                    ++cur;
                }
                int j = i;
                while(j < s.size() && s[j] != ' '){
                    s[cur] = s[j];
                    ++cur;
                    ++j;
                }
                reverse(s.begin()+cur-j+i,s.begin()+cur);
                i = j;
            }
        }
        s.resize(cur);
    }
};
补充：c++中输入输出流的使用
1.C++引入了ostringstream、istringstream、stringstream这三个类，要使用他们创建对象就必须包含<sstream>这个头文件。
istringstream类用于执行C++风格的串流的输入操作。
ostringstream类用于执行C风格的串流的输出操作。
strstream类同时可以支持C风格的串流的输入输出操作。
每次以空格作为读取结束的标识。

istringstream的构造函数原形如下：
istringstream::istringstream(string str);
它的作用是从string对象str中读取字符。
#include<iostream>  
#include<sstream>        //istringstream 必须包含这个头文件
#include<string>  
using namespace std;  
int main()  
{  
    string str="i am a boy";  
    istringstream is(str); //创建了一个名为is的istringstream对象，读取string str字符 
    string s;  
    while(is>>s)//从输入流中一个个读取string类型的字符串
    {  
        cout<<s<<endl;  
    }  
      
} 
输出是:
i
am
a
boy

12.10复习
方法一：stack
注意：
1.利用栈需要考虑' '的情况，如果不满足的话需要单独判断
class Solution {
public:
    void reverseWords(string &s) {
        stack<string> st;
        for(int i = 0; i < s.size(); ++i){
            if(s[i] == ' ') continue;
            int j = i;
            for(j = i; j <= s.size();++j){
                if(s[j] == ' ' || j == s.size()){
                    st.push(s.substr(i,j-i));
                    if(j == s.size()) break;
                    while(s[j] == ' ')++j;
                    break;
                }else{
                    continue;
                }
            }
            i= j-1;
        }
        s = "";
        if(st.empty()) return;
        while(!st.empty()){
            s +=st.top();
            st.pop();
            if(!st.empty()) s += " ";
        }
    }
};
方法2:先整体反转，再局部反转
注意：建立一个cur指针后面作为遍历的index,为了便于添加中间的空格元素，j作为每个单词的循环s 
class Solution {
public:
    void reverseWords(string &s) {
        int cur = 0;
        reverse(s.begin(),s.end());
        for(int i = 0; i < s.size(); ++i){
            if(s[i] != ' '){
                if(cur != 0){
                    s[cur] = ' ';
                    ++cur;
                }
                int j = i; 
                while(j < s.size() && s[j] != ' '){
                    s[cur] = s[j];
                    ++j;
                    ++cur;
                }
                reverse(s.begin()+i+cur-j,s.begin()+cur);
                i = j;
            }
        }
        s.resize(cur);
    }
};
方法3:用istringstream方法
class Solution {
public:
    void reverseWords(string &s) {
        istringstream is(s);
        string temp;
        is >> s;
        while(is >> temp) s = temp + ' ' + s;
        if(s != "" && s[0] == ' ') s = "";
    }
};

3.26复习
注意：
先整体反转再局部反转如果不处理空格的话思路非常直接：
class Solution {
public:
    string reverseWords(string s) {
        reverse(s.begin(),s.end());
        for(int i = 0; i < s.size(); ++i){
            if(s[i] != ' '){
                int j = i;
                while(j < s.size() && s[j] != ' '){
                    ++j;
                }
                reverse(s.begin()+i,s.begin()+j);
                i = j;
            }
        }
        return s;
    }
};
但是无法处理头部尾部以及中间有空格的情况，所以要建立cur指针来处理空格
cur表示从0开始的值，如果遍历到cur不为0，表示需要加上一个空格
在while循环找单词结尾的时候也需要一步一步更新cur,反转的时候因为要到cur所以要以cur为结尾，开始的指针要从i开始加上cur与j之间的差
最后因为还会有空格的情况，因此需要s.resize(cur)的意思是把字符串停留在cur的位置上
reverse()方法要用迭代器，表示头部的位置和尾部的位置+1
class Solution {
public:
    string reverseWords(string s) {
        int cur = 0;
        reverse(s.begin(),s.end());
        for(int i = 0; i < s.size(); ++i){
            if(s[i] != ' '){
                int j = i;
                if(cur != 0){
                    s[cur] = ' ';
                    ++cur;
                }
                while(j < s.size() && s[j] != ' '){
                    s[cur] = s[j];
                    ++cur;
                    ++j;
                }
                //此时cur的位置已经在整个字符串的最后一个字符的下一位
                reverse(s.begin()+i+cur-j,s.begin()+cur);
                i = j;
            }
        }
        s.resize(cur);
        return s;
    }
};
stack
注意：
1.要把i在循环结束之后与j对齐
2.注意可以用pop_back()弹出最后一个元素
3.
class Solution {
public:
    string reverseWords(string s) {
        stack<string>st;
        string result;
        for(int i = 0 ; i < s.size(); ++i){
            if(s[i] == ' ') continue;
            int j = i;
            while(j < s.size() && s[j] != ' '){
                ++j;
            }
            //substr的两个变量表示开始位置和长度
            string temp = s.substr(i,j-i);
            st.push(temp);
            i = j;
        }
        while(!st.empty()){
            result += st.top();
            st.pop();
            result += " ";
        }
        result.pop_back();
        return result;
    }
};
