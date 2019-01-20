题意：对一个已经排好序的数组进行平方排序
思路：
1.新建一个结果数组，设置两个指针分别指向开头和末尾。在头指针小于0的时候且小于右指针的时候，取每次比较的较大值。
放到数组的末尾。结果数组中的指针向前移动，输入的是哪个数字移动哪个指针。
2.当左指针大于0的时候，判断和右指针是否重合，没有重合的话不断向前移动右指针。
class Solution {
public:
    vector<int> sortedSquares(vector<int>& A) {
        int left = 0; 
        int right = A.size()-1;
        vector<int>ans(A.size(),0);
        int p = A.size()-1;
        while(A[left] <= 0 && left <= right){
            int l = A[left] * A[left];
            int r = A[right] * A[right];
            if(l == r) {
                ans[p] = l;
            }else ans[p] = max(l,r);
            if(ans[p] == l) {
                ++left;
            }else if(ans[p] == r){
                --right;
            }
            --p;
        }
        while(left <= right){
            ans[p] = A[right] *A[right];
            --right;
            --p;
        }
        return ans;
    }
};

Weekly contest 120总结：
现在需要提高的是速度，要加快思考的速度和对于一些固定应用模版的速度，不要在易错点或者模版上浪费过多时间。
解决方法：
1.多见题，多分类总结。
2.温故而知新。