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
2.求出连续的子数组和sun,想找到和等于k的值，那么可以快速查找map中是否有值等于sum-k,如果存在,那么一定也有和等于k,个数和sum-k的个数相等。
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
