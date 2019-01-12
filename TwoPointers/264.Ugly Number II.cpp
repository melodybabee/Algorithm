题意：263 follow up,找出第目标值个丑数
方法一：暴力拆解
TLE
思路：
1.完全利用263中的方法对所有数字依次进行遍历，判断是否是丑数，是的话+1。
遍历到指定个数输出遍历到的数字。
class Solution {
public:
    int nthUglyNumber(int n) {
        if(n == 0) return 0;
        int ret = 0;
        int temp = 0;
        while(ret < n){
            if(isugly(temp)) ++ret;
            if(ret < n)++temp;
        }
        return temp;
    }
    
    bool isugly(int t){
        if(t==0) return false;
        while(t % 2 == 0) t /= 2;
        while(t % 3 == 0) t /= 3;
        while(t % 5 == 0) t /= 5;
        return t == 1;
    }
};
方法2:DP
思路：
1.因为所有的丑数都是由2，3，5乘积乘来的，目标是把它们从小到大排列
2.那么建立一个数组放入第一个数字1，分别设置3个变量对其进行*2，*3，*5操作
3.取三个值中最小的值放到数组中，判断是从哪个因子乘积得到的，对其+1，再次进入循环
4.直到数组中的数字的个数等于目标值，输出数组中的最后一个元素
class Solution {
public:
    int nthUglyNumber(int n) {
        vector<int>ret(1,1);
        int i = 0;
        int j = 0;
        int k = 0;
        while(ret.size() < n){
            ret.push_back(min(min(ret[i]*2,ret[j]*3),ret[k]*5));
            if(ret.back() == ret[i]*2) ++i;
            if(ret.back() == ret[j]*3) ++j;
            if(ret.back() == ret[k]*5) ++k;
        }
        return ret.back();
    }
};

1.12复习：
注意：
1.本题的实质是设置了三个指针分别对各自2，3，5的数列进行循环，判断哪个小就在结果数组中输入小的那个
2.注意因为进入while循环之后要push进去新的数字，因此while的循环判断条件中没有等号，最后返回结果数组中的最后一位
class Solution {
public:
    int nthUglyNumber(int n) {
        vector<int>vec(1,1);
        int i = 0;
        int j = 0;
        int k = 0;
        while(vec.size() < n){
            vec.push_back(min(min(vec[i]*2,vec[j]*3),vec[k]*5));
            if(vec.back() == vec[i]*2) ++i;
            if(vec.back() == vec[j]*3) ++j;
            if(vec.back() == vec[k]*5) ++k;
        }
        return vec.back();
    }
};