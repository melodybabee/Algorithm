题意：找到数组中不重叠的3个子数组的最大和，返回坐标值。
思路：
1.题目中说明了一共是找3个数组，所以可以分成左中右三个数组。中间数组的位置最少要左右空出来k个位置。
2.建立两个dp数组分别叫left和right，left[i]表示在[0,i]范围内和为最大的子数组的起始位置。
right[i]表示在[i,结尾]范围内和为最大的子数组的起始位置。
3.建立一个数组，每一位更新成到该位之前数组的和。
4.从左侧更新left dp数组，如果遇到更大的进行更新，没有就等于之前的值。
右侧不断向左更新，如果遇到更大的更新，没有就等于之后的值。
5.开始循环中间数组，从中间数组坐标的最左循环到最右，每次的总和等于左边的DP数组中的和加上中间数组的和加上右边数组的和。
每次取较大值，一旦有较大值就更新坐标在返回数组中，最后返回坐标数组。
class Solution {
public:
    vector<int> maxSumOfThreeSubarrays(vector<int>& nums, int k) {
        int n = nums.size();
        int mx= INT_MIN;
        vector<int>ret;
        vector<int>left(n,0);
        vector<int>right(n,n-k);
        vector<int>sum{0};
        for(auto n :nums) sum.push_back(sum.back()+n);
        for(int i = k, total = sum[k] - sum[0];i < n ; ++i){
            if(sum[i+1]-sum[i+1-k] > total){
                left[i] = i+1-k;
                total = sum[i+1]-sum[i+1-k];
            }else{
                left[i] = left[i-1];
            }
        }
        
        for(int i = n-1-k, total = sum[n]-sum[n-k]; i>= 0;--i){
            if(sum[i+k]-sum[i] > total){
                right[i] = i;
                total = sum[i+k]-sum[i];
            }else{
                right[i] = right[i+1];
            }
        }
        
        for(int i = k ; i <= n - 2*k;++i){
            int l =left[i-1];
            int r = right[i+k];
            int total = sum[i+k]-sum[i]+sum[l+k]-sum[l]+sum[r+k]-sum[r];
            if(mx < total){
                mx = total;
                ret= {l,i,r};
            }
        }
        return ret;
    }
};