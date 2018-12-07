思路：
设计一个数据结构能够求出两数之和。
思路：
1.用hashmap来存放数字，遇到一个存入一个
2.循环map，用目标值-循环到的值的方法来查找map中是否存在想找的值。
注意：有两种情况，一种是两个不同的数字相加，那么需要判断循环到的数字和目标值不同
另一种是同一个数字出现两次，那么需要判断循环到的数字和想要找的数字相等，同时map中这一个位置出现了至少2次
class TwoSum {
private:
    unordered_map<int,int>map;
public:
    /** Initialize your data structure here. */
    TwoSum() {
        
    }
    
    /** Add the number to an internal data structure.. */
    void add(int number) {
        ++map[number];
    }
    
    /** Find if there exists any pair of numbers which sum is equal to the value. */
    bool find(int value) {
        for(auto a : map){
            int temp = value - a.first;
            if((map.count(temp) && temp != a.first )|| a.first == temp && a.second >=2) return true;
        }
        return false;
    }
};

/**
 * Your TwoSum object will be instantiated and called as such:
 * TwoSum obj = new TwoSum();
 * obj.add(number);
 * bool param_2 = obj.find(value);
 */