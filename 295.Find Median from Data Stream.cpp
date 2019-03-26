题意：找到输入的所有数字中的中位数
方法一：vector+排序
TLE，每次都需要排序时间复杂度过高
注意：因为返回值是double因此需要对int转换为double,或者除以2换成乘以0.5
class MedianFinder {
private:
    vector<int> vec;
    //int total = 0;
public:
    /** initialize your data structure here. */
    MedianFinder() {
        
    }
    
    void addNum(int num) {
        vec.push_back(num);
    }
    
    double findMedian() {
        sort(vec.begin(),vec.end());
        if(vec.size() % 2 == 0){
            return (double)(vec[vec.size()/2] + vec[vec.size()/2-1])/2;
        }else{
            return vec[(vec.size()-1)/2];
        }
    }
};

/**
 * Your MedianFinder object will be instantiated and called as such:
 * MedianFinder obj = new MedianFinder();
 * obj.addNum(num);
 * double param_2 = obj.findMedian();
 */
方法2: priority_queue
思路：
1.因为vector的方法在排序方法上耗时过高，因此需要一个数据结构来解决排序的问题，那么priority_queue是合适的
2.为了建立线性的查找，所以建立两个heap,尽量使两个heap中的元素个数相等，如果总数为奇数的话那么在小heap中多放入一个元素
3.中位数是在中间位置的元素，那么small heap中弹出的第一个元素应该是最大的，满足c++中heap的定义
而big heap需要满足弹出的是当前较小的一个，因此可以在push的时候就push进去负数，由大到小弹出那么弹出的就是最大的负数，即较小的正数
4.如果两个数量相等，分别弹出*0.5，如果不等直接返回min heap中的值
5.在push过程中，首先进min heap为了对所有的数字进行排序，再把最大的弹入max heap,如果min heap数量少再把max heap中的元素弹回min heap
注意在较大的栈中不断取反的特点
class MedianFinder {
private:
    priority_queue<int> small, big;
public:
    /** initialize your data structure here. */
    MedianFinder() {
        
    }
    
    void addNum(int num) {
        small.push(num);
        big.push(-small.top());
        small.pop();
        if(small.size() < big.size()){
            small.push(-big.top());
            big.pop();
        }
    }
    
    double findMedian() {
        return small.size() > big.size() ? small.top() : (small.top() - big.top())*0.5;
    }
};

/**
 * Your MedianFinder object will be instantiated and called as such:
 * MedianFinder* obj = new MedianFinder();
 * obj->addNum(num);
 * double param_2 = obj->findMedian();
 */