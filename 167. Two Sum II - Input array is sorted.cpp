class Solution {
public:
    vector<int> twoSum(vector<int>& numbers, int target) {
        vector<int> ret;
        int i = 0;
        int j = numbers.size()-1;
        
        while(numbers[i]+numbers[j]!= target){
        if(numbers[i] + numbers[j] > target)
            --j;
        if (numbers[i] + numbers[j] < target)
            ++i;
        }
        
        ret.push_back(i+1);
        ret.push_back(j+1);
        
        return ret;
    }
};

/*
本题是001的变形，001:https://leetcode.com/problems/two-sum/description/
设计思路：
1.在第一题的基础之上补充了vector由小到大顺序排列的条件，因此需要用到这个条件作出优化，像001一样用i,j循环两次vector的思路会time limit exceed
2.因此在vector的首尾建立两个指针，i，j
【重要】3.如果i+j > target,将较大的j减小；如果i+j < target,将较小的i增大

注意：
1.最后输出的是index,因此需要加1
*/