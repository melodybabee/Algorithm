题意：
找到两个数组中相同的所有元素，在349的基础之上可以有重复
方法1:sort()+while循环
思路：
1.分别对两个数组排序，利用排序好由小到大的性质，分别用两个指针对数组进行while循环
2.循环过程中哪个小移动哪个，直到相等，push到新的数组中，再分别向前移动
class Solution {
public:
    vector<int> intersect(vector<int>& nums1, vector<int>& nums2) {
        vector<int> ret;
        sort(nums1.begin(),nums1.end());
        sort(nums2.begin(),nums2.end());
        int i = 0, j = 0;
        while(i < nums1.size() && j < nums2.size()){
            if(nums1[i] < nums2[j]) ++i;
            else if(nums1[i] > nums2[j]) ++j;
            else{
                ret.push_back(nums1[i]);
                ++i;
                ++j;
            }
        }
        return ret;
    }
};
方法2:unorderd_map
思路：
1.把第一个数组中的所有数字存在一个map中，那么map的key就是数字，value是这个数字的个数
2.再循环第二个数组，如果有这个数字,push进去，在map的相应位置减1
3.注意不能用set,因为无法同时记录数字和数字的个数
class Solution {
public:
    vector<int> intersect(vector<int>& nums1, vector<int>& nums2) {
        unordered_map<int,int>map;
        vector<int> ret;
        for(auto &i : nums1) ++map[i];
        for(int i = 0; i < nums2.size();++i){
            if(map[nums2[i]] > 0){
                ret.push_back(nums2[i]);
                --map[nums2[i]];
            }
        }
        return ret;
    }
};
题目里面的follow up:
1.What if the given array is already sorted? How would you optimize your algorithm?
如果数组是排序好的，直接用while循环进行逐个比较即可。
2.What if nums1's size is small compared to nums2's size? Which algorithm is better?
如果nums1相对于nums2非常小，那么把nums1做成hashtable,因为这样hashtable所占空间更小。
如果悬殊很大，可以在长的字符串中对短的字符串进行二叉搜索。
3.What if elements of nums2 are stored on disk, and the memory is limited such that you cannot load all elements into the memory at once?
如果只有nums2不能放在内存中，则将nums1做成哈希表，nums2分批加载到内存中处理。
如果nums1和nums2都很大，都不适合储存在内存，那么就用外部排序分别来sort它们。将每2G(举例)读入内存，使用2指针技术，然后从内存中读取更多的2G。重复此操作，直到没有更多数据从磁盘读取。

12.11复习：
1.hashmap
Time: O(m + n) Space: O(m + n)
class Solution {
public:
    vector<int> intersect(vector<int>& nums1, vector<int>& nums2) {
        unordered_map<int,int>map;
        vector<int>vec;
        for(auto a : nums1) ++map[a];
        for(int i = 0; i< nums2.size();++i){
            if(map[nums2[i]] > 0) {
                vec.push_back(nums2[i]);
                --map[nums2[i]];
            }
        }
        return vec;
    }
};
2.hashmap优化
判断在map中是否存在那么可以不用每次都输入一个新的键值对
Time: O(m + n) Space: O(m)
class Solution {
public:
    vector<int> intersect(vector<int>& nums1, vector<int>& nums2) {
        unordered_map<int,int>map;
        vector<int>vec;
        for(auto a : nums1) ++map[a];
        for(int i = 0; i< nums2.size();++i){
            if(map.find(nums2[i]) != map.end() && map[nums2[i]] > 0) {
                vec.push_back(nums2[i]);
                --map[nums2[i]];
            }
        }
        return vec;
    }
};
3.sort+two pointers
Time: O(max(m, n) log(max(m, n))) Space: O(m + n)
class Solution {
public:
    vector<int> intersect(vector<int>& nums1, vector<int>& nums2) {
        sort(nums1.begin(),nums1.end());
        sort(nums2.begin(),nums2.end());
        int m = nums1.size();
        int n = nums2.size();
        int i = 0;
        int j = 0;
        vector<int>vec;
        while(i < m && j < n){
            if(nums1[i] == nums2[j]){
                vec.push_back(nums1[i]);
                ++i;
                ++j;
            }else if(nums1[i] > nums2[j]){
                ++j;
            }else{
                ++i;
            }
        }
        return vec;
    }
};