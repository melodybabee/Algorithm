题意：
判断数组中两个数字相加的和可以整除60的有多少组。
方法一：暴力拆解双层for循环会TLE
方法二：建立数组 + two sum
思路：
1.遍历每个数字对数字取余，再把他们存在数组中
2.对于每个遍历到的数字，先自身取余，再用60减去这个数字，因为建立了一个大小为60的数组，数字是从0-59，所以需要对相减后的结果再次取余
结果值加上数组中对应位置上的值即可
class Solution {
public:
    int numPairsDivisibleBy60(vector<int>& time) {
        vector<int>vec(60);
        int count = 0;
        for(auto t : time){
            count += vec[(60-t%60)%60];
            ++vec[t%60];
        }
        return count;
    }
};