/*
设计思路：
1.遍历vector, 不是0的数字就放到vector的前面，等到所有不是0的数字都移动到前面之后，在末尾补0；

注意：
1.请你区分while和if！！！
2.void方法不带返回值，直接return即可，隐形的return发生在最后一个函数结束以后，返回类型是void的函数使用return语句是为了引起函数的强制结束
3.注意每道题目想清思路再写代码，理不清楚思路不要写代码。
写完之后自己进行测试，把bug的原因和位置找出来，试图更正，必须要有思考的过程！！！
如果完全没有思路或者思考后仍WA再看搜索别人的答案。
*/
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

12.10复习
注意：不是0就与前面的0进行交换，j记录的是0的位置。
class Solution {
public:
    void moveZeroes(vector<int>& nums) {
        int j = 0;
        for(int i = 0; i < nums.size();++i){
            if(nums[i] != 0){
                swap(nums[i],nums[j]);
                ++j;
            }
        }
    }
};
