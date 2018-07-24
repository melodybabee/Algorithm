class Solution {
public:
    int removeDuplicates(vector<int>& nums) {
        if(nums.size()== 0) return 0;
        int p = 1;
        for (int i = 1; i < nums.size();++i)
            if (nums[i] != nums[i-1]){
                nums[p] = nums[i];
                ++p;
            }
        return p;
    }
};

/*
总结：
1.for循环从i=1的时候开始，判断nums[i]与nums[i-1],这样i就会到原vector的最后一位，不会出现少加上最后一位的情况
【重点】2.新的vector也从p=1的时候开始，不论第一位与第零位是否相等，原vector中的第零位都可以保留
3.用指针i循环原vector,循环至最后一位，并依次添加;用指针p代表新vector中的元素，逐次添加。
*/
