题意：给定一个target值，求出数组中最接近target值的三个值的和
方法一：暴力拆解，时间复杂度极高
思路：
1.暴力三层for循环，temp用于存储每个子数组的和与target值的差的最小值
2.当新的循环计算出比temp还小的值的时候，进入for循环用ret记录下此时的sum
3.返回ret值
4.注意temp如果在最开始想要初始值为最大，可以写作INT_MAX
class Solution {
public:
    int threeSumClosest(vector<int>& nums, int target) {
        int sum;
        int ret;
        int temp = INT_MAX;
        for(int i = 0; i < nums.size()-2; ++i){
            for(int j = i+1; j < nums.size()-1; ++j){
                for(int l = j+1; l < nums.size(); ++l){
                    sum = nums[i] + nums[j] + nums[l];
                    if(abs(sum - target) < temp){
                        ret = sum;
                    }
                    temp = min(temp,abs(sum-target));
                }
            }
        }
        return ret;
    } 
};

优化：先排序在双指针查找 T（O） = n * nlog(n);
思路：
1.和3sum类似，先排序，固定头结点，用双指针找头结点后面的元素，再把双指针逐渐向内侧移动
class Solution {
public:
    int threeSumClosest(vector<int>& nums, int target) {
        int closest = nums[0] + nums[1] + nums[2];
        int diff = abs(closest-target);
        sort(nums.begin(),nums.end());
        for(int i = 0; i < nums.size()-2; ++i){
            int fir = i+1;
            int last = nums.size()-1;
            while(fir < last){
                int sum = nums[i] + nums[fir] + nums[last];
                int newdiff = abs(sum - target);
                if(newdiff < diff){
                    diff = newdiff;
                    closest  = sum;
                }
                if(sum < target){
                    ++fir;
                }else{
                    --last;
                }
            }
        }
        return closest;
    }
};