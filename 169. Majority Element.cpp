class Solution {
public:
    int majorityElement(vector<int>& nums) {
       
        for (int i = 0; i < nums.size();++i){
            int ret = 0;
            for (int j = 0; j < nums.size();++j){
                if(nums[i]==nums[j]) ++ret;
                }
        
            if(ret > (nums.size()/2)){
                return nums[i];
                }
            }
        return -1;
    }
};
//T(O) = O(n^2), S(O) = O(1)
/*
设计思路：
1.设置一个指针在vector头部，循环整个vector,相同的加一
2.移动指针到与第一个数字值不同的位置，相加
3.把所有数字的频数存在一个数组里，比较最大值，输出

注意：
1.本题要求输出的是值，而不是频次，因为思路输出部分的思路不对
2.可以在for循环里++ret的时候，只要ret大于数组大小的一半，即可输出
3.当输入的数值过多时，解法不可通过，因此需要优化
*/
*****************************************
Sorting:
class Solution {
public:
    int majorityElement(vector<int>& nums) {
        sort(nums.begin(),nums.end());
        return nums[nums.size()/2];
    }
};
//T(O) = O(nlgn), S(O) = O(1)/O(n)
/*
优化：
1.首先将vector由小到大排列，因为出现最多次数的数字会超过所有数字的一半
2.因此直接输出中间位置的数字即可
*/
*****************************************
HashMap:（unordered_map)
class Solution {
public:
    int majorityElement(vector<int>& nums) {
        unordered_map <int,int> count;//<key,value>表示<number,出现的次数>
        for(int i = 0; i < nums.size(); ++i){
            ++count[nums[i]];
            if(count[nums[i]] > nums.size()/2){
                return nums[i];
            }
        }
    }
};
//T(O) = O(n), S(O) = O(n)
/*
思路：【待学习map和hashtable区别】当key很少的情况下，map与hashtable的效率差不多，甚至map更快，但当大规模的运算时，hashtable的效率会高很多
1.建立hashmap，unordered_map指无序映射，内部数据结构为红黑树，因此所有元素插入到map里面都会排好序，而且搜索过程为平衡二叉树搜索
2.依次循环vector,当循环到每一个数字的时候，在count的该位上+1
3.如果count在某一位上的大小已经大于vector大小的一半，则返回该数值
*/
*****************************************
Boyer-Moore Voting Algorithm
class Solution {
public:
    int majorityElement(vector<int>& nums) {
        int ret = nums[0];
        int count = 1;
        for(int i = 0; i < nums.size(); ++i){
            if(nums[i] == ret) count++;
            else{
                count--;
                if(count == 0) {
                    ret = nums[i];
                    count = 1;
                }
            }
        }
        return ret;
    }
};
//T(O) = O(n), S(O) = O(1)
/*
思路：
1.想要找到出现次数最多的数字，那么当他与其他数字抵消后，剩下的数字即为次数最多的数字
2.首先假设第一位是目标数字，count为1
3.如果第二位与它相等，count++，否则count--
4.一旦count为0的时候，将当前位设置为新的目标数字，count为1，再与后面的数字抵消，直到循环结束，目标数字所表示的值就为所求值
*/