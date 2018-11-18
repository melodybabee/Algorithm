题意：
判断一个数组是不是山状数组。
思路：
1.山状数组的定义是从头部到尾部是先单增后单减的
2.那么首先用一个for循环找到这个元素，如果满足递增，那么标记位设置为true；
如果遇到小于当前元素的数字，那么记录下最高点的位置，break循环。
如果等于当前数字，那么直接返回false.
3.再次从最高点的下一位进入for循环，如果后面的数字大于等于当前数字，直接返回false;
如果有单减，那么把标记为设置为true
4.最后返回两个标记位是否都是true,表示是否存在单增或者单减，同时内部满足单调的关系。
class Solution {
public:
    bool validMountainArray(vector<int>& A) {
        if(A.size() < 3) return false;
        int temp = -1;
        bool t = false;
        bool s = false;
        for(int i = 0; i < A.size() ; ++i){
            if(i > 0 && A[i] > A[i-1]) {
                t = true;
                continue;
            }
            else if (i > 0 && A[i] == A[i-1]) return false;
            else if(i > 0 && A[i] < A[i-1]){
                temp = i-1;
                break;
            }
        }
        for(int i = temp+1; i < A.size();++i){
            if(A[i] >= A[i-1]){
                return false;
            }else{
                s = true;
            }
        }
        return t && s;
    }
};
优化：
思路：
1.这种写法的思路非常清晰值得借鉴。
2.因为山状的性质就是有一个最高点，从头部到最高点增，从尾部到最高点反向增。
3.那么从头部开始循环直到最高点，从尾部开始反向循环到最高点。最后判断是否两个指针从初始位置移动（即有最高点）且两种方式判断出来的点重合。
class Solution {
public:
    bool validMountainArray(vector<int>& A) {
        int n = A.size(),i = 0, j = n-1;
        while(i+1 < n && A[i] < A[i+1]) ++i;
        while(j-1 > 0 && A[j] < A[j-1]) --j;
        return i > 0 && i ==j && j < n-1;
    }
};

Weekly contest 111总结：
1.本次AC3题，1200名左右，但是第一道easy题目提交了4次，耽误了大量时间。一方面思考清楚题意，另一方面善于运用下面测试的面板手动输入调试。
2.第一道题难度easy但是有很多边界情况没有考虑到，没有考虑全面corner cases的根本是没有弄清题意。
最开始以为是只要有一个最高点即可，后来发现必须严格遵守单增和单减。理清楚思路之后再开始写代码做题。
3.二三两道题的难度也不大，弄清楚题意直接写即可一次AC。
注意平时就要锻炼自己debug，自己理清问题的能力，不要借助通过每次提交来找错。
4.开始加强hard题目的练习，最后一道题目完全没有思路，平时练习中要开始着重锻炼。
