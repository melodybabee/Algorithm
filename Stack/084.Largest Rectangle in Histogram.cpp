Histogram 直方图
题意：
找到直方图中能形成的最大面积的矩形。
方法一：遍历
T(n) = O(n^2);
思路：
1.从头到尾遍历，进入循环之后，如果它的下一位还在范围内且下一位和当前位置相等，那么continue
2.如果不等，那么从当前位置开始向前循环，每次取高度的较小值*横坐标的长度=面积
3.最后取面积的较大值
class Solution {
public:
    int largestRectangleArea(vector<int>& heights) {
        int ret = 0;
        for(int i = 0; i < heights.size();++i){
            if(i+1 < heights.size() && heights[i] <= heights[i+1]) continue;
            
            int h = heights[i];
            for(int j = i; j >= 0; --j){
                h = min(h, heights[j]);
                ret = max(ret,h *(i-j+1));
            }
        }
        return ret;
    }
};
方法二：单调栈
T(n) = O(n);
思路：
1.因为题目中要求求出最大的面积，那么为了使连续的矩阵尽量多，使用单调栈的数据结构维护。
如果后面的数字的值小于当前栈顶的值，那么表示计算了以栈顶的顶为上边框的最大矩形。需要找到尽量多连续矩阵并使最低的那一块尽可能高。
2.那么本题构造的是一个单增的单调栈，每当遍历到的元素大于栈顶元素的时候，入栈。
一旦遇到比栈顶元素小的数字，说明计算的矩形的左右边框都已经到达了边界，因为单增栈的特性，在栈内的值小于栈顶元素，新遍历到的值也小于栈顶元素，因此计算以栈顶元素为上限的矩形的面积。
注意计算后要把遍历指针i-1，便于重新进入循环后操作比较遍历到的值与新的栈顶元素大小。
3.为了便于计算矩形的宽度，入栈的不是数组中的值，而是在数组中的坐标，每次计算面积的时候，出栈后如果栈空，说明遍历到的位置的值比头结点的位置的值还小，那么会形成宽比较大，高度较小的矩阵。
如果不为空，那么计算宽度为当前遍历到的位置和新的栈顶元素坐标的差值。
4.注意如果后面位置的数值等于栈顶元素时，入栈或者弹出栈顶元素进行计算都可以，不影响结果。
5.为了能计算所有在数组中的结果，需要手动在数组最后加上一个尾部值0，作为最小值，便于所有入栈元素都能出战被计算过一次。
class Solution {
public:
    int largestRectangleArea(vector<int>& heights) {
        stack<int>st;
        heights.push_back(0);
        int area = 0;
        for(int i = 0 ; i < heights.size();++i){
            if(st.empty() || heights[i] > heights[st.top()]){
                st.push(i);
            }else{
                int temp = st.top();
                st.pop();
                area = max(area,heights[temp]*(st.empty()? i : (i-st.top()-1)));
                --i;
            }
        }
        return area;
    }
};
内部while写法：
class Solution {
public:
    int largestRectangleArea(vector<int>& heights) {
        stack<int>st;
        heights.push_back(0);
        int area = 0;
        for(int i = 0 ; i < heights.size();++i){
            while(!st.empty() && heights[i] < heights[st.top()]){
                int temp = st.top();
                st.pop();
                area = max(area,heights[temp]*(st.empty()? i : (i-st.top()-1)));
            }
            st.push(i);
        }
        return area;
    }
};

补充：单调栈Monotone Stack
1.单调栈的一大优势就是线性的时间复杂度，所有的元素只会进栈一次，而且一旦出栈后就不会再进来了。
2.元素加入栈前，会在栈顶端把破坏栈单调性的元素都删除
3.使用单调栈可以找到元素向左遍历第一个比他小的元素，也可以找到元素向左遍历第一个比他大的元素。


2.21复习：
注意：
暴力的解法就是找到峰值再依次向前遍历，找到较大的面积。比两个for的循环增加了剪枝环节
class Solution {
public:
    int largestRectangleArea(vector<int>& heights) {
        int res = 0;
        for(int i = 0; i < heights.size();++i){
            if(i+1 < heights.size() && heights[i] < heights[i+1]) continue;
            int temp = heights[i];
            for(int j = i; j >= 0; --j){
                temp = min(temp,heights[j]);
                res = max(res,temp*(i-j+1));
            }
        }
        return res;
    }
};

单调栈：
注意：
1.首先分清楚是单增的栈还是单减的栈，区别在于单增的栈在遇到小于栈顶元素的时候处理，反之亦然
而本题遇到小于栈顶的元素的时候说明需要对当前的峰值进行处理计算，所以要用到单增的栈
2.注意为了便于计算横坐标的长度，栈中放的都是坐标位置
3.注意判断栈是否为空的状态。取栈顶元素之前需要判断，在计算宽度的时候还要计算。
class Solution {
public:
    int largestRectangleArea(vector<int>& heights) {
        stack<int> st;
        heights.push_back(0);
        int ret = 0;
        for(int i = 0; i < heights.size(); ++i){
            while(!st.empty() && heights[i] < heights[st.top()]){
                int temp = st.top();
                st.pop();
                ret = max(ret,heights[temp]*(st.empty() ? i : i-st.top()-1));
            }
            st.push(i);
        }
        return ret;
    }
};