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
#include <iostream>//something should be inputted
#include <string>
using namespace std;
class solution{
public: //the method is public, so that we should declare the method to public with a ":"
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
}；

int main()//define a main method
{
    Solution s;//create a new class to execute the method which could solve the problem
    vector<int> v1;
    vector<int> v2;
    v1.push_back(0);
    v1.push_back(1);
    v1.push_back(2);
    v1.push_back(3);
    int target = 4;
    v2 = s.TwoSum(v1,target);//call the mathod in the solution class
    for(int i = 0 ; i < v2.size();++i){
        cout << v2[i] << endl;
    }
    return 0;
}

二刷复习：
方法：hashtable
思路：
1.先遍历一遍数组把数组中的值都放在hashtable中，key放数组的值，value放坐标
2.二次遍历，想要找到的目标数字是目标值-遍历到的数字，在map中找是否有这个数字。
如果没有，跳过。如果有，还需要判断是否是原数字，如果是原数字，跳过；如果不是，说明找到目标值，直接push到返回的数组中，break;
class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        unordered_map<int,int>map;
        vector<int> ret;
        for(int i = 0; i< nums.size();++i){
            map[nums[i]] = i;
        }
        for(int i = 0; i< nums.size();++i){
            int num = target - nums[i];
            if(map.find(num) != map.end() && map[num] != i){
                ret.push_back(i);
                ret.push_back(map[num]);
                break;
            }
        }
        return ret;
    }
};
优化写法成一个for循环
class Solution{
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        unordered_map<int,int>map;
        vector<int> ret;
        for(int i = 0; i< nums.size();++i){
            int num = target - nums[i];
             if(map.find(num) != map.end()){
                ret.push_back(i);
                ret.push_back(map[num]);
                return ret;
            }
            map[nums[i]] = i;
        }
    }
};
