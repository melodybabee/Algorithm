题意：
280 follow up，扭动排序但是相邻两点不能相等
思路1:先排序再替换
T(n) = O(nlogn),S(n) = O(n);
1.首先把数组排序，定义一个中点指针和一个尾部指针，奇数取中点指针的值，偶数去尾部指针的值，再分别向前移动。
大小能够满足题目的要求。
注意：
因为数组从0开始，而指针是根据长度定义的，所以需要两者都需要-1.
但是中点指针如果-1，那么如果是奇数个长度的数组最后一位会超出范围，因此需要在除以2之前+1
class Solution {
public:
    void wiggleSort(vector<int>& nums) {
        vector<int> temp = nums;
        sort(temp.begin(),temp.end());
        int mid = (nums.size()+1)/2-1;
        int last = nums.size()-1;
        for(int i = 0; i < nums.size(); ++i){
            if(i % 2 == 0) nums[i] = temp[mid], --mid;
            else nums[i] = temp[last], --last;
        }
    }
};
思路2:【待学习】
T(n) = O(n),S(n) = O(1);