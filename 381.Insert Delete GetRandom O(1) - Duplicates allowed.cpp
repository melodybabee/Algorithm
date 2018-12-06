题意：
380 follow up,在380的基础之上有重复元素。
方法一：优先队列，但是时间复杂度不是线性的
思路：
1.本题与380的区别就在于会有多个重复元素，所以不能用值和它在数组中的位置一一对应了，需要记录下来所有该元素所在的位置。
所以用一个优先队列来储存值所有出现过的位置，同时判断insert方法返回true还是false在于判断优先队列的长度是否为1。
2.删除的时候仍然需要用需要删除的值和数组尾部的值进行交换。
注意先删除的一定是在数组中靠后位置的值，优先队列保证了这一点。
注意还需要更新尾部元素中在map里面对应的位置，把原先的尾部位置pop出来,push进去新的坐标值。
注意：
在remove的时候不能用在map中存在是否存在来判断，因为有可能元素存在但是不存在优先队列，因此需要根据优先队列是否为空来判断。
class RandomizedCollection {
private:
    unordered_map<int,priority_queue<int>>map;
    vector<int>vec;
public:
    /** Initialize your data structure here. */
    RandomizedCollection() {
        
    }
    
    /** Inserts a value to the collection. Returns true if the collection did not already contain the specified element. */
    bool insert(int val) {
        map[val].push(vec.size());
        vec.push_back(val);
        return map[val].size()==1;
    }
    
    /** Removes a value from the collection. Returns true if the collection contained the specified element. */
    bool remove(int val) {
        if(map[val].empty()) return false;
        int index = map[val].top();
        map[val].pop();
        if(index != vec.size()-1){
            int temp = vec.back();
            vec[index] = temp;
            map[temp].pop();
            map[temp].push(index);
        }
        vec.pop_back();
        return true;
    }
    
    /** Get a random element from the collection. */
    int getRandom() {
        return vec[rand()%vec.size()];
    }
};

/**
 * Your RandomizedCollection object will be instantiated and called as such:
 * RandomizedCollection obj = new RandomizedCollection();
 * bool param_1 = obj.insert(val);
 * bool param_2 = obj.remove(val);
 * int param_3 = obj.getRandom();
 */
方法2:unordered_set
unordered_set去重不排序，remove也是随机取出一个地址进行删除。
class RandomizedCollection {
private:
    unordered_map<int,unordered_set<int>>map;
    vector<int>vec;
public:
    /** Initialize your data structure here. */
    RandomizedCollection() {
        
    }
    
    /** Inserts a value to the collection. Returns true if the collection did not already contain the specified element. */
    bool insert(int val) {
        map[val].insert(vec.size());
        vec.push_back(val);
        return map[val].size()==1;
    }
    
    /** Removes a value from the collection. Returns true if the collection contained the specified element. */
    bool remove(int val) {
        if(map[val].empty()) return false;
        int index = *map[val].begin();
        map[val].erase(index);
        if(index != vec.size()-1){
            int temp = vec.back();
            vec[index] = temp;
            map[temp].erase(vec.size()-1);
            map[temp].insert(index);
        }
        vec.pop_back();
        return true;
    }
    
    /** Get a random element from the collection. */
    int getRandom() {
        return vec[rand()%vec.size()];
    }
};

/**
 * Your RandomizedCollection object will be instantiated and called as such:
 * RandomizedCollection obj = new RandomizedCollection();
 * bool param_1 = obj.insert(val);
 * bool param_2 = obj.remove(val);
 * int param_3 = obj.getRandom();
 */