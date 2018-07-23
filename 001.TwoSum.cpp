#include <iostream>
using std::vector;

class solution{
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        vector <int> ans;
        for (int i = 0；i < nums.size();i++){
            for (int j = 0; j < nums.size(); j++){
            if (nums[i] + nums [j] == target){
                ans.push_back[i];
                ans.push_back[j];
                return ans;
                }
            }
        }
    }
};

//note
/* 1.indices：位置序号。有指数、目录含义，本题中指在一个array中的位置序号
   2.注意vector的使用语法，可以认为是一个动态数组
   3.在需要用两个变量（可能跟时间复杂度有关？？）对整个vector进行遍历的时候，要想到两层for循环，思路是首先将一个变量（i)固定，使另一个变量（j)遍历到结尾，再逐渐移动第一个变量(i)，从而往复
   4.i++与++i的区别：在for循环中没有区别
   但++i是前量自增，先增加再赋值，比如int i = 0; a = ++i; a此时是1；
   i++是后量自增，先赋值再增加，同样int i = 0; a = i++; a此时是0；
   在大规模的循环中，++i更快，因为i++中系统需要保存一个临时变量保存i
   */
//PS.本题采用暴力解题法，有更好的方法，待学习
