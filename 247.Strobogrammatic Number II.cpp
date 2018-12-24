题意：246follow up,找到目标个数长度的正反可颠倒的数字。
方法一：递归
思路：
1.如果想形成正反可颠倒的数字，那么有两种情况，如果是偶数个，那么从空开始依次向两侧扩展。
如果是奇数个，那么从1，8，0这三个数字开始依次向两侧扩展。
2.不断在数字的两侧添加(1,1),(8,8),(6,9),(9,6)两个数字开始递归，除了最后一层不能添加(0,0)之外，其余各层可以添加(0,0)
3.递归的边界条件是如果m减到0或者1了，那么则开始依次向外扩展。用temp数组记录下上一次递归得到的值。
4.遍历temp数组中的每个数字，开始扩展，返回结果数组。
class Solution {
public:
    vector<string> findStrobogrammatic(int n) {
        return helper(n,n);
    }
    
    vector<string> helper(int m, int n){
        if(m == 0) return {""};
        if(m == 1) return{"1","8","0"};
        vector<string>temp = helper(m-2,n);
        vector<string>ret;
        for(auto t: temp){
            if(m != n) ret.push_back("0"+t+"0");
            ret.push_back("1"+t+"1");
            ret.push_back("8"+t+"8");
            ret.push_back("6"+t+"9");
            ret.push_back("9"+t+"6");
        }
        return ret;
    }
};

方法2:遍历
思路：
1.先分成奇数数组和偶数数组两个分别进行初始化
2.开始从2/3开始循环（比初始化的值大1），每次+2，分别在已有的数组两侧加上新的值，如果i和n的值相等，那么不要在头部和尾部加入0
3.最后返回遍历结束后的结果
class Solution {
public:
    vector<string> findStrobogrammatic(int n) {
        vector<string>even{""};
        vector<string>odd{"0","1","8"};
        vector<string>ret = even;
        if(n%2 == 1) ret = odd;
        for(int i = (n%2) +2; i <= n; i += 2){
            vector<string>t;
            for(auto r : ret){
                if(i != n) t.push_back("0"+r+"0");
                t.push_back("1"+r+"1");
                t.push_back("8"+r+"8");
                t.push_back("6"+r+"9");
                t.push_back("9"+r+"6");
            }
            ret = t;
        }
        return ret;
    }
};
