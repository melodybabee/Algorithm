class Solution {
public:
    void moveZeroes(vector<int>& nums) {
        int ans = 0;
        for(int i = 0; i < nums.size(); ++i){
            if(nums[i]!= 0){
                nums[ans] = nums[i];
                ans++;
            }
        }
        while(ans < nums.size()){
            nums[ans]= 0;
            ans++;
        }
        return;
    }
};
/*
设计思路：
1.遍历vector, 不是0的数字就放到vector的前面，等到所有不是0的数字都移动到前面之后，在末尾补0；

注意：
1.请你区分while和if！！！
2.void方法不带返回值，直接return即可，隐形的return发生在最后一个函数结束以后，返回类型是void的函数使用return语句是为了引起函数的强制结束
*/