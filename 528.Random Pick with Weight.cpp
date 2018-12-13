题意：根据权重随机返回一个坐标位置。
思路：
prefix sum + binary search
1.题意是数组中显示的是每个数字的权重，根据权重来返回坐标。
比如数组是A= [1,3,5].那么有1个0坐标，3个1坐标，5个2坐标。形成坐标数组[0,1,1,1,2,2,2,2,2]，从中随机返回一个值
2.那么在初始化的时候首先更新数组，更新为求和数组，那么最后一个值就是所有的权重和。
3.从1-最大值里面随机抽取一个数字，上述的例子中就是从1-9中随机抽取一个数字
4.那么index表示返回数组中第一个比it的值大的元素的位置，是在新数组0，1，2中进行选择
其中返回的upper_bound函数实际上是在执行二叉搜索的操作
5.最后返回的坐标位置是index-起始位置，为了将index指针类型转换为整数型
class Solution {
private:
    vector<int>s;
public:
    Solution(vector<int> w) {
        for(auto num : w){
            if(s.empty()) s.push_back(num);
            else s.push_back(s.back()+num);
        }
    }
    
    int pickIndex() {
        int m = s.back();
        int it = rand()%m;
        auto index = upper_bound(s.begin(),s.end(),it);
        return index-s.begin();
    }
};

/**
 * Your Solution object will be instantiated and called as such:
 * Solution obj = new Solution(w);
 * int param_1 = obj.pickIndex();
 */