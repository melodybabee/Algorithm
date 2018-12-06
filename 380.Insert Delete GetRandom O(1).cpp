题意：
设计一个数组结构能够执行插入，删除和获取随机数字的操作。
方法一：set
思路：
1.用set获取随机数组的操作不是线性的，但是为了熟悉一下set的操作。
2.set的特点是有序和去重，key按照递增排序；unordered_set的特点是去重，key是无序的。
3.set中插入操作是insert(),删除操作是erase(),判断set中有没有想找的值可以用count()来查找，也可以用s.find(值)！=s.end(),表示已经查找到。
4.set需要用迭代器来遍历，可以是从set.begin()开始，到不等于s.end()为止
也可以设置一个迭代器，用advance()函数对迭代器进行偏移操作，advance(it,n)表示向后偏移n个位置,n为整数
5.c++中rand()表示随机数发生器，可以产生随机数，本题中需要对产生的随机数取余用来产生移动的位置
6.注意输出迭代器的值的时候需要*it用取值符号。
class RandomizedSet {
private:
    unordered_set<int> set;
public:
    /** Initialize your data structure here. */
    RandomizedSet() {
        
    }
    
    /** Inserts a value to the set. Returns true if the set did not already contain the specified element. */
    bool insert(int val) {
        if(set.count(val)) return false;
        else{
            set.insert(val);
            return true;
        }
    }
    
    /** Removes a value from the set. Returns true if the set contained the specified element. */
    bool remove(int val) {
        if(!set.count(val)) return false;
        else{
            set.erase(val);
            return true;
        }
        
    }
    
    /** Get a random element from the set. */
    int getRandom() {
        auto iter = set.begin();
        advance(iter,rand()%set.size());
        return *iter;
    }
};

/**
 * Your RandomizedSet object will be instantiated and called as such:
 * RandomizedSet obj = new RandomizedSet();
 * bool param_1 = obj.insert(val);
 * bool param_2 = obj.remove(val);
 * int param_3 = obj.getRandom();
 */

方法2:unordered_map
思路：
1.用一个数组记录所有数字,map用来记录值和值在数组中的对应关系
2.insert就分别在数组和map中插入即可
remove需要先在数组中把要删除的位置交换到最后一位上，同时更新map中的对应值，在map中删除，从数组最后pop_back()即可
3.最后输出随机数从数组中找rand()%vec.size()的值就可以
class RandomizedSet {
private:
    unordered_map<int,int>map;
    vector<int>vec;
public:
    /** Initialize your data structure here. */
    RandomizedSet() {
        
    }
    
    /** Inserts a value to the set. Returns true if the set did not already contain the specified element. */
    bool insert(int val) {
        if(map.count(val)) return false;
        vec.push_back(val);
        map[val] = vec.size()-1;
        return true;
    }
    
    /** Removes a value from the set. Returns true if the set contained the specified element. */
    bool remove(int val) {
        if(!map.count(val)) return false;
        int last = vec.back();
        map[last] = map[val];
        vec[map[val]] = last;
        vec.pop_back();
        map.erase(val);
        return true;
    }
    
    /** Get a random element from the set. */
    int getRandom() {
        return vec[rand()%vec.size()];
    }
};

/**
 * Your RandomizedSet object will be instantiated and called as such:
 * RandomizedSet obj = new RandomizedSet();
 * bool param_1 = obj.insert(val);
 * bool param_2 = obj.remove(val);
 * int param_3 = obj.getRandom();
 */