题意：
在一个数组中分别有一个重复数字和缺失数字，分别找到他们。
方法一：数组对应位置取负数判断
思路：
1.循环数组，在其对应位置的数字置为负，如果循环到某位数字时已经为负数，说明之前循环过，那么这个数字就是重复的。
2.再次循环数组，循环到的正数就是缺失的数字。
注意；
1.因为在第一次循环的时候更新数组为负数，所以后面的判断都需要取绝对值才表示数组的位置。
class Solution {
public:
    vector<int> findErrorNums(vector<int>& nums) {
        vector<int> vec(2,-1);
        for(auto num :nums){
            if(nums[abs(num)-1]< 0) vec[0] = abs(num);
            else nums[abs(num)-1] = - nums[abs(num)-1];
        }z
        for(int i = 0; i < nums.size(); ++i){
            if(nums[i] > 0)
            vec[1] = i+1;
        }
        return vec;
    }
};
方法二：Hashtable计数
思路：
1.循环数组，把所有出现的数字进行计数，存到一个新的数组中,用数组模拟hashtable。
2.遍历循环数组，如果为0，即缺失；如果为2，即重复。
注意：
声明的计数数组的大小要等于原数组，因为nums.size()表示了个数，而不是坐标。
class Solution {
public:
    vector<int> findErrorNums(vector<int>& nums) {
        vector<int>count(nums.size(),0);
        vector<int>ret(2,0);
        for(auto &a : nums) ++count[a-1];
        for(int i = 0; i< count.size(); ++i){
            if(count[i] == 0) ret[1] = i+1;
            if(count[i] == 2) ret[0] = i+1;
        }
        return ret;
    }
};
方法三：while循环，swap交换
思路：
1.用while循环把所有数组中的数字放在其对应的位置上
2.再循环数组，没有归位的位置就是重复的元素，缺失的位置就是坐标值+1
class Solution {
public:
    vector<int> findErrorNums(vector<int>& nums) {
        for(int i = 0; i < nums.size(); ++i){
            while(nums[i] != nums[nums[i]-1]) swap(nums[i], nums[nums[i]-1]);
        }
        for(int i = 0; i< nums.size(); ++i){
            if(nums[i] != i+1) return{nums[i],i+1};
        }
    }
};
