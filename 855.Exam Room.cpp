题意：849follow up,找到现有位置距离最远的空位。
思路：
1.首先设置一个全局变量用来记录每次坐下的位置和原始数组的长度。
2.当数组中没有人坐的时候，表示数组为空，那么直接在数组中插入0元素，返回0
当数组中有人的时候，判断目前为止的最大距离。
先用第一个元素和最大值减去数组中的最后一个元素进行比较，再两两遍历数组中的数字求两个数字之间的距离的较大值。
如果当前的最大距离等于数据中的第一个元素，表示第一个位置为空，那么插入0，返回0
3.如果不等于第一位上的值，开始遍历，判断两两之间的差是否等于这个距离。
如果等于，在当前位置上插入这个元素，同时返回。
4.如果数组的个数只有一个，且最大的距离不等于第一位上的值，那么表示应该在最后一位上坐下，那么就在最后插入元素并返回
5.如果某位上的人走了，那么从头开始遍历，遍历的值等于目标值之后，用erase()方法删除
注意：
在数组中插入或者删除都需要用到迭代器，insert()需要用vec.begin()+X开始在指定位置进行插入，erase()要在指定位置进行删除
class ExamRoom {
private:
    vector<int>vec;
    int n;
public:
    ExamRoom(int N) {
        n = N;
    }
    
    int seat() {
        if(vec.size() == 0){
            vec.push_back(0);
            return 0;
        }
        int d = max(vec[0],n-1-vec[vec.size()-1]);
        for(int i = 0; i +1 < vec.size(); ++i){
            d = max(d,(vec[i+1]-vec[i])/2);
        }
        if(vec[0] == d){
            vec.insert(vec.begin(),0);
            return 0;
        }
        for(int i = 0; i +1 < vec.size(); ++i){
            if((vec[i+1]-vec[i])/2 == d){
                vec.insert(vec.begin()+i+1,(vec[i+1] + vec[i])/2);
                return vec[i+1];
            }
        }
        vec.push_back(n-1);
        return n-1;
    }
    
    void leave(int p) {
        for(int i = 0; i< vec.size(); ++i){
            if(vec[i] == p) vec.erase(vec.begin()+i);
        }
    }
};

/**
 * Your ExamRoom object will be instantiated and called as such:
 * ExamRoom obj = new ExamRoom(N);
 * int param_1 = obj.seat();
 * obj.leave(p);
 */