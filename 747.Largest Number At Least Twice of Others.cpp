class Solution {
public:
    int dominantIndex(vector<int>& nums) {
        int a = 0;
        int i = 0;
        int ret;
        int count = 0;
        for (i = 0; i < nums.size(); ++i){
            if(nums[i] > a){
                a = nums[i];
                ret = i;
            }
        }
        
        a = a/2;
        for (int n = 0; n< nums.size();++n){
            if(nums[n] > a)
                ++count;
        }
        if(count == 1)
            return ret;
        else 
            return -1;
        
    }
};


/*
设计思路：
1.循环vector找出最大的元素；
2.最大的元素除以2，再次循环vector进行比较，如果有数字大于它，reture -1;若没有的话返回此数的index;

注意：
1.如果创造的额外空间对于输入的数据量来说是常数，则此算法为原地工作。因此不论在开始申请几个int变量值，对于此题来说都space complexity is always o of 1. It is a constant.
2.if循环不加括号只执行第一个分号前的语句。
3.时间复杂度是O(2n) ==> O(n);两个循环叠加是n+n.
4.在第一次循环的时候，i的值会一直增加直到等于nums.size(),因此需要保存下来i
5.在第二次循环的时候，注意还会遍历到原元素，是现在的二倍，自然会大于它，因此需要计数，只有计数器值为1的时候才返回index.
*/