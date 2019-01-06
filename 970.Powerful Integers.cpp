题意：
判断在范围内两个数字的完全平方数能组成几个数字。
思路：
1.因为涉及到两个数字的完全平方，那么分别循环即可。注意两个平方数字的边界是当前数字的平方不超过规定范围即可。
2.需要注意当其中一方或者双方的指数为1的时候需要单独判断，不能进入循环，因为1的任何次数幂都是1。
3.在计算的过程中因为需要去重，所以用set来记录，最后输入到数组中。set是去重且自动排序，unordered_set不会排序。
class Solution {
public:
    vector<int> powerfulIntegers(int x, int y, int bound) {
        if(bound < 2 ) return {};
        if(x == 1 && y == 1) return {2};
        set<int>s;
        if(x == 1){
            for(int j = 0; pow(y,j) <= bound; ++j){
                int temp = 1 + pow(y,j);
                if(temp <= bound) s.insert(temp);
            }
        }
        else if(y == 1){
            for(int i = 0; pow(x,i) <= bound; ++i){
                int temp = 1 + pow(x,i);
                if(temp <= bound) s.insert(temp);
            }
        }
        else{
            for(int i = 0 ; pow(x,i) <= bound; ++i){
                for(int j = 0; pow(y,j) <= bound; ++j){
                    int temp = pow(x,i) + pow(y,j);
                    if(temp <= bound) s.insert(temp);
                }
            }
        }
        vector<int>ret;
        for(auto a: s) ret.push_back(a);
        return ret;
    }
};

Weekly Contest 118总结：
1.总结了一下打了10+次比赛但是名次提升不明显的原因：
首先投入度不够，有遇到困难就停滞不前的心态；
题目还是不够熟练，有点抵触暴力求解，所有题目首先要想到暴力求解的方法，尽管思路复杂但是想清楚后可以开始写，比赛中解题>高效解题；
对于一些套路没有形成条件反射，基本的解题思路以及写法该背下来的需要形成条件反射
2.第一题仍然有corner cases没有想到，想到了两个1不满足要求就应该还继续想1个1的情况。
3.第二题是煎饼排序的问题，有一定的套路，要加大题量。
4.第三题没有时间思考了，临近结束时刻不太能投入思考。关于tree的问题再想一想是可以求解的。