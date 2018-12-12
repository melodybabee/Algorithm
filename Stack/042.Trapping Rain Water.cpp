elevation 海拔
题意：
在不同海拔高度的地方下雨，因为高度差会有积水，求积水量。
方法1:stack
思路：
1.通过分析题意得到如果stack为空或者后面的海拔高度低于等于前一位，没有高度差，无法积水，入栈。
2.如果高于前一位，出栈，如果栈为空也要扔掉，因为没有差距没有坑。
3.当高度和宽度都有差距的时候，取两者高度较小的一个减去坑的高度*两者的宽度差就是水的多少。
注意：
1.所谓的高度差都是当前元素与其前一位置的元素，即栈顶元素比较。
class Solution {
public:
    int trap(vector<int>& height) {
        stack<int>st;
        int ret = 0;
        int i = 0;
        while(i < height.size()){
            if(st.empty()||height[i]<=height[st.top()]){
                st.push(i);
                ++i;
            }else{
                int j = st.top();
                st.pop();
                if(st.empty()) continue;
                ret += (min(height[i],height[st.top()])-height[j])*(i-st.top()-1);
            }
        }
        return ret;
    }
};
方法二：dp两次遍历数组
思路：
1.针对每一个坐标而言，因为一点是否有积水是其左右海拔决定的，因此找到其最大的左坐标，再找到其最大的右坐标，两者取其小就是当前下雨后的位置
2.再用下雨后的位置减去下雨前的位置，就是积水量
class Solution {
public:
    int trap(vector<int>& height) {
        vector<int>dp(height.size(),0);
        int m = 0;
        int ret = 0;
        for(int i = 0; i< height.size();++i){
            dp[i] = m;
            m = max(m,height[i]);
        }
        m = 0;
        for(int i = height.size()-1;i> 0; --i){
            dp[i]= min(m,dp[i]);
            m = max(m,height[i]);
            if(dp[i] > height[i]) ret += dp[i]-height[i];
        }
        return ret;
    }
};
方法三：两个指针一次性扫描数组
思路：
1.可以从图中直观的看到，如果设置两个指针从头尾中较小值开始扫描，哪边小移动哪边，如果更小的值，将差值加到ret中，如果遇到更大的值，那么重新确定左右窗口
2.直到左右指针相遇后返回结果
3.相当于从小的值的一侧开始找大的一侧的值，大的一侧相当于“墙”的作用，主要找到比自己更小的，那么说明会有积水。
class Solution {
public:
    int trap(vector<int>& height) {
        int l = 0; 
        int r = height.size()-1;
        int ret = 0;
        while(l < r){
            int m = min(height[l],height[r]);
            if(m == height[l]){
                ++l;
                while(l < r && height[l]< m){
                    ret += m-height[l];
                    ++l;
                }
            }else{
                --r;
                while(l < r && height[r]< m){
                    ret += m-height[r];
                    --r;
                }
            }
        }
        return ret;
    }
};

二刷：
应用单调栈。
注意：
1.本题应用的是单减栈，遇到大的数字输出栈顶元素。
2.因为是积水，所以高度是当前元素与新的栈顶元素中的较小值，再减去之前栈顶元素的值。
如果pop之后不存在栈顶元素，那么直接跳过，不能积水。
class Solution {
public:
    int trap(vector<int>& height) {
        stack<int>st;
        int ret = 0;
        for(int i = 0; i< height.size();++i){
            while(!st.empty() && height[i] > height[st.top()]){
                int temp = st.top();
                st.pop();
                if(st.empty())continue;
                ret += (min(height[i],height[st.top()])-height[temp]) * (i - st.top()-1);
            }
            st.push(i);
        }
        return ret;
    }
};

12.12复习：
方法一：stack
注意如果开始为空或者小于栈顶元素直接push进去
如果大于首先还需要用一个temp变量记录下栈顶元素的值，如果pop结束之后为空，那么直接continue
class Solution {
public:
    int trap(vector<int>& height) {
        stack<int>st;
        int ret = 0;
        for(int i = 0; i < height.size();++i){
            while(!st.empty() && height[i] > height[st.top()]){
                int temp = st.top();
                st.pop();
                if(st.empty()){
                    continue;
                }
                ret += (min(height[i],height[st.top()]) - height[temp]) *(i-st.top()-1);
            }
            st.push(i);
        }
        return ret;
    }
};
2.两个指针依次扫描
注意：
分别从左右开始找较小的值，哪边小向哪边移动，如果还小，记录下结果。直到两个指针相遇为止。
class Solution {
public:
    int trap(vector<int>& height) {
        int left = 0;
        int right = height.size()-1;
        int ret = 0;
        while(left < right){
            int temp = min(height[left],height[right]);
            if(height[left] == temp){
                ++left;
                while(left < right && height[left] < temp){
                    ret += temp - height[left];
                    ++left;
                }
            }else if(height[right] == temp){
                --right;
                while(left < right && height[right] < temp){
                    ret += temp - height[right];
                    --right;
                }
            }
        }
        return ret;
    }
};