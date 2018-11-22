Sort()方法，T(n) = nlogn, S(n)=1;
补充：
sort()具体执行的代码
1.sort函数可以三个参数也可以两个参数，必须的头文件#include < algorithm>和using namespace std::sort()
default (1)	template <class RandomAccessIterator>  void sort (RandomAccessIterator first, RandomAccessIterator last);
custom (2)	template <class RandomAccessIterator, class Compare>  void sort (RandomAccessIterator first, RandomAccessIterator last, Compare comp);
2.它使用的排序方法是类似于快排的方法，时间复杂度为n*log2(n) 
3.Sort函数有三个参数：（第三个参数可不写） 
（1）第一个是要排序的数组的起始地址。 
（2）第二个是结束的地址（最后一位要排序的地址） 
（3）第三个参数是排序的方法，可以是从大到小也可是从小到大，还可以不写第三个参数，此时默认的排序方法是从小到大排序。//还可以自己定义排序规则。
4.排序的区间可以必须是通过迭代器遍历的(数组下标也算)，迭代器的类型为随机迭代器；
stl set map 使用红黑树 avl树作为底层数据结构的实现，不支持随机迭代器，所以不能使用sort来排序；
5.排序是通过多次内存的copy来实现的，所以链表不能使用stl 算法sort来对其排序(next指针修改问题)；
---------------------
*Anagram 相同字母异序词
思路：
1.给出两个字符串判断其是否都由相同的字母组成，顺序可以不一样
2.因此可以对两个string分别进行排序，之后直接比较两个string是否相等即可
class Solution {
public:
    bool isAnagram(string s, string t) {
       sort(s.begin(),s.end());
       sort(t.begin(),t.end());
       return s==t;
    }
};

hashtable方法：
思路：
1.hashtable中的key放s,t中的字母，value中放个数，每次出现一个该位置+1或者-1
2.因此设置一个hashtable循环，如果s,t的长度不相等，那么直接返回false；否则s存在一个元素，个数+1;t中存在一个元素，-1
3.循环map,如果map中的值存在（不为0），则为false,否则为true
4.注意count自动循环map,count此时表示的是pair<char,int>,因此如果count的第二个元素存在（不为空），则返回false,否则返回true
class Solution {
public:
    bool isAnagram(string s, string t) {
        if(s.size()!= t.size()) return false;
        unordered_map<char,int>map;
        for(int i = 0; i < s.size(); ++i){
            map[s[i]]++;
            map[t[i]]--;
        }
        for(auto count:map){
            if(count.second) return false;
        }
        return true;
    }
};

hashtable更为简单的方法：
因为the string contains only lowercase alphabets，因此可以建一个array转换为26进制
1.建立一个int的array，值都为0
2.将s,t中的字符都转换为26进制，对应counts中的位置，s中有的值在counts中+1，t中有的值在counts中-1
3.最后循环counts,如果任何一位上有值，返回false,否则返回true.
class Solution {
public:
    bool isAnagram(string s, string t) {
        if (s.length() != t.length()) return false;
        int n = s.length();
        int counts[26] = {0};
        for (int i = 0; i < n; i++) { 
            counts[s[i] - 'a']++;
            counts[t[i] - 'a']--;
        }
        for (int i = 0; i < 26; i++)
            if (counts[i]) return false;
        return true;
    }
};

二刷：
注意hashtable的应用。因为需要判断A中的字符在B中是否都存在，个数是否相等，满足hashtable key-value的性质，故选择hashtable.
T(n) = O(n), S(n) = O(1).
class Solution {
public:
    bool isAnagram(string s, string t) {
        unordered_map<char,int>map;
        if(s.size() != t.size()) return false;
        for(int i = 0; i < s.size(); ++i){
            ++map[s[i]];
            --map[t[i]];
        }
        for(auto c: map){
            if(c.second != 0) return false;
        }
        return true;
    }
};

follow up:
有关于字符编码
########################
ASCII码：
计算机内部，所有信息最终都是一个二进制值。每一个二进制位（bit）有0和1两种状态，因此八个二进制位就可以组合出256种状态，这被称为一个字节（byte）。
也就是说，一个字节一共可以用来表示256种不同的状态，每一个状态对应一个符号，就是256个符号，从00000000到11111111。
英语字符与二进制位之间的关系，做了统一规定，这被称为 ASCII 码。
ASCII 码一共规定了128个字符的编码，比如空格SPACE " " 是32（二进制00100000），大写的字母A是65（二进制01000001）。
这128个符号（包括32个不能打印出来的控制符号），只占用了一个字节的后面7位，最前面的一位统一规定为0。
########################
非ASCII码：
由于不同语言的关系，一个字节只能表示256种符号，肯定是不够的，就必须使用多个字节表达一个符号。
简体中文常见的编码方式是 GB2312，使用两个字节表示一个汉字，所以理论上最多可以表示 256 x 256 = 65536 个符号。
虽然都是用多个字节表示一个符号，但是GB类的汉字编码与后文的 Unicode 和 UTF-8 是毫无关系的。
########################
unicode
世界上存在着多种编码方式，同一个二进制数字可以被解释成不同的符号。因此，要想打开一个文本文件，就必须知道它的编码方式，否则用错误的编码方式解读，就会出现乱码。
如果有一种编码，将世界上所有的符号都纳入其中。每一个符号都给予一个独一无二的编码，那么乱码问题就会消失。这就是 Unicode，就像它的名字都表示的，这是一种所有符号的编码。
Unicode 当然是一个很大的集合，现在的规模可以容纳100多万个符号。每个符号的编码都不一样。
U+0041表示英语的大写字母A。
问题：
比如，汉字严的 Unicode 是十六进制数4E25，转换成二进制数足足有15位（100111000100101），也就是说，这个符号的表示至少需要2个字节。
表示其他更大的符号，可能需要3个字节或者4个字节，甚至更多。
第一个问题是，如何才能区别 Unicode 和 ASCII ？计算机怎么知道三个字节表示一个符号，而不是分别表示三个符号呢？
第二个问题是，我们已经知道，英文字母只用一个字节表示就够了，如果 Unicode 统一规定，每个符号用三个或四个字节表示，那么每个英文字母前都必然有二到三个字节是0，这对于存储来说是极大的浪费，文本文件的大小会因此大出二三倍，这是无法接受的。
########################
UTF-8
UTF-8 就是在互联网上使用最广的一种 Unicode 的实现方式。
这里的关系是，UTF-8 是 Unicode 的实现方式之一。
UTF-8 的编码规则很简单，只有二条：
1）对于单字节的符号，字节的第一位设为0，后面7位为这个符号的 Unicode 码。因此对于英语字母，UTF-8 编码和 ASCII 码是相同的。
2）对于n字节的符号（n > 1），第一个字节的前n位都设为1，第n + 1位设为0，后面字节的前两位一律设为10。剩下的没有提及的二进制位，全部为这个符号的 Unicode 码。

Unicode符号范围     |        UTF-8编码方式
(十六进制)          |              （二进制）
----------------------+---------------------------------------------
0000 0000-0000 007F | 0xxxxxxx
0000 0080-0000 07FF | 110xxxxx 10xxxxxx
0000 0800-0000 FFFF | 1110xxxx 10xxxxxx 10xxxxxx
0001 0000-0010 FFFF | 11110xxx 10xxxxxx 10xxxxxx 10xxxxxx

如果本题改为Unicode类型，即底层的编码方式不同，比如输入汉字 你好 和 好你：
如果我们使用auto类型来循环不会影响底层的编码方式。
同样对于sort方法，是直接让标准库处理 Unicode 字符，也不会受到影响。


