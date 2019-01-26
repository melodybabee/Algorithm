题意：给出课程的耗时和deadline，找到能上的最大数量的课
思路：
1.因为pair中第二个元素的含义是deadline,在这个时间之前可以上课，之后就不能上这门课了
因此对原数组中的数字的第二个位置进行排序
2.遍历数组，用一个变量来相加上当前需要花费的时间
3.贪心思想的精髓在于设置一个最小堆，每次把遍历到的数字放入其中，如果时间的总和超过了deadline,那么需要做的是把最小堆中的栈顶元素输出
因为栈顶元素是耗时最长的课程，本题中的目的是找到可以上的最大数量的课程。把这个课程输出之后说不定可以上更多的课程
4.最后返回最小堆的长度
注意：
1.在C++中最小堆默认是由大到小的，所以直接输出即可。如果要从小到大，还需要自定义
2.pair默认按照第一位上的数字进行排序，自定义排序方法要建立[](这部分是需要比较的两个值),返回的是需要比较的大小，从小到大就是<,反之亦然
注意sort方法自定义后要在()中执行这些，后面要有分号；
class Solution {
public:
    int scheduleCourse(vector<vector<int>>& courses) {
        sort(courses.begin(),courses.end(),[](vector<int>&a,vector<int>&b){
            return a[1] < b[1];
        });
        int time = 0;
        priority_queue<int>q;
        for(int i = 0 ;i < courses.size(); ++i){
            time += courses[i][0];
            q.push(courses[i][0]);
            if(time > courses[i][1]){
                time -= q.top();
                q.pop();
            }
        }
        return q.size();
    }
};