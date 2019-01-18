题意：
环状数组找下一位最大，496 follow up
思路：
1.用栈来存放当前的坐标，进入循环之后如果栈不为空且遍历到的新数字要比栈顶坐标表示的数值大，那么在结果数组的对应位置上更新
2。因为数组是可以形成环的，所以i的循环从0开始到2倍的数组长度结束，每次的坐标要对数组的长度取余，超过了长度的部分不再进入栈
如果最后没有满足条件的情况，每次进入循环后会不进行任何操作
class Solution {
public:
    vector<int> nextGreaterElements(vector<int>& nums) {
        if(nums.empty()) return nums;
        vector<int>ans(nums.size(),-1);
        stack<int>st;
        for(int i = 0; i < 2*nums.size(); ++i){
            int num = nums[i%nums.size()];
            while(!st.empty() && num > nums[st.top()]){
                ans[st.top()] = num;
                st.pop();
            }
            if(i < nums.size())st.push(i);
        }
        
        return ans;
    }
};