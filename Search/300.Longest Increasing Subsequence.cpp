题意：
找到string中的最长递增子序列。
方法1：DP，类似暴力拆解
思路：
1.首先建立一个一维的dp数组，大小等于原数组的个数。从头开始遍历，更新dp数组。
2.在内部循环过程中遍历从头到当前位置的所有数字，如果有比当前位置小的数字，那么对在dp的数组前面的位置上的值+1更新
3.最后返回dp数组中的最大值。
class Solution {
public:
    int lengthOfLIS(vector<int>& nums) {
        vector<int>dp(nums.size(),1);
        int res = 0;
        for(int i = 0; i < nums.size(); ++i){
            for(int j = 0; j < i; ++j){
                if(nums[j] < nums[i])
                    dp[i] = max(dp[i],dp[j] +1);
            }
            res = max(res,dp[i]);
        }
        return res;
    }
};
方法2:二叉搜索更新数组
思路：
1.建立一个数组，放入第一个元素。从头部开始循环元素，如果小于第一个元素，替换，如果大于第一个元素，那么push到后面。
2.如果大于第一个元素小于第二个元素，因为新数组是单增的，可以用二叉搜索的方法。
那么用二叉搜索的方法找到第一个不小于此位置的元素，替换为此元素
3.最后更新之后的数组长度就是单增的最长子序列长度。
class Solution {
public:
    int lengthOfLIS(vector<int>& nums) {
        if(nums.empty()) return 0;
        vector<int> ret{nums[0]};
        for(auto & a : nums){
            if(a < ret[0]) ret[0] = a;
            else if(a > ret.back()) ret.push_back(a);
            else{
                int left = 0;
                int right = ret.size();
                while(left < right){
                    int mid = left + (right - left)/2;
                    if(ret[mid] < a) left = mid+1;
                    else right = mid;
                }
                ret[right] = a;
            }
        }
        return ret.size();
    }
};
方法3:直接二叉搜索
注意：一定注意在二叉搜索的时候搜索的是新建的dp数组，在有序的前提之下才能够进行二叉搜索。
class Solution {
public:
    int lengthOfLIS(vector<int>& nums) {
        vector<int> ret;
        for(int i = 0; i < nums.size(); ++i){
            int left = 0; 
            int right = ret.size();
            while(left < right){
                int mid = left + (right- left)/2;
                if(ret[mid] < nums[i]) left = mid+1;
                else right = mid;
            }
            if(right >= ret.size()) ret.push_back(nums[i]);
            else ret[right] = nums[i];
        }
        return ret.size();
    }
};
方法4:运用c++ STL中的lower_bound函数
思路：
1.lower_bound返回数组中第一个不小于指定值的元素
lower_bound(查找数组.begin(),查找数组.end(),查找元素)；
2.如果没有找到这个元素，表示这个元素目前为最大值，那么直接放在新数组的后面
3.如果找到了替换即可，注意因为查找的过程是应用指针类型，因此替换的时候需要用*取值
class Solution {
public:
    int lengthOfLIS(vector<int>& nums) {
        vector<int>ret;
        for(auto a : nums){
            auto it = lower_bound(ret.begin(),ret.end(),a);
            if(it == ret.end()) ret.push_back(a);
            else *it = a;
        }
        return ret.size();
    }
};
方法5:运用c++ STL中的upper_bound函数
思路：
1.upper_bound是返回数组中第一个大于指定值的元素,因此如果没有大于指定值的元素，直接push到新数组后面即可
如果有，替换即可。
2.进入循环之前需要先判断一下，因为如果是一样大的话就不需要判断，重新进入循环即可。
class Solution {
public:
    int lengthOfLIS(vector<int>& nums) {
        vector<int>ret;
        for(auto a : nums){
            if(find(ret.begin(),ret.end(),a) != ret.end()) continue;
            auto it = upper_bound(ret.begin(),ret.end(),a);
            if(it == ret.end()) ret.push_back(a);
            else *it = a;
        }
        return ret.size();
    }
};

12.10复习：
方法一：DP
每到一个新的数字就开始从0循环，在当前位置更新循环到的位置上的值+1和该位上的较大值，ret结果记录的是每一位上的较大值。
class Solution {
public:
    int lengthOfLIS(vector<int>& nums) {
        int ret = 0;
        vector<int> dp(nums.size(),1);
        for(int i = 0; i < nums.size();++i){
            for(int j = 0; j < i; ++j){
                if(nums[j] < nums[i]){
                    dp[i] = max(dp[i],dp[j] +1);
                }
            }
            ret = max(ret,dp[i]);
        }
        return ret;
    }
};
方法2:二叉搜索
注意：题目中要求的是找到递增的最长序列，不是子序列，所以新建的数组维护的就是单增的趋势。
如果找到更大的元素，那么添加在后面，否则在它合适的位置上替换上该值，最后返回数组的长度。
class Solution {
public:
    int lengthOfLIS(vector<int>& nums) {
        vector<int> ret;
        for(int i = 0; i < nums.size(); ++i){
            int left = 0;
            int right = ret.size();
            while(left < right){
                int mid = left + (right - left)/2;
                if(ret[mid] < nums[i]) left = mid +1;
                else right = mid;
            }
            if(right == ret.size()) ret.push_back(nums[i]);
            else ret[right] = nums[i];
        }
        return ret.size();
    }
};