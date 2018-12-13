/*
普通思路：
1.在vector里找只出现一次的元素，可以用i，j两个指针进行循环，如果没有第二个相同的元素出现，返回
2.但是此思路时间复杂度较高，为n的平方，因此需要优化
*/
************************************
class Solution {
public:
    int singleNumber(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        for(int i = 0; i < nums.size();i = i+2){
            if(nums[i]!= nums[i+1])
                return nums[i];
        }
        return 0;
    }
};
/*优化1:排序,时间复杂度 n*logn
1.首先将vector进行从小到大排序，循环新的vector
2.如果下一位与该位的值不同，则返回，若不同，则输出该位
注意：
1.nums[nums.size()]及其之后的值都为0，因此如果是最后一位最大的数字不同的话，也可以顺利输出
2.注意最后的return 0,是当for循环条件不满足，vector中没有单独的数字的情况
3.sort()函数【后面需要学习sort()函数内部代码机制,以及为什么时间复杂度是logn】
头文件：#include <algorithm>
有两种模式。返回值都是void,其中first和last都是迭代器，可以理解为指针，comp是自定义规则，比较范围[first,last)
(1)sort(first, last)
(2)sort(first, last, comp)
e.g.vector<int> vec = {3, 2, 4, 1, 7, 6, 5, 8 };
//1. 实现前四个元素的升序排序 sort(vec.begin(), vec.begin() + 4); 
//2. 实现后四个元素的升序排序 sort(vec.begin() + 4, vec.end(), comp); 
//3. 实现所有元素的升序排序 sort(vec.begin(), vec.end(), comp2);
//4. 降序排序sort(vec.rbegin(), vec.rend()); <==> sort(vec.begin(), vec.end()); reverse(vec.begin(), vec.end());
*/
************************************
class Solution {
public:
    int singleNumber(vector<int>& nums) {
        int ret = 0;
        for(int i = 0; i< nums.size();++i){
            ret = ret^nums[i];
        }
        return ret;
    }
};
/*优化2:Bit Manipulation位运算，T(n) = n, S(O) = 1
1.概念：位运算其实就是直接对在内存中的二进制数据进行操作，因此处理数据的速度非常快.
只可用于整形，不能用于float and double
2.常见的位操作有：
&，与，两位都为1时为1
|，或，两位都为0的时候为0
^，异或，相同为0，不同为1，任何数与0异或为此数
~，取反，0->1, 1->0
3.本题的思路是：
0与任何数异或的结果为0，相同数字异或结果为0。出现一次的数字会为该数字本身，出现两次的数字会相互抵消为0，因此还为初始值本身
*/
************************************
/*优化3:hashmap,时间和空间复杂度都是O(n)
【需要学习hashmap]
*/
************************************
/*优化4:数学方法，时间和空间复杂度都是O(n)
2*(a+b+c)-a-a-b-b-c = c
先全部求和再相减即可。
*/

12.11复习：
1.hashtable
class Solution {
public:
    int singleNumber(vector<int>& nums) {
        unordered_map<int,int>map;
        for(auto a:nums){
            ++map[a];
        }
        for(auto it : map){
            if(it.second == 1) return it.first;
        }
    }
};
2.位运算
注意^表示相同为0，不同为1，所以两个相同的数字位运算之后为0，不同为1，那么最后剩下的就是那个单独存在的元素。
class Solution {
public:
    int singleNumber(vector<int>& nums) {
        int res = 0;
        for(auto a: nums){
            res ^= a;
        }
        return res;
    }
};