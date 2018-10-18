题意：
找到数组中第一个缺失的正数
方法一：暴力拆解
sort(nums.begin(),nums.end());时间复杂度nlogn,for循环为n,因此为n+nlogn,要求复杂度n,所以不行
思路：
1.首先将nums排序，开始进入循环
2.如果数字小于等于0， 向后移动，直到第一位正数
3.设立一个temp变量，从1开始作为判断标记，如果等于temp，那么temp++
4.需要注意会存在重复的数字，因此在每次进入循环的时候都需要判断是否与前一位相等，如果相等，continue;
5.最后return temp
class Solution {
public:
    int firstMissingPositive(vector<int>& nums) {
        int temp = 1;
        sort(nums.begin(),nums.end());
        for(int i = 0; i < nums.size();++i){
            while(nums[i] <= 0){
                ++i;
            }
            if(nums[i] == nums[i-1]){
                continue;
            }
            if(nums[i] == temp){
                ++temp;
            }
            else{
                return temp;
            }
        }
        return temp;
    }
};
方法二：unordered_set
T(n) = O(n), S(n) = O(n);
思路：
1.用一个哈希set存入所有大于0的值，记录下最大的值
2.从1开始循环到最大值，如果set中没有某个值就返回某个址
class Solution {
public:
    int firstMissingPositive(vector<int>& nums) {
        unordered_set<int> set;
        int m = 0;
        for(auto &i : nums){
            if(i <= 0) continue;
            set.insert(i);
            m = max(m,i);
        }
        for(int j = 1; j <= m; ++j){
            if(!set.count(j)) return j;
        }
        return m +1;
    }
};
方法三：数组替换
T(n) = O(n), S(n) = O(1);
思路：
1.我们的目标是把数组的第0位放上1，第1位放上2...再去循环找是否满足这个规律，不满足的少哪位输出哪位
2.因此在第一次遍历的时候，如果小于等于0，不考虑，如果值过大超出了数组的范围，不考虑，如果有重复的值，不考虑
这样找到满足条件的值之后用这个值与它应该所在的值进行交换，更新了数组。
3.再次进入for循环的时候如果不满足当前index+1等于当前位置的值，返回当前位置的值
class Solution {
public:
    int firstMissingPositive(vector<int>& nums) {
        int n = nums.size();
        for(int i = 0; i < nums.size(); ++i){
            while(nums[i] > 0 && nums[i] < n && nums[i] != nums[nums[i]-1]){
                swap(nums[i], nums[nums[i]-1]);
            }
        }
        for(int i = 0; i < n; ++i){
            if(nums[i] != i+1) return i+1;
        }
        return n+1;
    }
};