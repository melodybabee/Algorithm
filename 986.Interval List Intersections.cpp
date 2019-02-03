题意：
汇合两个数组的交叉部分
思路：
1.设置两个指针分别遍历两个数组，每次取交叉的部分，左边界取大，右边界取小
2.如果有重叠的部分，那么把重叠的部分输入结果数组，结尾小的指针向后移动
3.如果没有重叠的部分，那么左边界小的指针向后移动
/**
 * Definition for an interval.
 * struct Interval {
 *     int start;
 *     int end;
 *     Interval() : start(0), end(0) {}
 *     Interval(int s, int e) : start(s), end(e) {}
 * };
 */
class Solution {
public:
    vector<Interval> intervalIntersection(vector<Interval>& A, vector<Interval>& B) {
        int p = 0;
        int q = 0;
        int temp = 0;
        vector<Interval>ret;
        while(p < A.size() && q < B.size()){
            int l = max(A[p].start,B[q].start);
            int r = min(A[p].end,B[q].end);
            if(l > r){
                if(l == A[p].start){
                    ++q;
                }else{
                    ++p;
                }
            }else{
                ret.push_back({l,r});
                if(r == A[p].end){
                    ++p;
                }
                else{
                    ++q;
                }
            }
        }
        return ret;
    }
};