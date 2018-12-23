题意：
找到2N大小的数组中重复N次的数字。
方法一：HashTable
思路：
1.先建立一个哈希表
2.循环哈希表，如果在哈希表中能找到当前循环到的元素，那么直接返回结果。没有找到，在哈希表中添加上这个元素。
class Solution {
public:
    int repeatedNTimes(vector<int>& A) {
        unordered_map<int,int>map;
        for(auto a:A){
            if(map.count(a)) return a;
            else ++map[a];
        }
    }
};

方法2:利用题目中的条件进行解题
思路：
1.因为题目中一共有2N个数字，N+1个不同的数字，那么其中一个数字出现了N次。
2.因此把数字分成3个3个进行比较，如果有相同的那么就返回，不相同继续循环。
如果到最后都没有相同的，那么返回最后一个元素。比如[2,1,3,2]
class Solution {
public:
    int repeatedNTimes(vector<int>& A) {
        for(int i = 2; i < A.size(); ++i){
            if(A[i-2] == A[i-1] || A[i-2] == A[i]) return A[i-2];
            if(A[i-1] == A[i]) return A[i];
        }
        return A[A.size()-1];
    }
};

Weekly contest 116总结：
1.本次状态有些恢复，可能是因为没有那么紧张了。短时间内AC了两道题，其中第二题本可以一次AC，有一个边界条件没有注意到位，思路是对的，还需要细心。
主要原因是上周重新重点复习了双指针的题目，所以能够一下子想到时间负责度比较好的解法。
后面刷题出了一刷tag题目以外，还要从各个类型出发进行总结性刷题。坚持坚持坚持！
2.第三题是前一阵周赛找最小矩形面积的变形，本次可以使边不平行于X轴和Y轴。有思路不会用代码表示，会在题目中更新。
3.hard类型的周赛题目还是没有仔细思考，要逐渐突破这一关。