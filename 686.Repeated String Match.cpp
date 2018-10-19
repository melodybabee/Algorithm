题意：
给一个短的字符串A，一个长的字符串B，判断多次循环A是否能使B成为A的子串
方法一：
C++ find()方法，运用npos查找
思路：
1.首先反复循环A，并不断添加A，直到A的长度大于等于B
2.在B中寻找A，如果找到结尾还没有找到，那么再添加一次A，用来处理abc,cab的情况。如果仍没有找到，返回-1
3.在添加长度的过程中对长度进行计数，一旦找到子串，返回计数长度
注意：
1.c++中find()方法可以直接用来查找
2.npos用法
npos是一个常数，表示size_t的最大值（Maximum value for size_t）。很多容器用npos表示不存在的东西。
npos可以表示string的结束位置，是string::type_size 类型的，也就是find（）返回的类型。
find函数在找不到指定值得情况下会返回string::npos。
class Solution {
public:
    int repeatedStringMatch(string A, string B) {
        int count = 1;
        string newA = A;
        while(newA.size() < B.size()){
            ++count;
            newA += A;
        }
        if(newA.find(B) != newA.npos) return count;
        else{
            newA += A;
            if(newA.find(B) != newA.npos) return count+1;
            else return -1;
        }
    }
};
方法二：循环字符
思路：
1.在循环A的基础上找B，如果A的值与B的位置上的值相等，那么B前进一步
A[(i+j)%A.size()]注意以小组为单位循环A的写法，对原数组的长度取余
2.如果到不等的时候B已经到末尾，那么返回一共有多少个A，否则返回-1
注意：
普通情况下计算有多少个A可以写作(i+j)/A.size()+1;但是当A不用循环的时候这个值为2，应该输出1，因此公式应写作(i+j-1)/A.size()+1；
class Solution {
public:
    int repeatedStringMatch(string A, string B) {
        for(int i = 0; i < A.size(); ++i){
            int j = 0;
            while(j < B.size() && A[(i+j)%A.size()]==B[j]) ++j;
            if(j == B.size()) return (i+j-1)/A.size()+1;
        }
        return -1;
    }
};