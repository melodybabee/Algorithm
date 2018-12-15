题意：在数组中找消失的数字
思路：
1.首先循环数组，因为1 ≤ a[i] ≤ n，数组的范围是 [1, n] ，所以每个数字本身应该都能各司其位
2.所以一旦发现不能在对应位置找到该数字的，那么就交换
3.最后从头部开始交换，如果对应位置不是想要的结果，那么push到结果数组中，最后返回
注意：
注意数组下标和对应位置。
class Solution {
public:
    vector<int> findDisappearedNumbers(vector<int>& nums) {
        vector<int>res;
        for(int i = 0; i< nums.size() ;++i){
            if(nums[i] != nums[nums[i]-1]){
            swap(nums[i],nums[nums[i]-1]);
            --i;
            }
        }
        for(int i = 0; i < nums.size();++i){
            if(nums[i] != i+1) res.push_back(i+1);
        }
        return res;
    }
};