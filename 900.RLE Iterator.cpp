题意：实现run-length encoded RLE的迭代器。每次输出指定的后面第n个元素
思路：
1.因为可以在原数组上直接操作判断，所以没有必要根据原数组再建立一个新的数组，再对新数组进行操作
2.那么把RLEIterator方法中的数组赋值到全局变量中，因为需要一个坐标位置用来记录遍历到数组的哪个位置上了
3.开始从头部判断，如果坐标的位置已经大于数组的长度，说明已经超过数组的范围，那么直接返回-1
否则进入while循环，如果next的值要小于当前的坐标指向的值，那么对应位置减去相应的值，返回下一位上的值
如果next的值要大于当前坐标指向的值，那么对应位置减去相应的值，坐标跳到下一位，再次进入while循环。
class RLEIterator {
private:
    vector<int> temp;
    int index;
public:
    RLEIterator(vector<int> A) {
        temp = A;
        index = 0;
    }
    
    int next(int n) {
        while(index  < temp.size()){
            if(n > temp[index]){
                n -= temp[index];
                index += 2;
            }else{
                temp[index] -= n;
                return temp[index+1];
            }
        }
        
        return -1;
    }
};

/**
 * Your RLEIterator object will be instantiated and called as such:
 * RLEIterator obj = new RLEIterator(A);
 * int param_1 = obj.next(n);
 */