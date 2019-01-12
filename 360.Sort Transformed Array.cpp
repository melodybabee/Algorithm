题意：对已经排好序的数组进行抛物线排序
方法一：最小堆
T(n) = O(nlogn);
思路：
1.用最小堆对计算的结果进行排序，用一个数组来记录最小堆中每输出的第一个元素，直到最小堆为空
注意：
1.最小堆priority_queue默认是由大到小的，因此如果想要从小到大排序，那么需要自定义。
注意要声明数组vector<int>，要自定义方法greater<int>
2.priority_queue需要用q.top()来获取头部元素
class Solution {
public:
    vector<int> sortTransformedArray(vector<int>& nums, int a, int b, int c) {
        priority_queue<int,vector<int>,greater<int>>q;
        vector<int>ret;
        for(auto n : nums){
            q.push(a*n*n+b*n+c);
        }
        while(!q.empty()){
            ret.push_back(q.top());
            q.pop();
        }
        return ret;
    }
};
方法2:利用抛物线的性质
T(n) = O(n);
思路：
1.利用抛物线的性质，由于数组是已经排好序的，那么如果a大于0表示开口向上，最大的值在两侧，那么设置两个指针分别从两侧开始比较大小，在返回数组中从结尾输入即可。
如果是a小于0的函数，那么开口向下，两侧是最小值，那么在返回数组中从头部开始输入即可。
2.注意在左右指针判断的过程中，当两者相遇的时候跳出，因此要有l <= r，相等的判断
class Solution {
public:
    vector<int> sortTransformedArray(vector<int>& nums, int a, int b, int c) {
        vector<int>ret(nums.size());
        int index= 0;
        if(a >= 0) index = nums.size() -1;
        int l = 0;
        int r = nums.size()-1;
        while(l <= r){
            if(a >= 0){
                ret[index] = cal(nums[l],a,b,c) >= cal(nums[r],a,b,c) ? cal(nums[l++],a,b,c) : cal(nums[r--],a,b,c);
                --index;
            }else{
                ret[index] = cal(nums[l],a,b,c) >= cal(nums[r],a,b,c) ? cal(nums[r--],a,b,c) : cal(nums[l++],a,b,c);
                ++index;
            }
        }
        return ret;
    }
    
    int cal(int num, int a, int b, int c){
        return a*num*num + b*num +c;
    }
};