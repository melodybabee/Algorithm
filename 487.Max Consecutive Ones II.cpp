题意：
485 follow up,可以将一个0替换成1，求出最多的连续1的个数。
思路：
1.因为题目中只能替换一个0，因此需要记录下其前一个0的位置，一旦后面还有0，需要获取前一个0后面一位的坐标开始新的循环。
2.因为可以符合先进先出的性质，因此用到队列，只要队列中的元素个数大于1，那么左边界就是队列中第一个元素+1.
3.在过程中记录下可以得到的最大值。
class Solution {
public:
    int findMaxConsecutiveOnes(vector<int>& nums) {
        queue<int>q;
        int left = 0;
        int ret = 0;
        for(int i = 0; i < nums.size(); ++i){
            if(nums[i] == 0) q.push(i);
            if(q.size() > 1){
                left = q.front()+1;
                 q.pop();
            }
            ret = max(ret,i-left+1);
        }
        return ret;
    }
};