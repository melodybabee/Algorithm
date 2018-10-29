题意：
给出一个数字和目标值，找到数字长度字符串全排列的数组中，目标值位置的字符串是什么。
思路：
1.通过观察发现，因为全排列是按照1，2，3，4，...的序列依次排序，因此可以通过（目标值／长度-1的阶乘）求得目标值所在位置的第一位数字是什么
然后对目标值取余，可以在第一个大组中再按照数字氛围若干小组，重复上述操作。
2.为了便于书写，首先声明一个数组记录下阶乘，这样目标值除以的除数依次就是由后向前的阶乘
3.再创建一个新的数组记录1-n的n位数字，注意从1开始，这样目标值／阶乘的位置就是数字数组中对应数字的位置
4.直到n小于1的时候结束
注意：
1.因为数字数组从1开始，所以k除以目标值的商对应的是数组下标，因此--k，注意本题中的下标值
2.string也可以进行push_back操作，直接在后面加入想加入的值就可以
3.vector.erase(i)方法可以删除位置i上的元素，剩下的元素从0开始依次排列
class Solution {
public:
    string getPermutation(int n, int k) {
        string ret;
        vector<int> f(n,1);
        vector<char> vec(n,1);
        for(int i= 1; i< n; ++i){
            f[i] = i*f[i-1];
        }
        for(int i = 0;i< n;++i){
            vec[i]= (i+1) + '0';
        }
        --k;
        for(int i = n; i>=1; --i){
            int pos = k/f[i-1];
            ret.push_back(vec[pos]);
            vec.erase(vec.begin()+pos);
            k %= f[i-1];
        }
        return ret;
    }
};