题意：
设计一个迭代器曲形输出两个数组中的元素。
思路：
1.建立一个全局变量的数组和一个全局变量的坐标，初始化的时候曲形输入，并把剩余部分的数组值加在末尾。
注意不同于链表，加末尾值的时候需要用while循环。
2.++i先相加再赋值，i++先赋值再相加
注意：
需要判断两个数组中都不存在或者其中某一个不存在的情况。
class ZigzagIterator {
private:
    vector<int> ret;
    int index = 0;
public:
    ZigzagIterator(vector<int>& v1, vector<int>& v2) {
        if(v1.empty() && v2.empty()) ret = {};
        if(v1.empty() || v2.empty()) ret = v1.empty() ? v2 : v1;
        else{
            int size = min(v1.size()-1,v2.size()-1);
            int i = 0;
            for(i; i <= size;++i){
                ret.push_back(v1[i]);
                ret.push_back(v2[i]);
            }
            while(i <= v2.size()-1){
                ret.push_back(v2[i]);
                ++i;
            }
            while(i <= v1.size()-1){
                ret.push_back(v1[i]);
                ++i;
            }
        }
    }

    int next() {
        return ret[index++];
    }

    bool hasNext() {
        if(index < ret.size()) {
            return true;
        }else return false;
    }
};

/**
 * Your ZigzagIterator object will be instantiated and called as such:
 * ZigzagIterator i(v1, v2);
 * while (i.hasNext()) cout << i.next();
 */

follow up：
如果是多个数组如何处理？
思路：
1.用自定义迭代器处理，设置一个queue满足先进先出的原则，里面放自定义的pair迭代器
2.在初始化方法中，pair中用来存放数组的头部迭代器和尾部迭代器。注意形成pair使用make_pair()方法
3.在输出下一个元素的方法中，分别获取栈头部pair的第一个位置和第二个位置的元素，注意end是在数组结束后的下一位，因此如果头部迭代器+1不等于尾部迭代器，说明没有到结尾，那么把剩下的部分重新入栈，输出头部迭代器指向的位置。
注意迭代器也是指针类型的一种，因此如果想要获取值需要*it，用取值符号。
class ZigzagIterator {
private:
    queue<pair<vector<int>::iterator,vector<int>::iterator>>q;
public:
    ZigzagIterator(vector<int>& v1, vector<int>& v2) {
        if(!v1.empty())q.push(make_pair(v1.begin(),v1.end()));
        if(!v2.empty())q.push(make_pair(v2.begin(),v2.end()));
    }

    int next() {
        auto it = q.front().first;
        auto last = q.front().second;
        q.pop();
        if(it+1 != last) q.push(make_pair(it+1,last));
        return *it;
        
    }

    bool hasNext() {
        return !q.empty();
    }
};

/**
 * Your ZigzagIterator object will be instantiated and called as such:
 * ZigzagIterator i(v1, v2);
 * while (i.hasNext()) cout << i.next();
 */
