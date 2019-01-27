题意：根据时间戳找到相对应的数值
方法一：unordered_map
思路：
1.在哈希表中key表示需要查找的字符串,为string类型。value值为另一个哈希表，key是需要查找的时间戳，value是string
2.在哈希表中的哈希表里面插入新的值
3.获取的时候判断是否有第一个key，没有返回空
如果正好能找到，直接返回，不能的话将时间戳依次向前移动到大于0的位置以后判断能否找到。不能的话返回空
class TimeMap {
private:
    unordered_map<string,unordered_map<int,string>>map;
public:
    /** Initialize your data structure here. */
    TimeMap() {
        
    }
    
    void set(string key, string value, int timestamp) {
        map[key][timestamp] = value;
    }
    
    string get(string key, int timestamp) {
        if(!map.count(key)) return "";
        if(map[key].count(timestamp)) return map[key][timestamp];
        else{
            --timestamp;
            while(timestamp > 0){
                if(map[key].count(timestamp)) return map[key][timestamp];
                --timestamp;
            }
            return "";
        }
    }
};

/**
 * Your TimeMap object will be instantiated and called as such:
 * TimeMap* obj = new TimeMap();
 * obj->set(key,value,timestamp);
 * string param_2 = obj->get(key,timestamp);
 */
优化：
1.用upper_bound()来找出比时间戳大一位的指针位置，如果等于begin返回空，否则返回其前一位即可
2.只有treemap才有upper_bound(),hashmap没有
3.只要用到了upper_bound()那么表示的位置就是指针类型，取值就要用->,同时（--it）指针类型也可以表示为prev(it)
class TimeMap {
private:
    unordered_map<string,map<int,string>>m;
public:
    /** Initialize your data structure here. */
    TimeMap() {
        
    }
    
    void set(string key, string value, int timestamp) {
        m[key][timestamp] = value;
    }
    
    string get(string key, int timestamp) {
        auto it = m[key].upper_bound(timestamp);
        return it == m[key].begin() ? "" : (--it)->second;
    }
};

/**
 * Your TimeMap object will be instantiated and called as such:
 * TimeMap* obj = new TimeMap();
 * obj->set(key,value,timestamp);
 * string param_2 = obj->get(key,timestamp);
 */
 最后一行也可以写成
 class TimeMap {
private:
    unordered_map<string,map<int,string>>m;
public:
    /** Initialize your data structure here. */
    TimeMap() {
        
    }
    
    void set(string key, string value, int timestamp) {
        m[key][timestamp] = value;
    }
    
    string get(string key, int timestamp) {
        auto it = m[key].upper_bound(timestamp);
        return it == m[key].begin() ? "" : prev(it)->second;
    }
};

/**
 * Your TimeMap object will be instantiated and called as such:
 * TimeMap* obj = new TimeMap();
 * obj->set(key,value,timestamp);
 * string param_2 = obj->get(key,timestamp);
 */