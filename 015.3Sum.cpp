题意：
找到数组中三个数组相加等于0的非重复子数组
思路：
1.首先对大数组进行排序，使其从小到大排列
2.确定头指针位置，用另外两个指针对头指针后面的数组分别从头尾进行查找，找到和等于0-头指针大小的两个元素
3.在查找的过程中，如果找到，需要判断内部是否有重复元素，如果有，跳过，没有，两个指针分别向内移动。
  同时如果相加的值小于目标值，左指针右移，如果大于目标值，右指针左移。
4.可以节省流程的条件：
进入for循环之前：
如果排序的结果最后一位小于0，返回空；
如果为空，返回空；
进入for循环之后：
如果头结点的值大于0，跳出循环；
如果有重复的头结点，跳过，重新进入循环；

注意：
1.编译错误提示：
reference binding to null pointer of type 'value_type'错误原因：
（1）测试样例输入为非空数组情况：
可能原因：
a.数组越界，在对vector初始化的时候没有初始化到合适大小，而在接下来的使用中使用了越界的下标。
b.对于vector构建出来的二维数组没有进行空间的申请,比如有些返回类型为vector<vector<>>类型的函数，对于这个返回值vector表示的二维数组要先申请大小，否则使用下标访问就会报这类错误。//即vector不声明大小不可以用下标循环
（2）测试样例输入为空数组情况：
对于数组长度为0的情况没有进行判断，加入判断条件就可以解决。
class Solution {
public:
    vector<vector<int>> threeSum(vector<int>& nums) {
        vector<vector<int>> ret;
        sort(nums.begin(), nums.end());
        if(nums.empty()) return {};
        if(!nums.empty() && nums[nums.size()-1]< 0) return {};
        for (int i = 0; i< nums.size()-2; ++i){
            if(nums[i]>0) break;
            if(i>0 && nums[i] == nums[i-1]) continue;
            int target = -nums[i];
            int p = i+1;
            int q = nums.size()-1;
            while(p<q){
                if(nums[p]+nums[q] == target){
                    ret.push_back({nums[i],nums[p],nums[q]});
                    while(p < q && nums[p+1] == nums[p]) ++p;
                    while(p < q && nums[q-1] == nums[q]) --q;
                    ++p;
                    --q;
                }else if(nums[p] + nums[q] < target){
                    ++p;
                }else{
                    --q;
                }
            }
        }
        return ret;
    }
};