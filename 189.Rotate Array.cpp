创建新的array
class Solution {
public:
    void rotate(vector<int>& nums, int k) {
        if (nums.empty()) return;
        if(k > nums.size()) k = k%nums.size();
        vector<int> ret(nums.size(),0);
        int i = 0;
        int n = nums.size()-k;
        for(n;n < nums.size();++n){
            ret[i] = nums[n];
            ++i;
        }
        n = 0;
        while (n < nums.size()-k){
            ret[i] = nums[n];
            ++n;
            ++i;
        }
        nums = ret;
        return;
    }
};
//T(n) = O(n), S(n) = O(n);
/*
思路：
1.通过观察发现,得到k的值之后，可以得到所要得到的结果的值的第0位，就是原数组的n=nums.size()-k位
2.因此新建一个vector,从头部开始将原数组的位置一一对应即可，循环新的数组
3.当n的值超过原数组的长度之后，置0，原数组的头部开始循环，直到与nums.size()-k相等为止
4.此时返回新的vector，本题void方法默认返回nums的值，可以用新vector对原vector赋值
注意：
1.需要首先判断一下k,如果k很大，用k对数组的长度做取余处理
2.如果原数组本身为空，直接返回
*/
【Using Cyclic Replacements】如果直接在原数组上更新会破坏原array,但可以把要交换的元素保存起来，不需要新建array，改进后的 S(n) = O(1)；

*****************************************
reverse()反转法
class Solution {
public:
    void rotate(vector<int>& nums, int k) {
        int n = nums.size();
        k = k%n;
        reverse(0,n-1,nums);
        reverse(0,k-1,nums);
        reverse(k,n-1,nums);
        return;
    }
    
    void reverse(int begin, int end, vector<int>&nums){
        int i = begin;
        int j = end;
        int temp;
        for(i,j; i< j; ++i, --j){
            temp = nums[i];
            nums[i] = nums[j];
            nums[j] = temp;
        }
        return;
    }
};
//T(n) = O(n), S(n) = O(1);
/*
1.首先将整个vector反转，在分别反转（0，k-1)和（k,nums.size()-1)直接得到结果
*/
