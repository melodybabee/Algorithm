permutation 排列
lexicographically 字典顺序
题意：
找到下一位排序，下一位排序是指全排列的下一位。比如[123],全排列有以下结果
[123][132][213][231][312][321]是按照数字大小排序的
那么如果给出一个数字[213],需要返回[231]
思路：
1.通过观察发现，从后往前遍历数组，如果是依次增大的，那么只需要反转即可。
如果不断增大突然遇到了减小一项，那么应该更换这个数字。这个数字需要与在它后面比它大的数字中的最小数更换，即从后向前循环一但发现比它大的数字就更换。这个数字一定存在因为由后向前是依次递增的。
2.更换后在对后面的数字进行反转即可。
注意：
1.本题是套路题，需要理解下数字的位数排列大小导致的数字大小。
2.从后向前数字是依次递增的性质贯穿本题，应该时刻应用这一性质，从而找到次大值。
class Solution {
public:
    void nextPermutation(vector<int>& nums) {
        int j;
        for(int i = nums.size()-2; i >= 0; --i){
            if(nums[i] < nums[i+1]){
                for(j = nums.size()-1; j > i;--j){
                    if(nums[j] > nums[i]){
                        break;
                    }
                }
                swap(nums[j],nums[i]);
                reverse(nums.begin()+i+1, nums.end());
                return;
            } 
        }
        reverse(nums.begin(),nums.end());
    }
};