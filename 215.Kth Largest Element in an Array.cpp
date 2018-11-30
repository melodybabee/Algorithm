题意：
找到array中第K大的值，不是元素。
思路一：priority_queue
1.在priority_queue中依次输入数组中的元素，在K之前不断pop出顶部的元素，最后返回堆顶元素。
class Solution {
public:
    int findKthLargest(vector<int>& nums, int k) {
        priority_queue<int> q;
        int ret = 0;
        for(int i = 0; i < nums.size(); ++i){
            q.push(nums[i]);
        }
        for(int i = 1; i < k; ++i){
            q.pop();
        }
        ret = q.top();
        return ret;
    }
};
优化：
priority_queue可以通过数组的头部和尾部直接输入元素
class Solution {
public:
    int findKthLargest(vector<int>& nums, int k) {
        priority_queue<int> q(nums.begin(),nums.end());
        for(int i = 1; i < k; ++i){
            q.pop();
        }
        return q.top();
    }
};
方法二：sort
注意题目中求的是第K大的值，不是第K大的数字，所以可以用排序，排序不去重。
class Solution {
public:
    int findKthLargest(vector<int>& nums, int k) {
        sort(nums.begin(),nums.end());
        return nums[nums.size()-k];
    }
};
补充：
sort函数：
头文件： #include<algorithm>
		using namespace std;
时间复杂度：O(nlogn)
sort函数有三个参数：（第三个参数可选） 
第一个是要排序的数组的起始地址
第二个是结束的地址（最后一位要排序的地址）
第三个参数是排序的方法，可以是升序也可是降序。如果不写第三个参数，则默认的排序方法是从升序排列
第三个参数：
bool compare(int a, int b) {
    //return a < b;  //升序排列
    return a > b;  //降序排列
}
方法3:quick sort
思路：
1.因为题目中找第K大的数字，那么把所有大于目标值的数左移，把所有小于目标值的数右移，这样第K大的坐标就是k-1.
如果返回的坐标是k-1,那么返回当前值否则缩小左右边界范围再次调用快排
2.进入快排之后把头部结点固定，左小于固定点且右大于固定点，交换
最后把右边界与固定点交换
返回右坐标的位置
注意：
1.swap函数两个位置必须是坐标，不能是值
2.注意在快排判断的过程中，不含等号，如果相等只改变坐标不进行交换
3.本题因为求第K大，所以所有大于K的数字应该放在左侧
class Solution {
public:
    int findKthLargest(vector<int>& nums, int k) {
        int i = 0;
        int j = nums.size()-1;
        while(true){
            int pos = quickSort(i,j,nums);
            if(pos == k-1) return nums[pos];
            else if(pos > k-1) j = pos-1;
            else i = pos +1;
        }
    }
    
    int quickSort(int left, int right, vector<int>& nums){
        int goal = nums[left];
        int l = left +1;
        int r = right;
        while(l <= r){
            if(nums[l] < goal && nums[r] > goal){
                swap(nums[l],nums[r]);
                ++l;
                --r;
            }
            if(nums[l] >= goal) ++l;
            if(nums[r] <= goal) --r;
        }
        swap(nums[r],nums[left]);
        return r;
    }
};
方法4:堆排序方法待学习