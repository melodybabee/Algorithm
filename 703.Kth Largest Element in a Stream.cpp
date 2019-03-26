题意：找到数据流中第K大的元素
思路：
1.用一个priority_queue来维护一个K大小的queue,因为每次需要返回的是第K大的元素，所以这个heap需要从小到大排列，这样一来每次返回的top()元素才是想要的元素
默认为从大到小，用priority_queue<int,vector<int>,greater<int>>q;改变为从小到大
2.每次不断push进去新的元素，一旦超过k的大小，直接push出去，push出去为返回栈顶元素并删除
3.添加新的元素也是，一旦在指定的大小区间内，直接返回top()
class KthLargest {
private:
    int target;
    priority_queue<int,vector<int>,greater<int>>q;
public:
    KthLargest(int k, vector<int> nums) {
        target = k;
        for(int i = 0;i < nums.size(); ++i){
            q.push(nums[i]);
            if(q.size() > k) q.pop();
        }
    }
    
    int add(int val) {
        q.push(val);
        if(q.size() > target) q.pop();
        return q.top();
    }
};
/**
 * Your KthLargest object will be instantiated and called as such:
 * KthLargest* obj = new KthLargest(k, nums);
 * int param_1 = obj->add(val);
 */