问题：
1.如何分割string,如何分割空格
【补充】C++的输入输出
(1)基于控制台的I/O
基于控制台的I/O：
iostream: istream从流中读取
          ostream写到流中去
          iostream对流进行读写，从istream和ostream派生
基于文件的I/O：
fstream: ifstream从文件中读取，从istream派生
         ofstream写到流中去,从ostream派生
         fstream对流进行读写，从iostream派生
基于字符串的I/O:
sstream: istringstream从string中读取，从istream派生
         ostringstream写到string中去,从ostream派生
         stringstream对string进行读写，从iostream派生
头文件  #include <sstream>  
描述：从流中提取数据，支持 >> 操作
这里字符串可以包括多个单词，单词之间使用空格分开
istringstream的构造函数原形：  
istringstream::istringstream(string str);  
istringstream istr("1 56.7");  //把字符串"1 56.7"存入字符串流istr中 
----------------------------
把字符串类型转为其他类型输出
int n;  
double d;  
istr>>n;//第一个数为整型数据，输出1   
istr>>d;//第二个数位浮点数，输出56.7 
>>表示存入的字符流的含义 
from：https://www.cnblogs.com/ranjiewen/p/5312909.html
2.hashmap的操作：
hash_map <int, int> hm1；
hm1.insert(Int_Pair(2, 20));//map中插入key-value对
hm1_RcIter = hm1.find( 2 );//hashmap找到key为2的元素
cout<<hm1_RcIter -> second；//输出的就是20这个值
hm1_RcIter = hm1.find(4);
if (hm1_RcIter == hm1.end( ))//找到map的结尾仍然找不到，则返回没有这个元素
      cout << "The hash_map hm1 doesn't have an element "
           << "with a key of 4." << endl;
   else
      cout << "The element of hash_map hm1 with a key of 4 is: "
           << hm1_RcIter -> second << "." << endl;

思路：
1.建立两个散列表，key分别存放pattern和string的值，value存放数值
2.循环其中一个string，分别找pattern第0位和str第0位是否存在，如果有一方存在或者都存在，判断是否相等，不相等返回false
3.如果都不存在，分别在这两个map中添加数值
4.返回i的大小与其中另一个string的长度是否相等

注意：
1.string可以按位循环

class Solution {
public:
    bool wordPattern(string pattern, string str) {
        unordered_map<char,int> map1;
        unordered_map<string,int> map2;
        istringstream in(str);
        //istringstream是C++中从string读取的STL,in是读取后存储的变量名，会以空格划分依次读取，str即原字符串
        int i = 0;
        for(string word; in >> word; ++i){
            //word作为in的输出值，每次输出一个
            if(map1.find(pattern[i]) != map1.end() || map2.find(word) != map2.end()){
                if(map1[pattern[i]] != map2[word]) return false;
            }
            else{
                map1[pattern[i]] = map2[word] = i+1;//注意map不可存0
            }
        }
        return pattern.size() == i;
        
    }
};

思路：
1.用一个map也可以实现，key放pattern的字符，value放str输出的word
2.先找key是否存在，若存在，判断是否和word相等，不等返回false
3.不存在遍历map看word是否存在，存在不等返回false
4.如果都不存在再写入新的key-value对
5.返回长度是否相等
class Solution {
public:
    bool wordPattern(string pattern, string str) {
        unordered_map<char,string>map;
        istringstream in(str);
        int i = 0;
        for(string word; in >> word;++i){
            if(map.find(pattern[i]) != map.end()){
                if(map[pattern[i]] != word) return false;
            }else{
                for(unordered_map<char,string>::iterator it = map.begin();it != map.end();++it){
                    if(it->second == word) return false;
                    }
                map[pattern[i]] = word;
            }
        }
        return i == pattern.size();
    }
};