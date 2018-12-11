题意：
合并两个array中相同的部分为一个vector
思路：
1.先将两个vector排序，这样方便排除重复的元素
2.再用两个for循环查找，外层循环如果重复就跳过，内层循环如果找到了就break避免重复
class Solution {
public:
    vector<int> intersection(vector<int>& nums1, vector<int>& nums2) {
        vector<int> ret;
        if(nums1.empty() || nums2.empty()) return ret;
        sort(nums1.begin(),nums1.end());
        sort(nums2.begin(),nums2.end());
        int p = 0;
        for(int j = 0; j < nums1.size(); ++j){
            if(j > 0 && nums1[j] == nums1[j-1]) continue;
                for (int i = 0; i < nums2.size(); ++i){
                    if(nums2[i]  == nums1[j]){
                        ret.push_back(nums2[i]);
                        break;
                    }
                }
        }
        return ret;
    }
};
复习2.0
注意本题的核心是找到两个数组中相同的元素，不是找重复的数组，所以找到了直接push到新数组中即可。
class Solution {
public:
    vector<int> intersection(vector<int>& nums1, vector<int>& nums2) {
        vector<int> ret;
        if(nums1.empty() || nums2.empty()) return ret;
        sort(nums1.begin(),nums1.end());
        sort(nums2.begin(),nums2.end());
        for(int i = 0; i < nums1.size(); ++i){
            if(i>0 &&nums1[i] == nums1[i-1]) continue;
            for(int j = 0; j < nums2.size();++j){
                if(nums2[j] == nums1[i]) {
                    ret.push_back(nums2[j]);
                    break;
                }
            }
        }
        return ret;
    }
};
优化1:
因为上面写的代码中已经对数组进行排序，所以就不需要用for循环进行双重循环，用两个指针来比较数组即可。
class Solution {
public:
    vector<int> intersection(vector<int>& nums1, vector<int>& nums2) {
        vector<int> ret;
        sort(nums1.begin(),nums1.end());
        sort(nums2.begin(),nums2.end());
        int i = 0, j = 0;
        while(i < nums1.size() && j < nums2.size()){
            if(nums1[i] < nums2[j]) ++i;
            else if(nums1[i] > nums2[j]) ++j;
            else{
                if(ret.empty() || ret.back() != nums1[i]) ret.push_back(nums[1]);
                ++i;
                ++j;
            }
        }
        return ret;
    }
};
优化2:利用unordered_set
思路：
1.用一个set来存储第一个数组中存在的数字，遍历第一个数组，如果在set中存在，那么insert到新的set中
2.最后把set类型转换为vector即可
vector<int>(ret.begin(),ret,end())；
class Solution {
public:
    vector<int> intersection(vector<int>& nums1, vector<int>& nums2) {
        set<int> set(num1.begin(),num1.end());
        set<int> ret;
        for(auto &a : nums2){
            if(set.count(a)) ret.insert(a);
        }
        return vector<int>(ret.begin(),ret,end());
    }
};

12.11复习：
1.unordered_map
先把一个输入到map中另一个在里面查找，找到了删除避免有重复的元素
class Solution{
public:
    vector<int> intersection(vector<int>& nums1, vector<int>& nums2) {
        unordered_map<int,int>map;
        vector<int>vec;
        for(auto a:nums1) ++map[a];
        for(int i = 0;i < nums2.size();++i){
            if(map.count(nums2[i])){
                vec.push_back(nums2[i]);
                map.erase(nums2[i]);
            }
        }
        return vec;
    }
};
2.unorded_set
思路：
1.利用set去重的特质 因此返回的数组也应该是set类型
2.最后转换为vector
class Solution {
public:
    vector<int> intersection(vector<int>& nums1, vector<int>& nums2) {
        unordered_set<int>set(nums1.begin(),nums1.end());
        unordered_set<int>ret;
        for(auto a : nums2){
            if(set.count(a)) ret.insert(a);
        }
        return vector<int>(ret.begin(),ret.end());
    }
};
follow up：
1.双指针方法是分别先对数组进行排序，再开始从头部依次遍历，相等，放到结果中，不想等那么小的一方前进。
2.如果是[1,2,3,...10000]和[1,3,4...10000]双指针遍历是o(n),更快的方法是先双指针查找，如果一定程度上找不到之后那么直接二叉搜索。
