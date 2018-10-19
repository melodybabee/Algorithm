题意：
有0，1，2三种颜色乱序排放，不用sort()方法按照0，1，2的顺序有序输出
方法一：桶排序／计数排序
思路：
1.用一个数组记录下每个数字的个数，再循环数组，更新到nums里。
class Solution {
public:
    void sortColors(vector<int>& nums) {
        int a = 0;
        int b = 0;
        int c = 0;
        for(int i = 0; i < nums.size() ;++i){
            if(nums[i]==0) ++a;
            else if(nums[i]==1) ++b;
            else if(nums[i]==2) ++c;
        }
        for(int i = 0; i < nums.size();++i){
            if(a!=0) {
                nums[i] = 0;
                --a;
            }
            else if(b!=0) {
                nums[i] = 1;
                --b;
            }
            else if(c!=0) {
                nums[i] = 2;
                --c;
            }
        }
        return;
    }
};
优化写法：
class Solution {
public:
    void sortColors(vector<int>& nums) {
        int count[3] = {0}, idx = 0;
        for (int i = 0; i < nums.size(); ++i) ++count[nums[i]];
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < count[i]; ++j) {
                nums[idx++] = i;
            }
        }
    }
};
方法二：交换排序
思路：
1.设置一个头尾指针，如果遇到0，当前位与头指针交换，如果遇到2，当前位与位指针交换
2.注意与2交换后会有新的元素跑到前面来，因此需要重新判断一遍，--i
3.循环的范围要小于尾指针，不然会把交换好的2又移动到前面去
class Solution {
public:
    void sortColors(vector<int>& nums) {
        int p = 0;
        int q = nums.size()-1;
        for(int i = 0; i <= q ;++i){
            if(nums[i] == 0) {
                swap(nums[i],nums[p]);
                ++p;
            }
            if(nums[i] == 2){
                swap(nums[i],nums[q]);
                --q;
                --i;
            }
        }
    }
};