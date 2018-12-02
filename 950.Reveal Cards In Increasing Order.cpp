题意：
按照要求把数组调整成输出为升序的格式。
思路：【原理存疑】
1.对题目中的操作方法进行反操作即能得到，即simulation模拟题目中给出的过程。
2.题目中要求求出增序的数列，那么首先对数组进行降序排列，greater<int>()方法表示降序
3.开始遍历，把新的数组中的尾部元素放在头部，同时加入当前最大的元素，不断循环直到结束。
class Solution {
public:
    vector<int> deckRevealedIncreasing(vector<int>& deck) {
        sort(deck.begin(),deck.end(),greater<int>());
        vector<int>ret;
        ret.push_back(deck[0]);
        for(int i = 1; i < deck.size();++i){
            int temp = ret.back();
            ret.pop_back();
            ret.insert(ret.begin(),temp);
            ret.insert(ret.begin(),deck[i]);
        }
        return ret;
    }
};