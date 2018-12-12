题意：
不能用除法，找到数组中除了自己的所有数字乘积。
方法一：左右遍历
T(n) = O(n), S(n) = O(n);
思路：
1.分别用一个左数组一个右数组来记录数组中某一个位置的左边的数值乘积，和右边的数值乘积。
2.最后结果数组是左数组位置*右数组位置的乘积的和。
注意：
1.数组只有声明了size的时候才可以用坐标的位置来更新。
class Solution {
public:
    vector<int> productExceptSelf(vector<int>& nums) {
        vector<int>l(nums.size(),1);
        vector<int>r(nums.size(),1);
        vector<int>ret(nums.size());
        for(int i = 1; i < nums.size();++i){
            l[i] = l[i-1] * nums[i-1];
        }
        for(int i = nums.size()-2; i >= 0; --i){
            r[i] = r[i+1] * nums[i+1];
        }
        for(int i = 0; i < nums.size(); ++i){
            ret[i] = l[i] * r[i];
        }
        return ret;
    }
};

优化：
T(n) = O(n), S(n) = O(1);不算返回结果的数组
思路：
1.先更新左半边的乘积，接着初始化一个值为1的值，用这个值来不断从尾部开始与原数组相乘，实现更新右边乘积的作用。
2.最后在已有的左乘积结果的基础之上乘上中间值的值，作为最终结果。
class Solution {
public:
    vector<int> productExceptSelf(vector<int>& nums) {
        vector<int>ret(nums.size(),1);
        for(int i = 1; i < nums.size();++i){
            ret[i] = ret[i-1] * nums[i-1];
        }
        int temp = 1;
        for(int i = nums.size()-1; i >= 0; --i){
            ret[i] *= temp;
            temp *= nums[i];
        }
        return ret;
    }
};

12.12复习：
注意：先用两个数组分别更新左半边和右半边，在分别乘积更新在数组中。
class Solution {
public:
    vector<int> productExceptSelf(vector<int>& nums) {
        vector<int>left(nums.size(),1);
        vector<int>right(nums.size(),1);
        for(int i = 1 ; i < nums.size(); ++i){
            left[i] = left[i-1] * nums[i-1];
        }
        for(int i = nums.size()-2; i >= 0; --i){
            right[i] = right[i+1] * nums[i+1];
        }
        for(int i = 0 ; i < nums.size();++i){
            nums[i] = left[i] *right[i];
        }
        return nums;
    }
};
优化是首先更新左侧，用一个temp变量1一个一个从右侧开始乘积，每次更新到结果数组中。