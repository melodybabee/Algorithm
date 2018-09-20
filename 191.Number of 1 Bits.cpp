class Solution {
public:
    int hammingWeight(uint32_t n) {
        int ret = 0;
        for(int i = 0; i < 32; ++i){
            if((n&1) == 1) ++ret;
            n >>= 1;
        }
        return ret;
    }
};
//O(1), O(1)
/*
思路：
1.循环原数，做位与运算，同时计数，奇数+1，偶数不变
2.原数向右移动一位
*/