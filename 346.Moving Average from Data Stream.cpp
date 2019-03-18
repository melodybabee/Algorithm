题意：设计计算规定长度的数字的平均值
思路：
1.因为题目中的要求是如果没有达到规定的数量，有几个数字取几个数字的平均值，一旦超过了，那么应该删除之前的数字，只保留规定大小的
2.那么题目中的性质正好满足queue的性质，直接用queue来记录即可
3.注意为了方便计算queue中的所有值，每次都先相加再判断是否大于queue的长度。如果大于再减，同时删除顶部元素。
class MovingAverage {
private:
    queue<int> q;
    int s;
    double total = 0;
public:
    /** Initialize your data structure here. */
    MovingAverage(int size) {
        s = size;
    }
    
    double next(int val) {
        total += val;
        q.push(val);
        if(q.size() > s){
            total -= q.front();
            q.pop();
        }
        return total/q.size();
    }
};

/**
 * Your MovingAverage object will be instantiated and called as such:
 * MovingAverage obj = new MovingAverage(size);
 * double param_1 = obj.next(val);
 */