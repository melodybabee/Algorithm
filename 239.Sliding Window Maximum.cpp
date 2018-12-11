题意：
在窗口内返回最大值。
方法一：priority_queue
T(n) = nlogn;
思路：
1.因为最大堆的性质，每次能返回最大值，那么所有遍历到的点都放入heap中。
注意heap中的类型是pair，第一个元素是值，第二个元素师坐标位置。
2.如果坐标位置小于当前遍历到的位置-k,说明这个最大值已经不在窗口范围内，那么pop
3.如果遍历到的位置坐标大于k-1,即如果超出了第一个窗口的长度，那么每次都需要返回一个值，返回的就是heap顶的最大值。
class Solution {
public:
    vector<int> maxSlidingWindow(vector<int>& nums, int k) {
        priority_queue<pair<int,int>>q;
        vector<int> ret;
        for(int i = 0; i < nums.size();++i){
            while(!q.empty() && q.top().second <= i-k) q.pop();
            q.push(make_pair(nums[i],i));
            if(i >= k-1){
                ret.push_back(q.top().first);
            }
        }
        return ret;
    }
};
方法2:deque,双向队列
T(n) = n;
思路：
1.双向队列的区别在于pop需要区分为pop_front()和pop_back(),push()也要区分前后
2.queue的顶部放的是目前的较大元素，只要遍历到的位置比k-1大，那么每次需要push进去一个新的值。
3.如果不为空且q的头部元素小于i-k,说明窗口已经移动走，那么直接把头部元素弹出。
如果q尾部的元素小于当前值，那么尾部元素跳出，push进去新的值。
注意：
q中存放的是坐标位置，便于比较窗口是否在其范围内以及是否应该在结果中push进去顶部元素。
class Solution {
public:
    vector<int> maxSlidingWindow(vector<int>& nums, int k) {
        vector<int>vec;
        deque<int>q;
        for(int i = 0; i< nums.size();++i){
            if(!q.empty() && q.front() <= i-k) q.pop_front();
            while(!q.empty() && nums[q.back()] < nums[i]) q.pop_back();
            q.push_back(i);
            if(i >= k-1){
                vec.push_back(nums[q.front()]);
            }
        }
        return vec;
    }
};