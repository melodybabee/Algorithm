题意：判断能否把数组划分为若干组，每组的数字是相同的
思路：
1.首先遍历数组，用一个map来记录下每个数字出现的次数
2.遍历map,判断当前数字和value值的最大公约数
3.最后返回最大公约数是否大于1
注意：
1.c++中__gcd()用来直接求最大公约数
可以写成
 int gcd(int dx,int dy){
     return dy == 0 ? dx : gcd(dy,dx%dy);
 }
是有0的时候才返回的，因此初始值需要设置为0.
class Solution {
public:
    bool hasGroupsSizeX(vector<int>& deck) {
        unordered_map<int,int>map;
        int res = 0;
        for(auto d: deck) ++map[d];
        for(auto m : map) res = __gcd(res,m.second);
        return res > 1;
    }
};