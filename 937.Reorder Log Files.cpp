题意：
有一个log文件，排除string中的第一个字符，对后面的string进行先字母后数字的排序。
方法一：分别设置letter vector和num vector 
思路：
1.循环原数组，注意因为需要取出的是数组中的字符串，因此用for(string &s : logs)形式进行循环，之前想不起来用这种形式进行循环
2.循环到第一个空格的后一位，如果是字母，把第一位加入到尾部，push到新的isletter vector中
3.如果是数字直接放入数字的数组中
4.因为要求对字母进行排序，用sort()方法直接排序即可，做题的时候以为第一个字母相同需要比较第二位，但后来看题目中没有类似的要求，因此暴力排序即可
5.再把isletter中的字符串依次复原，最后在后面加入数字数组中的字符串，输出数组即可
注意：
1.找子串的时候，s.substr(0,i)表示返回从0开始的长度为i的子串
s.substr(i+1) 表示返回i+1开始到尾部的所有子串
class Solution {
public:
    vector<string> reorderLogFiles(vector<string>& logs) {
        vector<string> isletter;
        vector<string> isnum;
        for(string &s : logs){
            int i = 0;
            while(s[i] != ' ') ++i;
            if(isalpha(s[i+1])) isletter.push_back(s.substr(i+1) + " " + s.substr(0,i));
            else isnum.push_back(s);
        }
        sort(isletter.begin(), isletter.end());
        for(string &s : isletter){
            int i = s.size()-1;
            while(s[i] != ' ') --i;
            s = s.substr(i+1) + " " + s.substr(0,i);
        }
        for (string &s : isnum) isletter.push_back(s);
        return isletter;
    }
};
优化：
看到讨论区有写到stable_sort和partition_sort的方法，overriding原有的sort cmp排序方法。
还有引入sstream进行输出的。
【待学习】

Contest 110总结：
1.本题是这次的第一道easy题，没有AC，做题的时候纠结于对于字母字符串的第一位相同如何比较第二位，这样增加了题目的难度，简单思考了下应该需要继续循环字母串再进行比较【待深入思考】
但是后来再次阅读题目发现并没有类似的要求，说明了读题的重要性。
现在对于长的、一上来读不懂的题目还会有抵触情绪，要刻意纠正！
2.还有一个心态上需要调整的是，难题／没有思路的题目尽可能的多写，不会高级的方法就用暴力／最基础的方法写。一为了促进思考，二可能写着写着会茅塞顿开。
上述的方法是非常基础的字符串操作，没有涉及目前不会的sort复写和sstream,同时注意抓紧学习新知识。
3.第二道是tree的问题，其实一开始就写出正确思路了，有一点小错，再看一遍就能订正，却自暴自弃了一会儿快1个小时才AC。
注意心态！！反复强调！！
没有算法题是不需要思考就可以写出来的，一梳理心态，二继续加快刷题速度多多见题多多思考。