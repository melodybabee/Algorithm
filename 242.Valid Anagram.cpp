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