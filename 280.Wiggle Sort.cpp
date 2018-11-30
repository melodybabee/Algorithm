题意：
扭动排序，使得nums[0] <= nums[1] >= nums[2] <= nums[3]...
方法一：排序
T（n） = O(ologn);
思路：
1.通过观察发现，如果把数组排序，2，3交换，4，5交换......以此类推，那么就能满足题目中的条件
class Solution {
public:
    void wiggleSort(vector<int>& nums) {
        sort(nums.begin(),nums.end());
        for(int i = 2; i < nums.size(); i += 2){
            swap(nums[i-1],nums[i]);
        }
    }
};
方法2:遍历
T（n） = O(n);
思路：
1.当i为奇数且比前一小，或者i为偶数比起那一个大的时候，当前位置与前一位交换即可。
2.因为等号的时候成立所以直接交换后即可得到结果。
class Solution {
public:
    void wiggleSort(vector<int>& nums) {
        for(int i = 1; i < nums.size(); ++i){
            if((i % 2 == 0 && nums[i] > nums[i-1]) || (i % 2 ==1 && nums[i] < nums[i-1])){
                swap(nums[i],nums[i-1]);
            }
        }
    }
};
