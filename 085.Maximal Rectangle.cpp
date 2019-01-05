题意：找到矩阵中最大的矩形面积
方法一：类似084，利用单调栈找最大直方图面积
思路：
1.首先想到的是利用BFS或者DFS进行解题，但是难点在于无法计算出面积的长度和宽度，同时本题需要借助之前的结果，那么容易想到是DP的思路
2.那么设置一个数组用来遍历每一行，把每一行更新直方图的面积，类似084题的思路
注意这个数组是不断进行累加的，也就是说新的一行会在之前的基础之上进行更新，是0就改为0，不是0就在原基础上+1
3.每遍历结束一行之后就用单调栈找到最大的面积
单调栈中的思路是如果为空或者比顶部元素大，那么输入
如果比顶部元素大，那么弹出顶部元素，计算面积，更新
注意：
1.单调栈中如果想把所有的值都计算过一次，那么需要在遍历之前加入0，才能使所有元素都有机会输出
2.弹出栈顶元素之后，因为少了一个元素，所以遍历的i坐标需要后退1个位置
3.单调栈的核心思想就是每弹出一个元素，用其值作为高，用当前位置的坐标减去新的栈顶元素的坐标作为宽
4.因为在数组的最后加上了一个0，所以每次进入新的循环的时候需要重新声明一下数组的大小，用resize()方法
区分：
resize()，设置大小（size）;
reserve()，设置容量（capacity）;
size()是分配容器的内存大小，而capacity()只是设置容器容量大小，但并没有真正分配内存。
打个比方：正在建造的一辆公交车，车里面可以设置40个座椅（reserve(40);），这是它的容量，但并不是说它里面就有了40个座椅，只能说明这部车内部空间大小可以放得下40张座椅而已。而车里面安装了40个座椅(resize(40);)，这个时候车里面才真正有了40个座椅，这些座椅就可以使用了。
public:
    int maximalRectangle(vector<vector<char>>& matrix) {
        vector<int> temp;
        int ret = 0;
        for(int i = 0; i < matrix.size(); ++i){
            temp.resize(matrix[i].size());
            for(int j = 0; j < matrix[i].size(); ++j){
                temp[j] = matrix[i][j] == '0' ? 0 : temp[j] +1;
            }
            ret = max(ret, cal(temp));
        }
        return ret;
    }
    
    int cal(vector<int>&temp){
        stack<int>st;
        int ret = 0;
        temp.push_back(0);
        for(int i = 0 ; i < temp.size(); ++i){
            if(st.empty() || temp[st.top()] <= temp[i]) st.push(i);
            else{
                int tep = st.top();
                st.pop();
                ret = max(ret, temp[tep] * (st.empty() ? i : (i - st.top() -1)));
                --i;
            }
        }
        return ret;
    }
};