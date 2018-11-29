题意：
找到字符串中前K个高频数字的值。
方法一：HashTable + heap 
思路：
1.首先用一个哈希表记录下字符串中的数字的频数。
2.将频数key-value作为一对pair输入到priority_queue中，c++默认的为最大堆
3.注意C++中的最大堆如果是pair类型的数组是以key值来进行排列的，因此本题中对频数进行排序就需要push到优先队列的时候先value再key值。
4.最后输出前k个pair中的第一个值，即map中的key的值，输出到数组中。
class Solution {
public:
    vector<int> topKFrequent(vector<int>& nums, int k) {
        unordered_map<int,int>map;
        vector<int> vec;
        priority_queue<pair<int,int>>q;
        for(auto num : nums){
            ++map[num];
        }
        for(auto it:map){
            q.push({it.second,it.first});
        }
        for(int i = 0; i < k;++i){
            vec.push_back(q.top().second);
            q.pop();
        }
        return vec;
    }
};
补充：
优先队列：priority queue
1.堆排序使用一个最大堆来按照映射次数从大到小排列，在C++中使用priority_queue来实现，默认是最大堆
2.heap对于map/unordered_map的排序（大小排序方式）是根据key值来排序的
3.q.push():新添加一个元素在末尾，然后重新调整堆序。也就是把元素添加在底层vector的end()处。
内部执行一个siftup()函数，上溯函数来重新调整堆序
4.q.pop():把堆顶元素取出来，放到了数组或者是vector的末尾，用原来末尾元素去替代
执行siftdown()下溯函数来重新调整堆序
5.q.back():执行pop()之后最大的元素并没有被取走，而是放于底层容器的末尾。如果要取走，则可以使用底部容器

方法二：bucket sort
思路：
1.首先用哈希表记录下每个数字的频率，创建一个字符串大小的桶排序
2.把map中的频率作为桶数组中的坐标，key作为数组中的值。
3.这样从后往前遍历桶数组，只要坐标中有值就push到新的数组汇总，如果数组的大小等于k,那么返回
注意：
因为有可能不同数字有相同过的频率，因此bucket数组中也需要是vector的形式，用来存放相同频率的所有数组，在输出的时候逐个输出
由于map输出到bucket中的顺序是不确定的，因此push到bucket数组中也是不确定的，但是题目中说了k的值往往是有效的，因此不会存在相同频率的数字有的输出有的没有输出的情况。
class Solution {
public:
    vector<int> topKFrequent(vector<int>& nums, int k) {
        unordered_map<int,int>map;
        vector<int> ret;
        vector<vector<int>> bucket(nums.size()+1);
        for(auto num : nums) ++map[num];
        for(auto it : map){
           bucket[it.second].push_back(it.first);
        }
        for(int i = bucket.size()-1; i>=0; --i){
            for(int j = 0; j< bucket[i].size();++j){
                ret.push_back(bucket[i][j]);
                if(ret.size() == k) return ret;
            }
        }
    }
};
