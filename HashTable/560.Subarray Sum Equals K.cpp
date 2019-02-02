题意：
在数组中找到子数组和等于目标值的个数，001two sum follow up。
方法一：设置累加和数组
T（n）= O（n^2）
思路：
1.每次进入第一层循环之前设置一个初始值记录和。
2.再次进入第二层循环，如果和等于目标值，计数器+1
注意：
1.需要判断一个元素是否等于目标值，如果相等，那么计数器也需要+1。
class Solution {
public:
    int subarraySum(vector<int>& nums, int k) {
        int count = 0;
        for(int i = 0; i < nums.size(); ++i){
            int sum = nums[i];
            if(sum == k) ++ count;
            for(int j = i+1; j < nums.size();++j){
                sum += nums[j];
                if(sum == k) ++count;
            }
        }
        return count;
    }
};
方法二：Hashtable
T（n）= O（n）;
思路：
1.首先建立一个hashtable,key放入连续子数组之和，value放入出现的频次。
2.求出连续的子数组和sum,想找到和等于k的值，那么可以快速查找map中是否有值等于sum-k,如果存在,那么一定也有和等于k,个数和sum-k的个数相等。
3.同时把新的子数组的和放入map中
class Solution {
public:
    int subarraySum(vector<int>& nums, int k) {
        unordered_map<int,int>map{{0,1}};
        int ret = 0;
        int sum = 0;
        for(int i = 0 ; i < nums.size(); ++i){
            sum += nums[i];
            ret += map[sum-k];
            ++map[sum];
        }
        return ret;
        
    }
};

12.11复习：
1.暴力拆解：
注意：
1.需要加上元素本身计数
class Solution {
public:
    int subarraySum(vector<int>& nums, int k) {
        int count = 0;
        for(int i = 0; i < nums.size(); ++i){
            int temp = nums[i];
            if(temp == k) ++ count;
            for(int j = i+1; j < nums.size(); ++j){
                temp += nums[j];
                if(temp == k) ++count;
            }
        }
        return count;
    }
};
2.hashmap
注意：
1.sum保证了数组是连续的，因为是逐个累加的
2.要在map中首先声明初始量{0,1};
class Solution {
public:
    int subarraySum(vector<int>& nums, int k) {
        unordered_map<int,int>map {{0,1}};
        int ret = 0; 
        int sum = 0;
        for(int i= 0; i < nums.size();++i){
            sum += nums[i];
            ret += map[sum-k];
            ++map[sum];
        }
        return ret;
    }
};
如果数组中都是正数还可以用two pointers,有负数存在就不行:
class Solution {
public:
    int subarraySum(vector<int>& nums, int k) {
        int ret = 0; 
        int sum = 0;
        int j = 0;
        for(int i= 0; i < nums.size();++i){
            sum += nums[i];
            while(sum > k){
                sum -= nums[j];
                ++j;
            }
            if(sum == k) ++ ret;
        }
        return ret;
    }
};

2.1复习：
注意：
two pointers的方法虽然快，但是如果有0或者负数的话就不能用，因为有可能会有和0的情况，那么两个指针重合的时候一定等于0，所以不能得到结果。
而且如果让左指针小于右指针的话，那么比如[-1,-1,0]和为1的时候，右指针遍历过程中加的结果始终不会大于k,那么就不能找到[-1,0]的情况
但是如果都是正数，那么和不可能是0，因此可以直接two pointers比较
class Solution {
public:
    int subarraySum(vector<int>& nums, int k) {
        int left = 0;
        int count = 0;
        int sum = 0;
        for(int r = 0; r < nums.size(); ++r){
            sum += nums[r];
            while(sum > k){
                sum -= nums[left];
                ++left;
            }
            if(sum == k) ++count;
        }
        return count;
    }
};
所以需要用到一个hashtable,用来记录数组的前缀和。如果在map中有子数组等于sum-k,那么也一定有和等于k，那么直接相加即可。
注意因为有sum==k的情况，所以在map中需要插入{0,1}这个key-value,最后返回计数器的数量
前缀和保证了数组一定是连续的。
class Solution {
public:
    int subarraySum(vector<int>& nums, int k) {
        unordered_map<int,int>map{{0,1}};
        int count = 0;
        int sum = 0;
        for(int r = 0; r < nums.size(); ++r){
            sum += nums[r];
            count += map[sum-k];
            ++map[sum];
        }
        return count;
    }
};
