题意：找到数组中距离1的最长距离是多少
思路：
1.因为想要找到的是距离1的位置的长度，那么首先用一个头指针来指向第一个位置。
2.从0开始进入循环，如果没有遇到1，那么不作任何处理。
遇到1了，如果头指针还在第一个位置，那么最长的长度就是从该位置到头部指针的位置。如果头部指针不在第一个位置上了，那么距离就是两个指针取中点。
3.每当遇见1的时候，就把头部指针更新到新的1的位置上。
4.在循环结束之后，为了处理类似(1,0,0,0)的情况。还需要比较下当前的结果值与数组长度-当前位置上的差值中的较大值
class Solution {
public:
    int maxDistToClosest(vector<int>& seats) {
        int ret = 0;
        int temp = 0;
        int n = seats.size();
        for(int i = 0; i < seats.size(); ++i){
            if(seats[i] == 1) {
                if(temp == 0) ret = max(ret,i-temp);
                else ret = max(ret,(i-temp+1)/2);
                temp = i+1;
            }
        }
        ret = max(ret,n-temp);
        return ret;
    }
};