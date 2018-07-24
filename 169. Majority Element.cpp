class Solution {
public:
    int majorityElement(vector<int>& nums) {
       
        for (int i = 0; i < nums.size();++i){
            int ret = 0;
            for (int j = 0; j < nums.size();++j){
                if(nums[i]==nums[j]) ++ret;
                }
        
            if(ret > (nums.size()/2)){
                return nums[i];
                }
            }
        return -1;
    }
};
/*
设计思路：
1.设置一个指针在vector头部，循环整个vector,相同的加一
2.移动指针到与第一个数字值不同的位置，相加
3.把所有数字的频数存在一个数组里，比较最大值，输出

注意：
1.本题要求输出的是值，而不是频次，因为思路输出部分的思路不对
2.可以在for循环里++ret的时候，只要ret大于数组大小的一半，即可输出
3.当输入的数值过多时，解法不可通过，因此需要优化
*/