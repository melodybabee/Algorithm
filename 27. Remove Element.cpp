class Solution {
public:
    int removeElement(vector<int>& nums, int val) {
        int p = 0;
        for (int i = 0; i < nums.size(); ++i)
            if(nums[i] != val){
               nums[p] = nums[i];
               p++;
            }
        
       return p;
        
    }
};
/*
为了保证o(1)的时间复杂度，不允许新建一个space去更新这个array,因此用到指针是最好的方法,缺点在于没法很好的返回新的长度
因此可以重新写vector
解法的要点在于重新设置p,使p为0，这样一旦不等于既定值，就可以把原有的值写入。
相当于i是原vector里的指针循环，p是新vector的指针循环。
如果原有的vector为空，那么直接返回p,不用单独列出这个情况。
*/